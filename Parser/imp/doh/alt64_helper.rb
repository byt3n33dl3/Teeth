#!/usr/bin/env ruby
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

require "pp"
require "optparse"
require "set"

OptionParser.new do |o|
  o.on('--not [characters]') { |b| $not = b }
  o.on('-h') { puts o; exit }
  o.parse!
end

$a = {}
$a["lower"]   = "abcdefghijklmnopqrstuvwxyz"
$a["upper"]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
$a["number"]  = "0123456789"
$a["special"] = " !\"#\$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

$a = $a.map do |k,v|
  [k, v.chars.sort.join]
end.to_h
TOTAL = 64

$out = ""

puts "Give me one or more of '#{$a.keys.join ' '}' as arguments" if ARGV.length == 0

def red(s)
  "\e[31m#{s}\e[0m"
end
def yellow(s)
  "\e[33m#{s}\e[0m"
end

sets = ARGV.map {|b|
  abort red("Error: #{b} is not one of '#{$a.keys.join ' '}'.") unless $a.has_key? b
  $a[b]
}

sets.sort_by { |v|
  v.length
}.each_with_index { |b, i|
  b.delete! $not if $not
  want = (TOTAL - $out.length) / (sets.length - i)
  #puts "want #{want} = #{(TOTAL - $out.length)} / #{(sets.length - i)}"
  want = b.length if b.length < want
  $out += b.chars.sort.join[0..want-1]
}

if $out.length != 64
  abort red("Error: Got '#{$out}' of length #{$out.length} which != 64")
end


u = Set.new $out.chars
# figure out which characters are duplicated
dups = $out.chars.reject { |c| u.delete(c) if u.include?(c) }
dl = dups.length
if dl > 0
  abort red("Error: The character#{dl>1?'s':''} '#{dups.join}' occur#{dl>1?'':'s'} more than once.  This reduces entropy and is not safe!")
end

$out = $out.chars.sort.join

puts yellow("#{' '*$out.index(' ')}/---- Note: don't forget to include the space") if $out =~ / /

puts $out
