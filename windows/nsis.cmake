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

# Version.
SET(CPACK_PACKAGE_VERSION_MAJOR ${MAJORVERSION_NUMBER})
SET(CPACK_PACKAGE_VERSION_MINOR ${MINORVERSION_NUMBER})
SET(CPACK_PACKAGE_VERSION_PATCH ${PATCHVERSION_NUMBER})

# Base name of installer.
SET(CPACK_PACKAGE_NAME ${PACKAGE_NAME})

# Installion target directory.
SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${DISPLAYNAME_STRING})

# Menu name under Programs.
SET(CPACK_NSIS_MENU_LINKS "${EXECUTABLENAME_STRING}" "${EXECUTABLENAME_STRING}")

# License file (displayed during install).
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")

# Create Startup menu item (and delete it on uninstall).
SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
    CreateShortCut '$SMSTARTUP\\\\${EXECUTABLENAME_STRING}.lnk' '$INSTDIR\\\\${EXECUTABLENAME_STRING}${CMAKE_EXECUTABLE_SUFFIX}'
    CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\README.lnk' '$INSTDIR\\\\README.txt'
    ")
SET(CPACK_NSIS_DELETE_ICONS_EXTRA "
    Delete '$SMSTARTUP\\\\${EXECUTABLENAME_STRING}.lnk'
    Delete '$SMPROGRAMS\\\\$MUI_TEMP\\\\README.lnk'
    ")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "Exec 'notepad.exe README.txt'")

# Run the executable after the install.
SET(CPACK_NSIS_MUI_FINISHPAGE_RUN
    "..\\\\${EXECUTABLENAME_STRING}${CMAKE_EXECUTABLE_SUFFIX}")


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


#
# Installation
#


#
# CMakeLists.txt
#
