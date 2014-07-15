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

INCLUDE(CMakeDependentOption)
INCLUDE(ExternalProject)

OPTION(OPTION_MOONPHASE_BUILDMOONPHASEQT
    "Build the Qt Moon Phase application." ON)
OPTION(OPTION_MOONPHASE_BUILDMOONPHASEQTDOCUMENTATION
    "Build the Qt Moon Phase application documentation." OFF)


#
# Configuration
#

# Name and version.
SET(EXECUTABLENAME_STRING "moonphase-qt")

IF(OPTION_MOONPHASE_BUILDMOONPHASEQT)
  # Trigger installation of images during install..
  SET(BUILD_EXECUTABLE 1 CACHE INTERNAL
      "Trigger installation of images during install.")
  # Need Qt4.
  FIND_PACKAGE(Qt4 REQUIRED)
  INCLUDE(${QT_USE_FILE})
  # Create a configuration file.
  CONFIGURE_FILE(
      "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in"
      "${CMAKE_CURRENT_BINARY_DIR}/config.h")
  # Check for debug mode.
  STRING(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_TYPE)
  IF("${BUILD_TYPE}" STREQUAL "" OR "${BUILD_TYPE}" STREQUAL "DEBUG")
    ADD_DEFINITIONS(-DDEBUG)
  ENDIF("${BUILD_TYPE}" STREQUAL "" OR "${BUILD_TYPE}" STREQUAL "DEBUG")
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQT)

IF(OPTION_MOONPHASE_BUILDMOONPHASEQTDOCUMENTATION)
  # Check for Doxygen
  FIND_PACKAGE(Doxygen REQUIRED)
  # Create the Doxygen file.
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in"
      "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQTDOCUMENTATION)


#
# Include paths
#

IF(OPTION_MOONPHASE_BUILDMOONPHASEQT)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_BINARY_DIR}"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwbuttonlineedit/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwcolorbutton/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwfilechooser/")
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQT)


#
# Sources
#

IF(OPTION_MOONPHASE_BUILDMOONPHASEQT)
  INCLUDE("${CMAKE_SOURCE_DIR}/common/common.cmake")
  SET(MOONPHASEQT_SOURCES
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/moonphaseqt.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/controlpaneldialog.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/moonanimation.cpp")
  SET(MOONPHASEQT_HEADERS
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/controlpaneldialog.h")
  SET(MOONPHASEQT_FORMS
      "${CMAKE_CURRENT_SOURCE_DIR}/forms/controlpaneldialog.ui")
  SET(MOONPHASEQT_RESOURCES
      "${CMAKE_CURRENT_SOURCE_DIR}/resources/moonphaseqt.qrc")
  QT4_WRAP_CPP(MOONPHASEQT_MOC ${MOONPHASEQT_HEADERS})
  QT4_WRAP_UI(MOONPHASEQT_UI ${MOONPHASEQT_FORMS})
  QT4_ADD_RESOURCES(MOONPHASEQT_QRC ${MOONPHASEQT_RESOURCES})
  SET(MOONPHASEQT_FILES
      ${MOONPHASEQT_SOURCES}
      ${MOONPHASEQT_MOC}
      ${MOONPHASEQT_UI}
      ${MOONPHASEQT_QRC})
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQT)


#
# Binaries
#

IF(OPTION_MOONPHASE_BUILDMOONPHASEQT)
  # moonphase-qt depends on an external library that is built from source code.
  IF(UNIX)
    SET(CONFIGURE_COMMAND
        "${CMAKE_CURRENT_SOURCE_DIR}/wwwidgets/cmake_configure_command.sh")
    SET(BUILD_COMMAND "$(MAKE)")
  ELSEIF(WIN32 AND MSVC)
    SET(CONFIGURE_COMMAND
        "${CMAKE_CURRENT_SOURCE_DIR}/wwwidgets/cmake_configure_command.bat")
    SET(BUILD_COMMAND nmake.exe)
  ELSE()
    MESSAGE(FATAL_ERROR
        "Unknown build configuration. CMakeLists.txt needs to be updated!")
  ENDIF()
  SET(FNAME "${CMAKE_STATIC_LIBRARY_PREFIX}wwwidgets4")
  IF(WIN32)
    IF(CMAKE_STATIC_LIBRARY_PREFIX EQUAL "Debug")
      SET(FNAME "${FNAME}d")
    ENDIF()
  ENDIF()
  SET(FNAME "${FNAME}${CMAKE_STATIC_LIBRARY_SUFFIX}")
  EXTERNALPROJECT_ADD(wwwidgets
      URL "http://www.wysota.eu.org/wwwidgets/wwWidgets-1.0.tar.gz"
      URL_HASH MD5=e8f8cbe75ee409f18ba44f786bcc438c
      DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/wwwidgets/"
      SOURCE_DIR "${CMAKE_BINARY_DIR}/wwwidgets/"
      BINARY_DIR "${CMAKE_BINARY_DIR}/wwwidgets/"
      PATCH_COMMAND ""
      CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
      BUILD_COMMAND ${BUILD_COMMAND}
      INSTALL_COMMAND "")

  ADD_EXECUTABLE(
      ${EXECUTABLENAME_STRING}
      ${TOOLBOXGENERIC_FILES}
      ${COMMON_FILES}
      ${MOONPHASEQT_FILES})
  TARGET_LINK_LIBRARIES(
      ${EXECUTABLENAME_STRING}
      -lm 
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/${FNAME}"
      ${QT_LIBRARIES})
  ADD_DEPENDENCIES(${EXECUTABLENAME_STRING} wwwidgets)
  ADD_LIBRARY(wwwidgets4 STATIC IMPORTED)
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQT)

IF(OPTION_MOONPHASE_BUILDMOONPHASEQTDOCUMENTATION)
  ADD_CUSTOM_TARGET(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    SOURCES "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQTDOCUMENTATION)


#
# Subdirectories
#


#
# Installation
#

IF(OPTION_MOONPHASE_BUILDMOONPHASEQT)
  INSTALL(TARGETS "${EXECUTABLENAME_STRING}" RUNTIME DESTINATION bin)
ENDIF(OPTION_MOONPHASE_BUILDMOONPHASEQT)


#
# CMakeLists.txt
#
