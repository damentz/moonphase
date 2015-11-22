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

INCLUDE(CMakeDependentOption)

# Only allow build in Release version.
STRING(TOLOWER "${CMAKE_BUILD_TYPE}" BUILDTYPELC)
IF("${BUILDTYPELC}" STREQUAL "release")
  SET(BUILDRELEASEFLAG ON)
ELSE()
  SET(BUILDRELEASEFLAG OFF)
ENDIF()

# Options.
CMAKE_DEPENDENT_OPTION(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN
    "Build the ${TOOLBOX_DISPLAYNAME} Qt Designer plugin." OFF
    "BUILDRELEASEFLAG" OFF)
OPTION(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGINDOCUMENTATION
    "Build the ${TOOLBOX_DISPLAYNAME} Qt Designer plugin documentation.")


#
# Configuration
#

# Subproject name.
SET(SUBPROJECTNAME "${PROJECT_NAME}designer")

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN)
  # Need Qt4.
  IF(NOT QT4_FOUND)
    FIND_PACKAGE(Qt4 REQUIRED)
    INCLUDE(${QT_USE_FILE})
  ENDIF()

  ADD_DEFINITIONS(${DEFINE_PREFIX}BUILD_PLUGIN)
ENDIF()

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGINDOCUMENTATION)
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

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN)
  INCLUDE_DIRECTORIES("${QT_QTDESIGNER_INCLUDE_DIR}")
ENDIF()


#
# Sources
#

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN)
  INCLUDE("${CMAKE_CURRENT_LIST_DIR}/../widgets/toolboxqtwidgets.cmake")
  SET(TOOLBOXQTDESIGNERPLUGIN_SOURCES
      "${CMAKE_CURRENT_LIST_DIR}/sources/aboutwidgetplugin.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/sources/debuglogviewerwidgetplugin.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/sources/messagelogviewerwidgetplugin.cpp"
      "${CMAKE_CURRENT_LIST_DIR}/sources/toolboxwidgetsinterface.cpp")
  SET(TOOLBOXQTDESIGNERPLUGIN_HEADERS
      "${CMAKE_CURRENT_LIST_DIR}/sources/aboutwidgetplugin.h"
      "${CMAKE_CURRENT_LIST_DIR}/sources/debuglogviewerwidgetplugin.h"
      "${CMAKE_CURRENT_LIST_DIR}/sources/messagelogviewerwidgetplugin.h"
      "${CMAKE_CURRENT_LIST_DIR}/sources/toolboxwidgetsinterface.h")
  SET(TOOLBOXQTDESIGNERPLUGIN_FORMS )
  SET(TOOLBOXQTDESIGNERPLUGIN_RESOURCES )
  QT4_WRAP_CPP(TOOLBOXQTDESIGNERPLUGIN_MOC ${TOOLBOXQTDESIGNERPLUGIN_HEADERS})
  QT4_WRAP_UI(TOOLBOXQTDESIGNERPLUGIN_UI ${TOOLBOXQTDESIGNERPLUGIN_FORMS})
  QT4_ADD_RESOURCES(TOOLBOXQTDESIGNERPLUGIN_QRC ${TOOLBOXQTDESIGNERPLUGIN_RESOURCES})
  SET(TOOLBOXQTDESIGNERPLUGIN_FILES
      ${TOOLBOXQTDESIGNERPLUGIN_SOURCES}
      ${TOOLBOXQTDESIGNERPLUGIN_HEADERS}
      ${TOOLBOXQTDESIGNERPLUGIN_MOC}
      ${TOOLBOXQTDESIGNERPLUGIN_UI}
      ${TOOLBOXQTDESIGNERPLUGIN_QRC})
ENDIF()


#
# Binaries
#

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN)
  # Create the library.
  ADD_LIBRARY(${PROJECT_NAME} SHARED
      ${TOOLBOXQTWIDGETS_FILES}
      ${TOOLBOXQTDESIGNERPLUGIN_FILES})
  # Anything undefined causes an error.
  TARGET_LINK_LIBRARIES(${PROJECT_NAME} "-Wl,-z,defs" QtCore QtGui)
ENDIF()

# Build the library documentation.
IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGINDOCUMENTATION)
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

IF(OPTION_TOOLBOX_BUILDQTDESIGNERPLUGIN)
  INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/lib${PROJECT_NAME}.so"
      DESTINATION "${QT_PLUGINS_DIR}/designer/")
ENDIF()


#
# CMakeLists.txt
#
