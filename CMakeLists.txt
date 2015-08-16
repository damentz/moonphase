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

# CMake minimum version.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name.
PROJECT(moonphase)

# Load user preferences.
INCLUDE(${CMAKE_SOURCE_DIR}/preferences.cmake OPTIONAL)

# Build information.
SET(MAJORVERSION_NUMBER 0)
SET(MINORVERSION_NUMBER 2)
SET(PATCHVERSION_NUMBER 3)
SET(DISPLAYNAME_STRING "Moon Phase")
SET(OWNER_STRING "Alan Wise")
SET(DESCRIPTION_STRING "Displays the phase of the moon in the system tray.")
SET(COPYRIGHTNOTICE_STRING
    "Copyright (C) 2014 ${OWNER_STRING}.")
SET(WEBSITE_STRING "http://sourceforge.net/projects/moonphase/")
SET(LICENSE_STRING
    "License GPLv3: GNU GPL version 3 or later <http://gnu.org/licenses/>.")
SET(PACKAGE_NAME "moonphase")

# Convert license agreement to include file.
FILE(READ "${PROJECT_SOURCE_DIR}/COPYING" COPYING)
STRING(REGEX REPLACE "\"" "\\\\\"" ESCAPEQUOTES "${COPYING}")
STRING(REGEX REPLACE "\n" "\\\\n\"\n\"" CCODE "${ESCAPEQUOTES}")
SET(LICENSEAGREEMENT "const char f_pLicenseAgreement[]=\n\"${CCODE}\";")
FILE(WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/licenseagreement.h" "${LICENSEAGREEMENT}")

IF(WIN32)
  ADD_DEFINITIONS(-DUNICODE)  # Needed for qtsingleapplication (qlockedfile_win.cpp)
ENDIF()

# Install information.
IF(UNIX)
  SET(INSTALL_BINARYDIRECTORY "bin")
  SET(INSTALL_ICONDIRECTORY "share/icons")
  SET(INSTALL_IMAGEDIRECTORY "share/moonphase")
ELSEIF(WIN32 AND MSVC)
  SET(INSTALL_BINARYDIRECTORY ".")
  SET(INSTALL_ICONDIRECTORY ".")
  SET(INSTALL_IMAGEDIRECTORY ".")
ELSE()
  MESSAGE(FATAL_ERROR
      "Unknown build configuration. CMakeLists.txt needs to be updated!")
ENDIF()

# Default to Release build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF()


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

IF(BUILD_EXECUTABLE)
  FILE(GLOB MOONPHASE_IMAGES "${CMAKE_SOURCE_DIR}/images/*")
  INSTALL(FILES ${MOONPHASE_IMAGES} DESTINATION ${INSTALL_IMAGEDIRECTORY})
ENDIF()


#
# CMakeLists.txt
#
