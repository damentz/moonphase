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
OPTION(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARY
    "Build the ${TOOLBOX_DISPLAYNAME} Qt Utilities library." ON)
OPTION(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARYDOCUMENTATION
    "Build the ${TOOLBOX_DISPLAYNAME} Qt Utilities library documentation." OFF)


#
# Configuration
#

# Subproject name.
SET(SUBPROJECTNAME ${PROJECT_NAME}qtutilities)
SET(TOOLBOXQTUTILITIES_DESCRIPTION
    "A Qt specific collection of code and data which can be used across multiple projects.")

IF(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARY)
  # Need Qt4.
  IF(NOT QT4_FOUND)
    FIND_PACKAGE(Qt4 REQUIRED QtCore QtNetwork)
    INCLUDE(${QT_USE_FILE})
  ENDIF()
ENDIF()

IF(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARYDOCUMENTATION)
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

INCLUDE_DIRECTORIES(
#    "${CMAKE_CURRENT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/generic/sources/")
#    "${PROJECT_SOURCE_DIR}/qt/widgets/sources/")


#
# Sources
#

IF(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARY)
  SET(TOOLBOXQTUTILITIES_SOURCES
      "${CMAKE_CURRENT_LIST_DIR}/sources/updatenotifier.cpp")
  SET(TOOLBOXQTUTILITIES_HEADERS
      "${CMAKE_CURRENT_LIST_DIR}/sources/updatenotifier.h")
  SET(TOOLBOXQTUTILITIES_FORMS )
  SET(TOOLBOXQTUTILITIES_RESOURCES )
  QT4_WRAP_CPP(TOOLBOXQTUTILITIES_MOC ${TOOLBOXQTUTILITIES_HEADERS})
  QT4_WRAP_UI(TOOLBOXQTUTILITIES_UI ${TOOLBOXQTUTILITIES_FORMS})
  QT4_ADD_RESOURCES(TOOLBOXQTUTILITIES_QRC ${TOOLBOXQTUTILITIES_RESOURCES})
  SET(TOOLBOXQTUTILITIES_FILES
      ${TOOLBOXQTUTILITIES_SOURCES}
      ${TOOLBOXQTUTILITIES_HEADERS}
      ${TOOLBOXQTUTILITIES_MOC}
      ${TOOLBOXQTUTILITIES_UI}
      ${TOOLBOXQTUTILITIES_QRC})
ENDIF()


#
# Binaries
#

IF(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARY)
  # Create the library.
  ADD_LIBRARY(${SUBPROJECTNAME} STATIC
      ${TOOLBOXQTUTILITIES_FILES})
ENDIF()

# Build the library documentation.
IF(OPTION_TOOLBOX_BUILDQTUTILITIESLIBRARYDOCUMENTATION)
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
