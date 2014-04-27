/*
** This file is part of toolbox.
** Copyright (C) 2008-2013 by Alan Wise (alanwise@users.sourceforge.net)
**
** This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**   GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
**   along with this program.  If not, see
**     <http://www.gnu.org/licenses/>,
**   or write to the
**     Free Software Foundation, Inc.,
**     59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/**
*** \file debuglog.h
*** \brief Write debug information to a file.
*** \details This module provides the ability to write debug information to a
***    text file.
***
*** All functions should be accessed through the function wrapper macros. This
***    method of calling the function wrapper macros ensures that if the
***    module is not enabled, absolutely no code should be generated.
***
*** Two macros must be defined to use the debug log facilities:
***    ENABLE_DEBUGLOG and USE_DEBUGLOG.
***
*** ENABLE_DEBUGLOG must be defined for all files using the debug log
***    facilities.  The best method is to define it as part of common
***    compile options. If defined only for debuglog.c, code will be
***    generated for the functions in this file, but the macros will not
***    generate code to actually call the functions.  If defined for
***    files other than debuglog.c, the functions in this file will not
***    be compiled, but the macros will generate code to actually call
***    the functions; ultimately resulting in link errors.
***
*** USE_DEBUGLOG allows the debug log facilities to be enabled/disabled
***    on an individual file basis.  If defined before including
***    debuglog.h, the macros will generate code to call the functions.
***    If not defined, no code to call the functions is generated.
***
*** If enabled at compile time, the logging can also be enabled/disabled
***    at run time.
***
*** This module can indent according to function call depth.  To enable
***    this feature, place DEBUGLOG_LogIn() at the beginning of each
***    function, and DEBUGLOG_LogOut() at EACH exit point.
***
*** \warning This module is NOT thread safe.
**/


#ifndef   DEBUGLOG_H
#define   DEBUGLOG_H

#if       defined(ENABLE_DEBUGLOG) && defined(BUILD_PLUGIN)
#error    "ENABLE_DEBUGLOG and BUILD_PLUGIN can not both be defined."
#error    "Check your settings."
#endif    /* defined(ENABLE_DEBUGLOG) && defined(BUILD_PLUGIN) */

#if       !defined(ENABLE_DEBUGLOG) && defined(ENABLE_DEBUGLOGGUI)
#error    "ENABLE_DEBUGLOGGUI is defined and needs ENABLE_DEBUGLOG to be "
#error    "defined also, but it is not. Check your settings."
#endif    /* !defined(ENABLE_DEBUGLOG) && defined(ENABLE_DEBUGLOGGUI) */


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

#if       defined(DEBUGLOG_NOWRAPPERMACROS)
/* Allow certain modules to access prototypes, but not macros. */
#undef    USE_DEBUGLOG
#endif    /* defined(DEBUGLOG_NOWRAPPERMACROS) */

#if       !defined(DEBUGLOG_C)
#if       defined(ENABLE_DEBUGLOG) && defined(USE_DEBUGLOG) \
              && !defined(BUILD_PLUGIN)

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
*** \brief DebugLog_GetFileNamePointer wrapper.
*** \details Wrapper macro for DebugLog_GetFileNamePointer().
*** \returns Pointer to debug log file name.
*** \warning Do not free the returned pointer!
**/
#define   DEBUGLOG_GetFileNamePointer()       DebugLog_GetFileNamePointer()
/**
*** \hideinitializer
*** \brief DebugLog_Initialize() wrapper.
*** \details Wrapper macro for DebugLog_Initialize().
*** \param enabledflag
***     Enable flag.\n
***     0 - Disable logging.\n
***     !0 - Enable logging.
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
              DebugLog_Printf( format "\n",v1,v2)
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
*** \param v8 Variable #9.
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
*** \param v8 Variable #9.
*** \param v8 Variable #10.
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
*** \param v8 Variable #9.
*** \param v8 Variable #10.
*** \param v8 Variable #11.
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
*** \param v8 Variable #9.
*** \param v8 Variable #10.
*** \param v8 Variable #11.
*** \param v8 Variable #12.
**/
#define   DEBUGLOG_Printf12(format,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)  \
              DebugLog_Printf(format"\n",v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12)
/**
*** \hideinitializer
*** \brief DebugLog_SetEnabledFlag() wrapper.
*** \details Wrapper macro for DebugLog_SetEnabledFlag().
*** \param enabledflag
***   Enable flag.\n
***   0 - Disable logging.\n
***   !0 - Enable logging.
**/
#define   DEBUGLOG_SetEnabledFlag(enabledflag) \
              DebugLog_SetEnabledFlag(enabledflag)

#else     /* defined(ENABLE_DEBUGLOG) && defined(USE_DEBUGLOG)
              && !defined(BUILD_PLUGIN) */

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
#define   DEBUGLOG_GetFileNamePointer()       (NULL)
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

#endif    /* defined(ENABLE_DEBUGLOG) && defined(USE_DEBUGLOG)
              && !defined(BUILD_PLUGIN) */
#endif    /* !defined(DEBUGLOG_C) && !defined(DEBUGLOGDIALOG_CPP) */


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

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

/**
*** \brief Returns runtime enable flag.
*** \details Returns the value of the runtime debug log enable flag.
*** \retval 0 Disabled.
*** \retval !0 Enabled.
**/
int DebugLog_GetEnabledFlag(void);
/**
*** \brief Returns file name.
*** \details Returns a pointer to the file name of the debug log.
*** \returns Pointer to file name.
*** \warning Do not free the returned pointer!
**/
char const * DebugLog_GetFileNamePointer(void);
/**
*** \brief Initialize the module.
*** \details Initializes the debug log by truncating the existing debug log,
***     and then writing the date and time to it.  Also sets the runtime enable
***     flag according to the passed parameter.
*** \param EnabledFlag
***   0 - Disable.\n
***   !0 - Enable.
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
*** \brief Write printf style string.
*** \details Writes a printf style string to the debug log.
*** \param pFormat Printf style format string.
*** \param ...  Additional parameters.
**/
void DebugLog_Printf(char const *pFormat,...);
/**
*** \brief Sets runtime enable flag.
*** \details Enables/disables (at runtime) the ability to log debug data.
*** \param EnabledFlag
***     0 - Disable.\n
***     !0 - Enable.
**/
void DebugLog_SetEnabledFlag(int EnabledFlag);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* DEBUGLOG_H */
