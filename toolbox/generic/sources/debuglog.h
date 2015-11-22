/*
** This file is part of toolbox.
** Copyright (C) 2008-2015 by Alan Wise (alanwise@users.sourceforge.net)
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
*** \file debuglog.h
*** \brief Write debug information to a file.
*** \details This module provides the ability to write debug information to a
***   text file.
***
*** All functions should be accessed through the function wrapper macros. This
***   method of calling the function wrapper macros ensures that if the
***   module is not enabled, absolutely no code should be generated.
***
*** USE_DEBUGLOG must be defined for all files using the debug log
***   facilities.  It allows the debug log facilities to be enabled/disabled
***   on an individual file basis.  If defined before including
***   debuglog.h, the macros will generate code to call the functions.
***   If not defined, no code to call the functions is generated.
***
*** The logging can also be enabled/disabled at run time.
***
*** This module can indent according to function call depth.  To enable
***   this feature, place DEBUGLOG_LogIn() at the beginning of each
***   function, and DEBUGLOG_LogOut() at EACH exit point.
***
*** \warning This module is NOT thread safe.
**/


#ifndef   DEBUGLOG_H
#define   DEBUGLOG_H


/****
*****
***** INCLUDES
*****
****/


/****
*****
***** DEFINES
*****
****/

#ifndef   DEBUGLOG_NOWRAPPERMACROS

#ifdef    USE_DEBUGLOG

/**
*** \hideinitializer
*** \brief DebugLog_GetEnabledFlag() wrapper.
*** \details Wrapper macro for DebugLog_GetEnabledFlag().
*** \retval 0 Logging disabled.
*** \retval !0 Logging enabled.
**/
#define   DEBUGLOG_GetEnabledFlag()           DebugLog_GetEnabledFlag()
/**
*** \hideinitializer
*** \brief DebugLog_GetFilenamePointer wrapper.
*** \details Wrapper macro for DebugLog_GetFilenamePointer().
*** \returns Pointer to debug log filename.
**/
#define   DEBUGLOG_GetFilenamePointer()       DebugLog_GetFilenamePointer()
/**
*** \hideinitializer
*** \brief DebugLog_Initialize() wrapper.
*** \details Wrapper macro for DebugLog_Initialize().
*** \param enabledflag Enable flag.\n
***   0 - Disable logging.\n
***   !0 - Enable logging.
**/
#define   DEBUGLOG_Initialize(enabledflag)    DebugLog_Initialize(enabledflag)
/**
*** \hideinitializer
*** \brief DebugLog_LogIn() wrapper.
*** \details Wrapper macro for DebugLog_LogIn().
**/
#define   DEBUGLOG_LogIn()                    DebugLog_LogIn()
/**
*** \hideinitializer
*** \brief DebugLog_LogOut() wrapper.
*** \details Wrapper macro for DebugLog_LogOut().
**/
#define   DEBUGLOG_LogOut()                   DebugLog_LogOut()
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
**/
#define   DEBUGLOG_Printf0(format) \
              DebugLog_Printf(format"\n")
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
**/
#define   DEBUGLOG_Printf1(format,v1) \
              DebugLog_Printf(format"\n",v1)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
**/
#define   DEBUGLOG_Printf2(format,v1,v2) \
              DebugLog_Printf(format"\n",v1,v2)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
**/
#define   DEBUGLOG_Printf3(format,v1,v2,v3) \
              DebugLog_Printf(format"\n",v1,v2,v3)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
**/
#define   DEBUGLOG_Printf4(format,v1,v2,v3,v4)     \
              DebugLog_Printf(format"\n",v1,v2,v3,v4)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
**/
#define   DEBUGLOG_Printf5(format,v1,v2,v3,v4,v5)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
**/
#define   DEBUGLOG_Printf6(format,v1,v2,v3,v4,v5,v6)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
**/
#define   DEBUGLOG_Printf7(format,v1,v2,v3,v4,v5,v6,v7)   \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
*** \param v8 Variable #8.
**/
#define   DEBUGLOG_Printf8(format,v1,v2,v3,v4,v5,v6,v7,v8)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
*** \param v8 Variable #8.
*** \param v9 Variable #9.
**/
#define   DEBUGLOG_Printf9(format,v1,v2,v3,v4,v5,v6,v7,v8,v9)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8,v9)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
*** \param v8 Variable #8.
*** \param v9 Variable #9.
*** \param v10 Variable #10.
**/
#define   DEBUGLOG_Printf10(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
*** \param v8 Variable #8.
*** \param v9 Variable #9.
*** \param v10 Variable #10.
*** \param v11 Variable #11.
**/
#define   DEBUGLOG_Printf11(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)
/**
*** \hideinitializer
*** \brief DebugLog_Printf() wrapper.
*** \details Wrapper macro for DebugLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
*** \param v6 Variable #6.
*** \param v7 Variable #7.
*** \param v8 Variable #8.
*** \param v9 Variable #9.
*** \param v10 Variable #10.
*** \param v11 Variable #11.
*** \param v12 Variable #12.
**/
#define   DEBUGLOG_Printf12(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)
/**
*** \hideinitializer
*** \brief DebugLog_SetEnabledFlag() wrapper.
*** \details Wrapper macro for DebugLog_SetEnabledFlag().
*** \param enabledflag Enable flag.\n
***   0 - Disable logging.\n
***   !0 - Enable logging.
**/
#define   DEBUGLOG_SetEnabledFlag(enabledflag) \
              DebugLog_SetEnabledFlag(enabledflag)

