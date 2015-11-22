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

# Need Qt4.
IF(NOT QT4_FOUND)
  FIND_PACKAGE(Qt4 REQUIRED)
  INCLUDE(${QT_USE_FILE})
ENDIF()


#
# Include paths
#

INCLUDE_DIRECTORIES(
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/generic/sources/"
    "${PROJECT_SOURCE_DIR}/qt/widgets/sources/")


#
# Sources
#

SET(TOOLBOXQTWIDGETS_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/sources/aboutwidget.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/sources/debugtools.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/sources/debuglogviewerwidget.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/sources/messagelogviewerwidget.cpp")
SET(TOOLBOXQTWIDGETS_HEADERS
    "${CMAKE_CURRENT_LIST_DIR}/sources/aboutwidget.h"
    "${CMAKE_CURRENT_LIST_DIR}/sources/debugtools.h"
    "${CMAKE_CURRENT_LIST_DIR}/sources/debugtools_private.h"
    "${CMAKE_CURRENT_LIST_DIR}/sources/debuglogviewerwidget.h"
    "${CMAKE_CURRENT_LIST_DIR}/sources/messagelogviewerwidget.h")
SET(TOOLBOXQTWIDGETS_FORMS
    "${CMAKE_CURRENT_LIST_DIR}/forms/aboutwidget.ui"
    "${CMAKE_CURRENT_LIST_DIR}/forms/debugconsoledialog.ui"
    "${CMAKE_CURRENT_LIST_DIR}/forms/debugconsoleoptionsdialog.ui"
    "${CMAKE_CURRENT_LIST_DIR}/forms/debuglogviewerwidget.ui"
    "${CMAKE_CURRENT_LIST_DIR}/forms/messagelogviewerwidget.ui")
SET(TOOLBOXQTWIDGETS_RESOURCES
    "${CMAKE_CURRENT_LIST_DIR}/resources/debugconsole.qrc")
QT4_WRAP_CPP(TOOLBOXQTWIDGETS_MOC ${TOOLBOXQTWIDGETS_HEADERS})
QT4_WRAP_UI(TOOLBOXQTWIDGETS_UI ${TOOLBOXQTWIDGETS_FORMS})
QT4_ADD_RESOURCES(TOOLBOXQTWIDGETS_QRC ${TOOLBOXQTWIDGETS_RESOURCES})
SET(TOOLBOXQTWIDGETS_FILES
    ${TOOLBOXQTWIDGETS_SOURCES}
    ${TOOLBOXQTWIDGETS_HEADERS}
    ${TOOLBOXQTWIDGETS_MOC}
    ${TOOLBOXQTWIDGETS_UI}
    ${TOOLBOXQTWIDGETS_QRC})


#
# Binaries
#


#
# Subdirectories
#


#
# Installation
#


#
# CMakeLists.txt
#
