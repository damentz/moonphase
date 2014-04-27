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
*** \file messagelog.h
*** \brief Write messages to a text file.
*** \details Write debugging messages to a text file.
***
*** All functions should be accessed through the function wrapper macros. This
***     method of calling the function wrapper macros ensures that if the
***     module is not enabled, absolutely no code should be generated.
***
*** ENABLE_MESSAGELOG must be defined for all files using the message log
***     facilities.  The best method is to define it as part of common
***     compile options. If defined only for messagelog.c, code will be
***     generated for the functions in this file, but the macros will not
***     generate code to actually call the functions.  If defined for
***     files other than messagelog.c, the functions in this file will not
***     be compiled, but the macros will generate code to actually call
***     the functions; ultimately resulting in link errors.
***
*** \warning This module is NOT thread safe.
**/


#ifndef   MESSAGELOG_H
#define   MESSAGELOG_H

#if       defined(ENABLE_MESSAGELOG) && defined(BUILD_PLUGIN)
#error    "ENABLE_MESSAGELOG and BUILD_PLUGIN can not both be defined."
#error    "Check your settings."
#endif    /* defined(ENABLE_MESSAGELOG) && defined(BUILD_PLUGIN) */

#if       !defined(ENABLE_MESSAGELOG) && defined(ENABLE_MESSAGELOGGUI)
#error    "ENABLE_MESSAGELOGGUI is defined and needs ENABLE_MESSAGELOG to be "
#error    "defined also, but it is not. Check your settings."
#endif    /* !defined(ENABLE_MESSAGELOG) && defined(ENABLE_MESSAGELOGGUI) */


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

#if       defined(MESSAGELOG_NOWRAPPERMACROS)
/* Allow certain modules to access prototypes, but not macros. */
#undef    USE_MESSAGELOG
#endif    /* defined(MESSAGELOG_NOWRAPPERMACROS) */

#if       defined(ENABLE_MESSAGELOG) && !defined(BUILD_PLUGIN)

/**
*** \brief Serious (possibly fatal) error.
*** \details Value indicating a serious (possibly fatal) error.
**/
#define   MESSAGELOGTYPE_ERROR         (1)
/**
*** \brief Warning.
*** \details Value indicating a warning.
**/
#define   MESSAGELOGTYPE_WARNING       (2)
/**
*** \brief General information
*** \details Value indicating general information.
**/
#define   MESSAGELOGTYPE_INFORMATION   (3)
/**
*** \brief Code needs to be implemented.
*** \details Value indicating code needs to be implemented.
**/
#define   MESSAGELOGTYPE_TODO          (4)
/**
*** \brief Temporary code implementation.
*** \details Value indicating temporary code implementation.
**/
#define   MESSAGELOGTYPE_TEMPORARY     (5)

#if       !defined(MESSAGELOG_C)

/**
*** \hideinitializer
*** \brief Log an error message.
*** \details Tests an ERRORCODE_T variable and if less than 0, prints an error
***     messagecontaining the file name, line number, and errorcode to the log
***     file.
*** \param errorcode ERRORCODE_T variable to test.
**/
#define   MESSAGELOG_LogError(errorcode) \
    if ((errorcode)<0) MessageLog_Printf( \
    __FILE__,__LINE__,MESSAGELOGTYPE_ERROR,"ErrorCode=0x%08X\n",(errorcode))

/**
*** \hideinitializer
*** \brief Print simplified error message.
*** \details Simplified form of printing an error message to the message log.
***   Only prints the file name, line number, and a user defined message.
*** \param message User defined message.
**/
#define   MESSAGELOG_Error(message) \
    MessageLog_Printf(__FILE__,__LINE__,MESSAGELOGTYPE_ERROR,message);
/**
*** \hideinitializer
*** \brief Print simplified warning message.
*** \details Simplified form of printing a warning message to the message log.
***   Only prints the file name, line number, and a user defined message.
*** \param message User defined message.
**/
#define   MESSAGELOG_Warning(message) \
    MessageLog_Printf(__FILE__,__LINE__,MESSAGELOGTYPE_WARNING,message);
/**
*** \hideinitializer
*** \brief Print simplified info message.
*** \details Simplified form of printing an information message to the message log.
***   Only prints the file name, line number, and a user defined message.
*** \param message User defined message.
**/
#define   MESSAGELOG_Info(message) \
    MessageLog_Printf(__FILE__,__LINE__,MESSAGELOGTYPE_INFORMATION,message);
/**
*** \hideinitializer
*** \brief Print simplified todo message.
*** \details Simplified form of printing a todo message to the message log.
***   Only prints the file name, line number, and a user defined message.
*** \param message User defined message.
**/
#define   MESSAGELOG_Todo(message) \
    MessageLog_Printf(__FILE__,__LINE__,MESSAGELOGTYPE_TODO,message);
/**
*** \hideinitializer
*** \brief Print simplified temporary message.
*** \details Simplified form of printing an temporary message to the message log.
***   Only prints the file name, line number, and a user defined message.
*** \param message User defined message.
**/
#define   MESSAGELOG_Temporary(message) \
    MessageLog_Printf(__FILE__,__LINE__,MESSAGELOGTYPE_TODO,message);