#else     /* USE_DEBUGLOG */

/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param enableflag Ignored.
**/
#define   DEBUGLOG_Enable(enableflag)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \retval 0 DebugLog is disabled.
**/
#define   DEBUGLOG_GetEnabledFlag()           (0)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \returns NULL DebugLog is disabled.
**/
#define   DEBUGLOG_GetFilenamePointer()       NULL
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param enabledflag Ignored.
**/
#define   DEBUGLOG_Initialize(enabledflag)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
**/
#define   DEBUGLOG_LogIn()
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
**/
#define   DEBUGLOG_LogOut()
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
**/
#define   DEBUGLOG_Printf0(format)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
**/
#define   DEBUGLOG_Printf1(format,v1)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
**/
#define   DEBUGLOG_Printf2(format,v1,v2)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
**/
#define   DEBUGLOG_Printf3(format,v1,v2,v3)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
**/
#define   DEBUGLOG_Printf4(format,v1,v2,v3,v4)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
**/
#define   DEBUGLOG_Printf5(format,v1,v2,v3,v4,v5)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
**/
#define   DEBUGLOG_Printf6(format,v1,v2,v3,v4,v5,v6)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
**/
#define   DEBUGLOG_Printf7(format,v1,v2,v3,v4,v5,v6,v7)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
*** \param v8 Ignored.
**/
#define   DEBUGLOG_Printf8(format,v1,v2,v3,v4,v5,v6,v7,v8)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
*** \param v8 Ignored.
*** \param v9 Ignored.
**/
#define   DEBUGLOG_Printf9(format,v1,v2,v3,v4,v5,v6,v7,v8,v9)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
*** \param v8 Ignored.
*** \param v9 Ignored.
*** \param v10 Ignored.
**/
#define   DEBUGLOG_Printf10(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
*** \param v8 Ignored.
*** \param v9 Ignored.
*** \param v10 Ignored.
*** \param v11 Ignored.
**/
#define   DEBUGLOG_Printf11(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
*** \param v6 Ignored.
*** \param v7 Ignored.
*** \param v8 Ignored.
*** \param v9 Ignored.
*** \param v10 Ignored.
*** \param v11 Ignored.
*** \param v12 Ignored.
**/
#define   DEBUGLOG_Printf12(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)
/**
*** \hideinitializer
*** \brief Does nothing.
*** \details Does nothing, DebugLog is disabled.
*** \param enabledflag Ignored.
**/
#define   DEBUGLOG_SetEnabledFlag(enabledflag) \
              DebugLog_SetEnabledFlag(enabledflag)

#endif    /* USE_DEBUGLOG */

#endif    /* DEBUGLOG_NOWRAPPERMACROS */


/****
*****
***** DATA TYPES
*****
****/


/****
*****
***** DATA
*****
****/


/****
*****
***** VARIABLES
*****
****/


/****
*****
***** PROTOTYPES
*****
****/

#if       defined(USE_DEBUGLOG) || defined(DEBUGLOG_NOWRAPPERMACROS)

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

/**
*** \brief Runtime debug log enable flag value.
*** \details Returns the value of the runtime debug log enable flag.
**/
int DebugLog_GetEnabledFlag(void);
/**
*** \brief Debug log filename pointer.
*** \details Returns a pointer to the filename of the debug log.
**/
char const * DebugLog_GetFilenamePointer(void);
/**
*** \brief Initializes the debug log.
*** \details Initializes the debug log by truncating the existing debug log,
***   and then writing the date and time to it.  Also sets the runtime enable
***   flag according to the passed parameter.
**/
void DebugLog_Initialize(int EnabledFlag);
/**
*** \brief Increase indent depth.
*** \details Increases the indent depth.
**/
void DebugLog_LogIn(void);
/**
*** \brief Decrease indent depth.
*** \details Decreases the indent depth.
**/
void DebugLog_LogOut(void);
/**
*** \brief Write a string to the debug log.
*** \details  Writes a printf style string to the debug log.
**/
void DebugLog_Printf(char const *pFormat,...);
/**
*** \brief Runtime enable/disable logging.
*** \details Enables/disables (at runtime) the ability to log debug data.
**/
void DebugLog_SetEnabledFlag(int EnabledFlag);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */

#endif    /* defined(USE_DEBUGLOG) || defined(DEBUGLOG_NOWRAPPERMACROS) */


#endif    /* DEBUGLOG_H */
