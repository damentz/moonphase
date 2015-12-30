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


# Options.
OPTION(OPTION_TOOLBOX_BUILDGENERICLIBRARY 
    "Build the ${TOOLBOX_DISPLAYNAME} generic library." ON)
OPTION(OPTION_TOOLBOX_BUILDGENERICLIBRARYDOCUMENTATION
    "Build the ${TOOLBOX_DISPLAYNAME} generic library documentation." OFF)


#
# Configuration
#

# Subproject name.
SET(SUBPROJECTNAME "${PROJECT_NAME}generic")
SET(TOOLBOXGENERIC_DESCRIPTION
    "A generic collection of code and data which can be used across multiple projects.")

IF(OPTION_TOOLBOX_BUILDGENERICLIBRARY)
  SET(CMAKE_MODULE_PATH 
      ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")
  FIND_PACKAGE(MHASH)
  IF(MHASH_FOUND)
    ADD_DEFINITIONS(${DEFINE_PREFIX}USE_MHASH)
  ELSE()
    MESSAGE(WARNING "Mhash library not found! Checksum module will not be built.")
  ENDIF()
ENDIF()

IF(OPTION_TOOLBOX_BUILDGENERICLIBRARYDOCUMENTATION)
  # Need Doxygen.
  IF(NOT DOXYGEN_FOUND)
    FIND_PACKAGE(Doxygen REQUIRED)
  ENDIF()
  # Create the Doxygen file.
  CONFIGURE_FILE("${CMAKE_CURRENT_LIST_DIR}/cmake/Doxyfile.in"
      "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${SUBPROJECTNAME}")
ENDIF()


#
# Include paths
#


#
# Sources
#

IF(OPTION_TOOLBOX_BUILDGENERICLIBRARY)
  SET(TOOLBOXGENERIC_SOURCES
      ${CMAKE_CURRENT_LIST_DIR}/sources/debuglog.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/file.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/messagelog.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/pathnamelist.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/utility.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/versionstring.c
      ${CMAKE_CURRENT_LIST_DIR}/sources/visualstudio.c)
  IF(MHASH_FOUND)
    SET(TOOLBOXGENERIC_SOURCES ${TOOLBOXGENERIC_SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/sources/checksum.c)
  ENDIF()
ENDIF()


#
# Binaries
#

IF(OPTION_TOOLBOX_BUILDGENERICLIBRARY)
  # Create the library.
  ADD_LIBRARY(${SUBPROJECTNAME} STATIC
      ${TOOLBOXGENERIC_SOURCES})# ${MHASH_LIBRARIES})
ENDIF()

# Build the library documentation.
IF(OPTION_TOOLBOX_BUILDGENERICLIBRARYDOCUMENTATION)
  ADD_CUSTOM_TARGET(doc-${SUBPROJECTNAME} ALL
      COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${SUBPROJECTNAME}"
      SOURCES "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${SUBPROJECTNAME}")
ENDIF()


#
# Subdirectories
#


#
# Installation
#


#
# CMakeLists.txt
#
