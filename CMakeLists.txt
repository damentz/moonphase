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

# CMake minimum version
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name
PROJECT(moonphase)

# Load user preferences
INCLUDE(${CMAKE_SOURCE_DIR}/preferences.cmake OPTIONAL)

# Build information.
SET(OWNER_STRING "Alan Wise")
SET(COPYRIGHTNOTICE_STRING
    "Copyright (C) 2014 ${OWNER_STRING}.")
SET(WEBSITE_STRING "")
SET(LICENSE_STRING 
    "License GPLv3: GNU GPL version 3 or later <http://gnu.org/licenses/>.")

# Convert license agreement to include file
FILE(READ "${PROJECT_SOURCE_DIR}/COPYING" COPYING)
STRING(REGEX REPLACE "\"" "\\\\\"" ESCAPEQUOTES "${COPYING}")
STRING(REGEX REPLACE "\n" "\\\\n\"\n\"" CCODE "${ESCAPEQUOTES}")
SET(LICENSEAGREEMENT "const char f_pLicenseAgreement[]=\n\"${CCODE}\";")
FILE(WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/licenseagreement.h" "${LICENSEAGREEMENT}")

# Additional modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")


#
# Include paths
#


#
# Sources
#


#
# Binaries
#


#
# Subdirectories
#

ADD_SUBDIRECTORY(qt)


#
# Installation
#


#
# CMakeLists.txt
#