/**
*** \hideinitializer
*** \brief MessageLog_GetFileNamePointer() wrapper.
*** \details Wrapper macro for MessageLog_GetFileNamePointer().
*** \param pointer Pointer to storage for the pointer to the message log
***     file name.
*** \retval *pointer Pointer to message log file name.
*** \warning Do not free the returned pointer!
**/
#define   MESSAGELOG_GetFileNamePointer(pointer) \
              MessageLog_GetFileNamePointer(p)
/**
*** \hideinitializer
*** \brief MessageLog_Initialize() wrapper.
*** \details Wrapper macro for MessageLog_Initialize().
**/
#define   MESSAGELOG_Initialize()               MessageLog_Initialize()
/**
*** \hideinitializer
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \param format Format string.
**/
#define   MESSAGELOG_Printf0(format) \
              MessageLog_Printf( f "\n" )
/**
*** \hideinitializer
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
**/
#define   MESSAGELOG_Printf1(format,v1) \
              MessageLog_Printf( f "\n",v1)
/**
*** \hideinitializer
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
**/
#define   MESSAGELOG_Printf2(format,v1,v2) \
              MessageLog_Printf( f "\n",v1,v2)
/**
*** \hideinitializer
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
**/
#define   MESSAGELOG_Printf3(format,v1,v2,v3)        \
    MessageLog_Printf( f "\n",v1,v2,v3)
/**
*** \hideinitializer
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
**/
#define   MESSAGELOG_Printf4(format,v1,v2,v3,v4)     \
    MessageLog_Printf( f "\n",v1,v2,v3,v4)
/**
*** \brief MessageLog_Printf() wrapper.
*** \details Wrapper macro for MessageLog_Printf().
*** \hideinitializer
*** \param format Format string.
*** \param v1 Variable #1.
*** \param v2 Variable #2.
*** \param v3 Variable #3.
*** \param v4 Variable #4.
*** \param v5 Variable #5.
**/
#define   MESSAGELOG_Printf5(format,v1,v2,v3,v4,v5)  \
    MessageLog_Printf( f "\n",v1,v2,v3,v4,v5)

#endif    /* !defined(MESSAGELOG_C) */

#else     /* defined(ENABLE_MESSAGELOG) && !defined(BUILD_PLUGIN) */

#if       !defined(MESSAGELOG_C)

/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param errorcode Ignored.
**/
#define   MESSAGELOG_LogError(errorcode)

/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param message Ignored.
**/
#define   MESSAGELOG_Error(message)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param message Ignored.
**/
#define   MESSAGELOG_Warning(message)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param message Ignored.
**/
#define   MESSAGELOG_Info(message)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param message Ignored.
**/
#define   MESSAGELOG_Todo(message)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param message Ignored.
**/
#define   MESSAGELOG_Temporary(message)

/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param pointer Ignored.
**/
#define   MESSAGELOG_GetFileNamePointer(pointer) \
              MessageLog_GetFileNamePointer(p)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param enableflag Ignored.
**/
#define   MESSAGELOG_Initialize(enableflag)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
**/
#define   MESSAGELOG_Printf0(format)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
**/
#define   MESSAGELOG_Printf1(format,v1)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
**/
#define   MESSAGELOG_Printf2(format,v1,v2)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
**/
#define   MESSAGELOG_Printf3(format,v1,v2,v3)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
**/
#define   MESSAGELOG_Printf4(format,v1,v2,v3,v4)
/**
*** \brief Does nothing.
*** \details Does nothing. MessageLog is disabled.
*** \param format Ignored.
*** \param v1 Ignored.
*** \param v2 Ignored.
*** \param v3 Ignored.
*** \param v4 Ignored.
*** \param v5 Ignored.
**/
#define   MESSAGELOG_Printf5(format,v1,v2,v3,v4,v5)

#endif    /* !defined(MESSAGELOG_C) */

#endif    /* defined(ENABLE_MESSAGELOG) && !defined(BUILD_PLUGIN) */


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

#ifdef    ENABLE_MESSAGELOG

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

/**
*** \brief Returns message log file name pointer.
*** \details Returns a pointer to the file name of the message log.
*** \returns Pointer to file name.
*** \warning Do not free the returned pointer!
**/
char const * MessageLog_GetFileNamePointer(void);
/**
*** \brief Initialize message log.
*** \details Initializes the message log by truncating the existing message
***     log, and then writing the date and time to it.**/
void MessageLog_Initialize(void);
/**
*** \brief printf to message log.
*** \details Writes a printf style string to the message log.
*** \param pFileName Pointer to the file name where the message was generated.
*** \param LineNumber Line number in the file where the message was generated.
*** \param Type Message log type (MESSAGELOGTYPE_?).
*** \param pFormat Printf style format string.
*** \param ... Additional parameters.
**/
void MessageLog_Printf(
    const char *pFileName,int LineNumber,int Type,const char *pFormat,...);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif  /* ENABLE_MESSAGELOG */


#endif    /* MESSAGELOG_H */
