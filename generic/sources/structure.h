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
*** \file structure.h
*** \brief Generic structure manipulation.
*** \details Generic methods to create/initialize/uninitialize/destroy
***     structures.
**/


#ifndef   STRUCTURE_H
#define   STRUCTURE_H


/****
*****
***** INCLUDES
*****
****/

#include  "errorcode.h"
#ifdef    DEBUG_STRUCTURE_C
#ifndef   USE_DEBUGLOG
#define   USE_DEBUGLOG
#endif    /* USE_DEBUGLOG */
#endif    /* DEBUG_STRUCTURE_C */
#include  "debuglog.h"

#include  <string.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \hideinitializer
*** \brief Create() structure prototype template.
*** \details Template to define a prototype for a function to allocate
***     memory for a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_Create(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Create()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_CREATE(prefix,typename) \
    /**
        \brief Allocates structure memory.
        \details Allocates memory for the structure.
        \param ppStructure Pointer to storage for the structure pointer.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_Create(/*@out@*/typename **ppStructure)

/**
*** \hideinitializer
*** \brief Create() structure function template.
*** \details Template to define a function to allocate memory for a structure.
***     The rough prototype is:\n
***     ERRORCODE_T prefix_Create(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Create()).
*** \param typename User type name.
**/
#define   STRUCTURE_FUNCTION_CREATE(prefix,typename) \
    STRUCTURE_PROTOTYPE_CREATE(prefix,typename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#prefix"_Create(%p)",ppStructure); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppStructure==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Allocate memory. */ \
        *ppStructure=(typename*)malloc(sizeof(**ppStructure)); \
        if (*ppStructure==NULL) \
          ErrorCode=ERRORCODE_SYSTEMFAILURE; \
        else \
          ErrorCode=ERRORCODE_SUCCESS; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Destroy() structure prototype template.
*** \details Template to define a prototype for a function to deallocate
***     memory for a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_Destroy(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Destroy()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_DESTROY(prefix,typename) \
    /**
        \brief Deallocates structure memory.
        \details Deallocates memory for the structure.
        \param ppStructure Pointer to storage for the structure pointer.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_Destroy(typename **ppStructure)

/**
*** \hideinitializer
*** \brief Destroy() structure function template.
*** \details Template to define a function to deallocate memory for a
***     structure. The rough prototype is:\n
***     ERRORCODE_T prefix_Destroy(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Destroy()).
*** \param typename User type name.
**/
#define   STRUCTURE_FUNCTION_DESTROY(prefix,typename) \
    STRUCTURE_PROTOTYPE_DESTROY(prefix,typename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#prefix"_Destroy(%p)",ppStructure); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppStructure==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else if (*ppStructure==NULL) \
        ErrorCode=ERRORCODE_INVALIDDATA; \
      { \
        /* Free structure. */ \
        free(*ppStructure); \
        *ppStructure=NULL; \
        ErrorCode=ERRORCODE_SUCCESS; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Initialize() structure prototype template.
*** \details Template to define a prototype for a function to initialize
***     a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_Initialize(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Initialize()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_INITIALIZE(prefix,typename) \
    /**
        \brief Initializes the structure.
        \details Clears the memory of the structure and then initializes the
            members.
        \param pStructure Pointer to the structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_Initialize(typename *pStructure)

/**
*** \hideinitializer
*** \brief Initialize() structure function template.
*** \details Template to define a function to initialize a structure. The
***     rough prototype is:\n
***     ERRORCODE_T prefix_Initialize(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Initialize()).
*** \param typename User type name.
**/
#define   STRUCTURE_FUNCTION_INITIALIZE(prefix,typename) \
    STRUCTURE_PROTOTYPE_INITIALIZE(prefix,typename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#prefix"_Initalize(%p)",pStructure); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pStructure==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Initialize structure. */ \
        memset(pStructure,0,sizeof(*pStructure)); \
    \
        /* Create structure members. */ \
        ErrorCode=prefix##_InitializeMembers(pStructure); \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief InitializeMembers() structure prototype template.
*** \details Template to define a prototype for a function to initialize
***     the members of a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_InitializeMembers(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_InitializeMembers()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_INITIALIZEMEMBERS(prefix,typename) \
    /**
        \brief Initializes structure members.
        \details Initializes the members of the structure.
        \param pStructure Pointer to the structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_InitializeMembers(typename *pStructure)

/**
*** \hideinitializer
*** \brief Uninitialize() structure prototype template.
*** \details Template to define a prototype for a function to uninitialize
***     a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_Uninitialize(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Uninitialize()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_UNINITIALIZE(prefix,typename) \
    /**
        \brief Uninitializes the structure.
        \details Uninitializes members of the structure and then clears the
            memory.
        \param pStructure Pointer to structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_Uninitialize(typename *pStructure)

/**
*** \hideinitializer
*** \brief Uninitialize() structure function template.
*** \details Template to define a function to uninitialize a structure. The
***     rough prototype is:\n
***     ERRORCODE_T prefix_Uninitialize(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_Uninitialize()).
*** \param typename User type name.
**/
#define   STRUCTURE_FUNCTION_UNINITIALIZE(prefix,typename) \
    STRUCTURE_PROTOTYPE_UNINITIALIZE(prefix,typename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#prefix"_Uninitialize(%p)",pStructure); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pStructure==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Destroy structure members if necessary. */ \
        ErrorCode=prefix##_UninitializeMembers(pStructure); \
    \
        /* Clear structure. */ \
        memset(pStructure,0,sizeof(*pStructure)); \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief UninitializeMembers() structure prototype template.
*** \details Template to define a prototype for a function to initialize
***     the members of a structure. The rough prototype is:\n
***     ERRORCODE_T prefix_UninitializeMembers(typename **ppStructure)
*** \param prefix Prefix for the function name (prefix_UninitializeMembers()).
*** \param typename User type name.
**/
#define   STRUCTURE_PROTOTYPE_UNINITIALIZEMEMBERS(prefix,typename) \
    /**
        \brief Uninitializes structure members.
        \details Uninitializes the members of the structure.
        \param pStructure Pointer to structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T prefix##_UninitializeMembers(typename *pStructure)


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

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* STRUCTURE_H */
