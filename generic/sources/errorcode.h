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
*** \file errorcode.h
*** \brief Error code type and error definitions.
*** \details Declares the ERRORCODE_T type and defines the various error codes
***     used throughout the system.
**/


#ifndef   ERRORCODE_H
#define   ERRORCODE_H


/****
*****
***** INCLUDES
*****
****/

#include  <errno.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \brief NULL parameter(s) error number.
*** \details Error number of 1 or more NULL parameters.
**/
#define   ERRORCODE_MAJOR_NULLPARAMETER     (-1)
/**
*** \brief Invalid parameter(s) error number.
*** \details Error number of 1 or more invalid parameters.
**/
#define   ERRORCODE_MAJOR_INVALIDPARAMETER  (-2)
/**
*** \brief Invalid data error number.
*** \details Error number of invalid data.
**/
#define   ERRORCODE_MAJOR_INVALIDDATA       (-3)
/**
*** \brief System failure error number.
*** \details Error number of system failure.
**/
#define   ERRORCODE_MAJOR_SYSTEMFAILURE     (-4)
/**
*** \brief Unsupported option, operation or data error number.
*** \details Error number of unsupported option, operation or data.
**/
#define   ERRORCODE_MAJOR_UNSUPPORTED       (-5)
/**
*** \brief Library failure error number.
*** \details Error number of library failure.
**/
#define   ERRORCODE_MAJOR_LIBRARYFAILURE    (-6)
/**
*** \brief Out of memory condition error number.
*** \details Error number of out of memory condition.
**/
#define   ERRORCODE_MAJOR_OUTOFMEMORY       (-7)
/**
*** \brief Function not yet implemented (stubbed) error number.
*** \details Error number of function not yet implemented (stubbed).
**/
#define   ERRORCODE_MAJOR_NOTIMPLEMENTED    (-8)

/**
*** \hideinitializer
*** \brief Encodes an ERRORCODE_T value.
*** \details Encodes a major and a minor code into an ERRORCODE_T value.
*** \param major Major code.
*** \param minor Minor code.
*** \returns ERRORCODE_T value.
**/
#define   ERRORCODE_MakeErrorCode(major,minor) \
              ( (major*65536) | (minor&65535) )

/**
*** \hideinitializer
*** \brief Partially decodes an ERRORCODE_T value.
*** \details Decodes and returns the major code of an ERRORCODE_T value.
*** \param errorcode ERRORCODE_T from which to extract the major code.
*** \returns Major error code.
**/
#define   ERRORCODE_GetMajorCode(errorcode) ((errorcode)>>16)
/**
*** \hideinitializer
*** \brief Partially decodes an ERRORCODE_T value.
*** \details Decodes and returns the minor code of an ERRORCODE_T value.
*** \param errorcode ERRORCODE_T from which to extract the minor code.
*** \returns Minor error code.
**/
#define   ERRORCODE_GetMinorCode(errorcode) ((errorcode)&65535)

/**
*** \hideinitializer
*** \brief Success.
*** \details Success result.
**/
#define   ERRORCODE_SUCCESS             (ERRORCODE_MakeErrorCode(1,0))
/**
*** \hideinitializer
*** \brief Success - true.
*** \details Success - true result.
**/
#define   ERRORCODE_TRUE                (ERRORCODE_MakeErrorCode(1,0))
/**
*** \hideinitializer
*** \brief Success - false.
*** \details Success - false result.
**/
#define   ERRORCODE_FALSE               (ERRORCODE_MakeErrorCode(0,0))
/**
*** \hideinitializer
*** \brief Failure - NULL parameter.
*** \details Error code indicating that one or more NULL pointers was passed
***     to a function expecting non-NULL.
**/
#define   ERRORCODE_NULLPARAMETER       \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_NULLPARAMETER,0)
/**
*** \hideinitializer
*** \brief Failure - Invalid parameter.
*** \details Error code indicating that one or more parameters is invalid
***     (out of range, uninitialized, etc.).
**/
#define   ERRORCODE_INVALIDPARAMETER    \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_INVALIDPARAMETER,0)
/**
*** \hideinitializer
*** \brief Failure - Invalid data.
*** \details Error code indicating that data used by function is invalid
***     (out of range, NULL, etc.).
**/
#define   ERRORCODE_INVALIDDATA         \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_INVALIDDATA,0)
/**
*** \hideinitializer
*** \brief Failure - System library call.
*** \details Error code indicating that a system library call failed.
**/
#define   ERRORCODE_SYSTEMFAILURE       \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_SYSTEMFAILURE,errno)
/**
*** \hideinitializer
*** \brief Failure - Option/data/operation unsupported.
*** \details Error code indicating that a/an option/data/operation is not
***     supported.
**/
#define   ERRORCODE_UNSUPPORTED         \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_UNSUPPORTED,0)
/**
*** \hideinitializer
*** \brief Failure - Non-system library call.
*** \details Error code indicating that an non-system library call failed.
**/
#define   ERRORCODE_LIBRARYFAILURE      \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_LIBRARYFAILURE,errno)
/**
*** \hideinitializer
*** \brief Failure - Out of memory.
*** \details Error code indicating that the system has run out of memory.
**/
#define   ERRORCODE_OUTOFMEMORY         \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_OUTOFMEMORY,0)
/**
*** \hideinitializer
*** \brief Failure - Not (yet) implemented.
*** \details  Error code indicating that a function is not yet implemented
***     (stubbed).
**/
#define   ERRORCODE_NOTIMPLEMENTED      \
              ERRORCODE_MakeErrorCode(ERRORCODE_MAJOR_NOTIMPLEMENTED,0)

/**
*** \hideinitializer
*** \brief Conditionally copy ERRORCODE_T value.
*** \details Copies the first ERRORCODE_T variable to the second ERRORCODE_T
***     variable, ONLY IF the first variable contains an error code and the
***     second variable does not contain an error code, i.e. copy the first
***     error and ignore all others.
*** \param t Current error code.
*** \param e Save error code.
*** \retval e==t Copy conditions met (see above).
*** \retval e!=t Copy conditions not met (see above).
**/
#define   ERRORCODE_ConditionalCopyError(t,e) \
              if ( ((t)<0) && ((e)>=0) ) (e)=(t)

/**
*** \hideinitializer
*** \brief Convert boolean to ERRORCODE_T value
*** \details Converts a boolean value to an ERRORCODE_T boolean value.
*** \param b Boolean value.
*** \retval ERRORCODE_TRUE Boolean value was non-zero.
*** \retval ERRORCODE_FALSE Boolean value was zero.
**/
#define   ERRORCODE_FromBoolean(b)  ((b)?(ERRORCODE_TRUE):(ERRORCODE_FALSE))


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief ERRORCODE_T typedef.
*** \details Typedef ERRORCODE_T to be signed, and big enough to hold error
***     data.
**/
typedef int ERRORCODE_T;


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

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* ERRORCODE_H */
