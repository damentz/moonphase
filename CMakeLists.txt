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

# CMake minimum version.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Project name.
PROJECT(moonphase)

# Load user preferences.
INCLUDE("${CMAKE_SOURCE_DIR}/preferences.cmake" OPTIONAL)

# Build information.
SET(MOONPHASE_MAJORVERSION "0")
SET(MOONPHASE_MINORVERSION "3")
SET(MOONPHASE_PATCHVERSION "1")
SET(MOONPHASE_DISPLAYNAME "Moon Phase")
SET(MOONPHASE_OWNER "Alan Wise")
SET(MOONPHASE_DESCRIPTION
    "Displays the phase of the moon in the system tray.")
SET(MOONPHASE_COPYRIGHTNOTICE
    "Copyright (C) 2014-2015 ${MOONPHASE_OWNER}.")
SET(MOONPHASE_WEBSITE "http://sourceforge.net/projects/moonphase/")
SET(MOONPHASE_LICENSE
    "License GPLv3: GNU GPL version 3 or later <http://gnu.org/licenses/>.")
SET(PACKAGE_NAME "moonphase")

# Convert license agreement to include file.
FILE(READ "${PROJECT_SOURCE_DIR}/COPYING" COPYING)
STRING(REGEX REPLACE "\"" "\\\\\"" ESCAPEQUOTES "${COPYING}")
STRING(REGEX REPLACE "\n" "\\\\n\"\n\"" CCODE "${ESCAPEQUOTES}")
SET(LICENSEAGREEMENT "const char f_pLicenseAgreement[]=\n\"${CCODE}\";")
FILE(WRITE
    "${CMAKE_CURRENT_BINARY_DIR}/licenseagreement.h" "${LICENSEAGREEMENT}")

# Additional compiler options and settings.
IF(UNIX)
  SET(DEFINE_PREFIX -D)
  ADD_DEFINITIONS(-Wall)
  ADD_DEFINITIONS(${DEFINE_PREFIX}_GNU_SOURCE)
      # Need this define for certain prototypes.
ELSEIF(WIN32 AND MSVC)
  SET(DEFINE_PREFIX /D)
  ADD_DEFINITIONS(${DEFINE_PREFIX}UNICODE)
      # Needed for qtsingleapplication (qlockedfile_win.cpp)
ELSE()
  MESSAGE(FATAL_ERROR
      "Unknown build configuration. CMakeLists.txt needs to be updated!")
ENDIF()

# If debug mode, set debug definition.
STRING(TOLOWER "${CMAKE_BUILD_TYPE}" BUILDTYPELC)
IF("${BUILDTYPELC}" STREQUAL "debug")
  ADD_DEFINITIONS(${DEFINE_PREFIX}DEBUG)
ENDIF()

# Default to Release build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF()

# Install information.
IF(UNIX)
  SET(INSTALL_BINARYDIRECTORY "bin")
  SET(INSTALL_ICONDIRECTORY "share/icons")
  SET(INSTALL_IMAGEDIRECTORY "share/${PROJECT_NAME}")
ELSEIF(WIN32 AND MSVC)
  SET(INSTALL_BINARYDIRECTORY ".")
  SET(INSTALL_ICONDIRECTORY ".")
  SET(INSTALL_IMAGEDIRECTORY ".")
ELSE()
  MESSAGE(FATAL_ERROR
      "Unknown build configuration. CMakeLists.txt needs to be updated!")
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

ADD_SUBDIRECTORY(qt/application)
ADD_SUBDIRECTORY(toolbox)


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
