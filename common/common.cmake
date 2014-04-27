#
# This file is part of moonphase.
# Copyright (C) 2014 by Alan Wise (alanwise@users.sourceforge.net)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#


#
# Configuration
#


#
# Include paths
#

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/sources/")


#
# Sources
#

# Until toolbox is updated
#INCLUDE(${CMAKE_SOURCE_DIR}/toolbox/generic/toolboxgeneric.cmake)
SET(COMMON_FILES 
    "${CMAKE_CURRENT_LIST_DIR}/sources/debuglog.c"
    "${CMAKE_CURRENT_LIST_DIR}/sources/messagelog.c")
# ...
SET(COMMON_FILES "${COMMON_FILES}"
    "${CMAKE_CURRENT_LIST_DIR}/sources/calcephem.c"
    "${CMAKE_CURRENT_LIST_DIR}/sources/moondata.c")


#
# Binaries
#


#
# Subdirectories
#


#
# Installation
#


#
# CMakeLists.txt
#
