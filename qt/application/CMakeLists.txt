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


INCLUDE(ExternalProject)

# Options.
OPTION(OPTION_MOONPHASE_BUILDQTAPPLICATION
    "Build the Qt ${MOONPHASE_DISPLAYNAME} application." ON)
OPTION(OPTION_MOONPHASE_BUILDQTAPPLICATIONDOCUMENTATION
    "Build the Qt ${MOONPHASE_DISPLAYNAME} application documentation." OFF)


#
# Configuration
#

# Name and version.
SET(MOONPHASEQT_EXECUTABLENAME "${PROJECT_NAME}-qt")

IF(OPTION_MOONPHASE_BUILDQTAPPLICATION)
  # Trigger installation of images during install.
  SET(BUILD_EXECUTABLE 1 CACHE INTERNAL
      "Trigger installation of images during install.")
  # Need Qt4.
  FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtNetwork)
  INCLUDE(${QT_USE_FILE})
  # Create a configuration file.
  CONFIGURE_FILE(
      "${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.in"
      "${CMAKE_CURRENT_BINARY_DIR}/config.h")
  # Create the desktop entry
  IF(UNIX)
    CONFIGURE_FILE(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${MOONPHASEQT_EXECUTABLENAME}.desktop.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${MOONPHASEQT_EXECUTABLENAME}.desktop")
  ENDIF()
  # Check for debug mode.
  STRING(TOLOWER "${CMAKE_BUILD_TYPE}" BUILDTYPELC)
  IF("${BUILDTYPELC}" STREQUAL "debug")
    ADD_DEFINITIONS(-DDEBUG)
  ENDIF()
ENDIF()

IF(OPTION_MOONPHASE_BUILDQTAPPLICATIONDOCUMENTATION)
  # Need Doxygen.
  FIND_PACKAGE(Doxygen REQUIRED)
  # Create the Doxygen file.
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in"
      "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${MOONPHASEQT_EXECUTABLENAME}")
ENDIF()


#
# Include paths
#

