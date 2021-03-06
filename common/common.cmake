#
# This file is part of moonphase.
# Copyright (C) 2014-2015 by Alan Wise (alanwise@users.sourceforge.net)
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

INCLUDE_DIRECTORIES(
    "${CMAKE_CURRENT_LIST_DIR}/sources/"
    "${CMAKE_SOURCE_DIR}/toolbox/generic/sources/")


#
# Sources
#

SET(COMMON_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/sources/calcephem.c"
    "${CMAKE_CURRENT_LIST_DIR}/sources/datetime.c"
    "${CMAKE_CURRENT_LIST_DIR}/sources/information.c"
    "${CMAKE_CURRENT_LIST_DIR}/sources/moondata.c")
SET(COMMON_FILES
    ${COMMON_SOURCES})


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
