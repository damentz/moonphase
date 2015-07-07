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
OPTION(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARY
    "Build the ${TOOLBOX_DISPLAYNAME} Qt widgets library." ON)
OPTION(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARYDOCUMENTATION
    "Build the ${TOOLBOX_DISPLAYNAME} Qt widgets library documentation." OFF)


#
# Configuration
#

# Subproject name.
SET(SUBPROJECTNAME ${PROJECT_NAME}qtwidgets)
SET(TOOLBOXQTWIDGETS_DESCRIPTION
    "A Qt specific collection of code and data which can be used across multiple projects.")

IF(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARY)
  # Need Qt4.
  IF(NOT QT4_FOUND)
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
  ENDIF()
ENDIF()

IF(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARYDOCUMENTATION)
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

IF(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARY)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/toolboxqtwidgets.cmake")
ENDIF()

#
# Binaries
#

IF(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARY)
  # Create the library.
  ADD_LIBRARY(${SUBPROJECTNAME} STATIC
      ${TOOLBOXQTWIDGETS_FILES})
ENDIF()

# Build the library documentation.
IF(OPTION_TOOLBOX_BUILDQTWIDGETSLIBRARYDOCUMENTATION)
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
