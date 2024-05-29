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
require "json"
require "yaml" 
require "pp"

$specs = YAML.load(File.open("domain_specs.yaml"))

puts JSON.pretty_generate($specs)
