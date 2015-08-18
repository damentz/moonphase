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
SET(CPACK_PACKAGE_VERSION_MAJOR ${MOONPHASE_MAJORVERSION})
SET(CPACK_PACKAGE_VERSION_MINOR ${MOONPHASE_MINORVERSION})
SET(CPACK_PACKAGE_VERSION_PATCH ${MOONPHASE_PATCHVERSION})

# Base name of installer.
SET(CPACK_PACKAGE_NAME ${MOONPHASEQT_EXECUTABLENAME})

# Installion target directory.
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Moon Phase (Qt)")

# Menu name under Programs.
SET(CPACK_NSIS_MENU_LINKS "${MOONPHASEQT_EXECUTABLENAME}" "${MOONPHASEQT_EXECUTABLENAME}")

# License file (displayed during install).
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")

# Create Startup menu item (and delete it on uninstall).
SET(CPACK_NSIS_CREATE_ICONS_EXTRA "
    CreateShortCut '$SMSTARTUP\\\\${MOONPHASEQT_EXECUTABLENAME}.lnk' '$INSTDIR\\\\${MOONPHASEQT_EXECUTABLENAME}${CMAKE_EXECUTABLE_SUFFIX}'
    CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\README.lnk' '$INSTDIR\\\\README.txt'
    ")
SET(CPACK_NSIS_DELETE_ICONS_EXTRA "
    Delete '$SMSTARTUP\\\\${MOONPHASEQT_EXECUTABLENAME}.lnk'
    Delete '$SMPROGRAMS\\\\$MUI_TEMP\\\\README.lnk'
    ")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "Exec 'notepad.exe README.txt'")

# Run the executable after the install.
SET(CPACK_NSIS_MUI_FINISHPAGE_RUN
    "..\\\\${MOONPHASEQT_EXECUTABLENAME}${CMAKE_EXECUTABLE_SUFFIX}")


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
