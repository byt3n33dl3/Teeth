# Copyright (c) 2016 Jake Willoughby
#
# This file is part of DOH.
#
# DOH is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# DOH is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with DOH.  See gpl3.txt. If not, see <http://www.gnu.org/licenses/>.
require 'openssl'
require 'io/console'
require "base64"

def red(s)
  "\e[31m#{s}\e[0m"
end

def rotate_bytes(b)
  c = b.bytes.reduce(""){|t,x| t += x.to_s(2).rjust(8, '0')}
  c = c.chars.unshift(c.chars.pop)[0..-2]
  a = 0.step(c.length, 8).reduce([]) { |t,i|
    next t if i == c.length
    t.push c[i..i+7].join.to_i(2)
  }.pack('c*')
  a
end

def doh(spec, hashedMaster, sequence, domain, salt, iterations, key_length, digest)
  bytes = OpenSSL::PKCS5.pbkdf2_hmac(hashedMaster, sequence + domain + salt, iterations, key_length*6/8, digest)
  rotated = 0

  attempts = 0
  while true #TODO: bound this so it exits
    catch :regenerate do
      attempts += 1
      abort red("More than 1000 rotation attempts, password requirements are too strict") if attempts > 1000
      pwd = Base64.encode64(bytes).delete("=").tr("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",spec["chars"])[0..key_length-1]

      (spec["require"] || []).each do |k,v|
        v.each do |i|

          # TODO: do this check at load time and not here
          required_not_in_chars = i.chars - spec["chars"].chars
          unless required_not_in_chars.empty?
            abort red("Error: Invalid domain spec for #{domain}. Requires characters '#{required_not_in_chars.join}', but they are not in the domain characters.")
          end

          total = 0
          i.each_char do |c|
            total += pwd.count c
          end

          ## didn't meet requirements, rotate bytes and try again
          # TODO: calculate the expected number of iterations to meet requirements and warn if high
          if total < k
            if rotated < 5
              bytes = rotate_bytes(bytes)
              rotated += 1
            else
              bytes = digest.digest(bytes)[0..key_length]
              rotated = 0
            end
            throw :regenerate
          end
        end
      end
      return pwd
    end
  end
end