IF(OPTION_MOONPHASE_BUILDQTAPPLICATION)
  INCLUDE_DIRECTORIES(
      "${CMAKE_BINARY_DIR}"
      "${CMAKE_CURRENT_BINARY_DIR}"
      "${CMAKE_SOURCE_DIR}/qt/qt-solutions/qtsingleapplication/src/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwbuttonlineedit/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwcolorbutton/"
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/qwwfilechooser/")
ENDIF()


#
# Sources
#

IF(OPTION_MOONPHASE_BUILDQTAPPLICATION)
  INCLUDE("${CMAKE_SOURCE_DIR}/common/common.cmake")
  SET(MOONPHASEQT_SOURCES
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/${PROJECT_NAME}qt.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/controlpaneldialog.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/moonanimation.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/../qt-solutions/qtsingleapplication/src/qtlocalpeer.cpp"
      "${CMAKE_CURRENT_SOURCE_DIR}/../qt-solutions/qtsingleapplication/src/qtsingleapplication.cpp")
  SET(MOONPHASEQT_HEADERS
      "${CMAKE_CURRENT_SOURCE_DIR}/sources/controlpaneldialog.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/../qt-solutions/qtsingleapplication/src/qtlocalpeer.h"
      "${CMAKE_CURRENT_SOURCE_DIR}/../qt-solutions/qtsingleapplication/src/qtsingleapplication.h")
  SET(MOONPHASEQT_FORMS
      "${CMAKE_CURRENT_SOURCE_DIR}/forms/controlpaneldialog.ui"
      "${CMAKE_CURRENT_SOURCE_DIR}/forms/testwidget.ui")
  SET(MOONPHASEQT_RESOURCES
      "${CMAKE_CURRENT_SOURCE_DIR}/resources/${PROJECT_NAME}qt.qrc")
  QT4_WRAP_CPP(MOONPHASEQT_MOC ${MOONPHASEQT_HEADERS})
  QT4_WRAP_UI(MOONPHASEQT_UI ${MOONPHASEQT_FORMS})
  QT4_ADD_RESOURCES(MOONPHASEQT_QRC ${MOONPHASEQT_RESOURCES})
  SET(MOONPHASEQT_FILES
      ${MOONPHASEQT_SOURCES}
      ${MOONPHASEQT_MOC}
      ${MOONPHASEQT_UI}
      ${MOONPHASEQT_QRC})
  IF(WIN32)
    SET(MOONPHASEQT_FILES ${MOONPHASEQT_FILES}
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/${PROJECT_NAME}-qt.rc")
  ENDIF()
ENDIF()


#
# Binaries
#

IF(OPTION_MOONPHASE_BUILDQTAPPLICATION)
  # moonphase-qt depends on an external library that is built from source code.
  IF(UNIX)
    SET(CONFIGURE_COMMAND
        "${CMAKE_CURRENT_SOURCE_DIR}/../wwwidgets/cmake_configure_command_${BUILDTYPELC}")
    SET(BUILD_COMMAND "$(MAKE)")
    SET(GUI_TYPE )
    SET(WWWIDGETS_LIBRARYPATHNAME ".")
    SET(OS_LIBRARIES m)
  ELSEIF(WIN32 AND MSVC)
    SET(CONFIGURE_COMMAND
        "${CMAKE_CURRENT_SOURCE_DIR}/../wwwidgets/cmake_configure_command_${BUILDTYPELC}.bat")
    SET(BUILD_COMMAND nmake)
    SET(GUI_TYPE WIN32)
    SET(WWWIDGETS_LIBRARYPATHNAME "${BUILDTYPELC}")
    SET(OS_LIBRARIES imm32.lib winmm.lib ws2_32.lib ${QT_QTMAIN_LIBRARY})
  ELSE()
    MESSAGE(FATAL_ERROR
        "Unknown build configuration. CMakeLists.txt needs to be updated!")
  ENDIF()
  SET(WWWIDGETS_LIBRARYPATHNAME
      "${WWWIDGETS_LIBRARYPATHNAME}/${CMAKE_STATIC_LIBRARY_PREFIX}wwwidgets4")
  IF(WIN32 AND MSVC)
    IF("${BUILDTYPELC}" STREQUAL "debug")
      SET(WWWIDGETS_LIBRARYPATHNAME "${WWWIDGETS_LIBRARYPATHNAME}d")
    ENDIF()
  ENDIF()
  SET(WWWIDGETS_LIBRARYPATHNAME "${WWWIDGETS_LIBRARYPATHNAME}${CMAKE_STATIC_LIBRARY_SUFFIX}")
  EXTERNALPROJECT_ADD(wwwidgets
      URL "http://www.wysota.eu.org/wwwidgets/wwWidgets-1.0.tar.gz"
      URL_HASH MD5=e8f8cbe75ee409f18ba44f786bcc438c
      DOWNLOAD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../wwwidgets/"
      SOURCE_DIR "${CMAKE_BINARY_DIR}/wwwidgets/"
      BINARY_DIR "${CMAKE_BINARY_DIR}/wwwidgets/"
      PATCH_COMMAND ""
      CONFIGURE_COMMAND ${CONFIGURE_COMMAND}
      BUILD_COMMAND ${BUILD_COMMAND}
      INSTALL_COMMAND "")

  # Create the executable
  ADD_EXECUTABLE(
      ${MOONPHASEQT_EXECUTABLENAME} ${GUI_TYPE}
      ${TOOLBOXGENERIC_FILES}
      ${COMMON_FILES}
      ${MOONPHASEQT_FILES})
  TARGET_LINK_LIBRARIES(
      ${MOONPHASEQT_EXECUTABLENAME}
      toolboxgeneric
      toolboxqtwidgets
      "${CMAKE_BINARY_DIR}/wwwidgets/widgets/${WWWIDGETS_LIBRARYPATHNAME}"
      ${OS_LIBRARIES}
      ${QT_LIBRARIES})
  ADD_DEPENDENCIES(${MOONPHASEQT_EXECUTABLENAME} wwwidgets)

  # Set up for cpack.
  IF(WIN32)
    # Build using nmake. DOESN'T WORK!
    SET(CPACK_CMAKE_GENERATOR "NMake Makefiles")

    # Package in an NSIS installer. DOESN'T WORK!
    SET(CPACK_GENERATOR "NSIS")

    # Options for the NSIS generator.
    INCLUDE("${CMAKE_SOURCE_DIR}/windows/nsis.cmake")
    #SET(CPACK_PROJECT_CONFIG_FILE "${CMAKE_SOURCE_DIR}/windows/nsis.cmake")
      # Crashes cpack under Windows XP.

    INCLUDE(CPack)
  ENDIF()
ENDIF()

# Build the library documentation.
IF(OPTION_MOONPHASE_BUILDQTAPPLICATIONDOCUMENTATION)
  ADD_CUSTOM_TARGET(doc-${MOONPHASEQT_EXECUTABLENAME} ALL
      COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${MOONPHASEQT_EXECUTABLENAME}"
      SOURCES "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-${MOONPHASEQT_EXECUTABLENAME}")
ENDIF()


#
# Subdirectories
#


#
# Installation
#

IF(OPTION_MOONPHASE_BUILDQTAPPLICATION)
  INSTALL(TARGETS "${MOONPHASEQT_EXECUTABLENAME}" RUNTIME
      DESTINATION ${INSTALL_BINARYDIRECTORY})
  IF(UNIX)
    # Install an icon.
    INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/resources/${PROJECT_NAME}-qt.xpm"
        DESTINATION share/icons)
    # Install the desktop file.
    INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/${MOONPHASEQT_EXECUTABLENAME}.desktop"
        DESTINATION share/applications)
  ENDIF()
  IF(WIN32)
    # Install README
    INSTALL(FILES "${CMAKE_SOURCE_DIR}/windows/README.txt"
        DESTINATION .)
  ENDIF()
ENDIF()


#
# CMakeLists.txt
#
