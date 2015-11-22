#
# This file is part of toolbox.
# Copyright (C) 2008-2015 by Alan Wise (alanwise@users.sourceforge.net)
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
PROJECT(toolbox)

# Load user preferences.
INCLUDE("${CMAKE_SOURCE_DIR}/preferences.cmake" OPTIONAL)

# Build information.
SET(TOOLBOX_MAJORVERSION "0")
SET(TOOLBOX_MINORVERSION "2")
SET(TOOLBOX_PATCHVERSION "0")
SET(TOOLBOX_DISPLAYNAME "Toolbox")
SET(TOOLBOX_OWNERNAME "Alan Wise")
SET(TOOLBOX_COPYRIGHTNOTICE
    "Copyright (C) 2008-2015 ${TOOLBOX_OWNERNAME}.")
SET(TOOLBOX_WEBSITE "http://sourceforge.net/projects/awtoolbox/")
SET(TOOLBOX_LICENSE
    "License GPLv3: GNU GPL version 3 or later <http://gnu.org/licenses/>.")

# Additional compiler options and settings.
IF(UNIX)
  SET(DEFINE_PREFIX -D)
  ADD_DEFINITIONS(-Wall)
  ADD_DEFINITIONS(-D_GNU_SOURCE) # Need this define for certain prototypes.
ELSEIF(WIN32 AND MSVC)
  SET(DEFINE_PREFIX /D)
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

ADD_SUBDIRECTORY(generic)
ADD_SUBDIRECTORY(qt/utilities)
ADD_SUBDIRECTORY(qt/widgets)
ADD_SUBDIRECTORY(qt/designer)


#
# Installation
#


#
# CMakeLists.txt
#
