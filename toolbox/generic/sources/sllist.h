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
*** \file sllist.h
*** \brief Macro expansions of SLList (singly linked list) functions.
*** \details This module provides the ability to create and manipulate singly
***     linked lists. The functions were written as macros so that the
***     compiler is able to perform type checking (as opposed to void*
***     implementations).
**/


#ifndef   SLLIST_H
#define   SLLIST_H


/****
*****
***** INCLUDES
*****
****/

#include  "mergesort.h"
#include  "sysdefs.h"

#include  <stdlib.h>
#include  <string.h>


/****
*****
***** DEFINES
*****
****/

/**
*** \hideinitializer
*** \brief SLList type declarations.
*** \details Template for type declarations for SLList functions.
*** \param listname Not currently used.
*** \param typebasename Prefix for type names (typebasename_T,
***     typebasenameLINK_T, typebasenameITERATOR_T,
***     typebasenameCONSTITERATOR_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_TYPES(listname,typebasename,usertype) \
    /**
        \brief Singly linked list link.
        \details Individual entry in a singly linked list.
    **/ \
    typedef struct struct##typebasename##LINK \
    { \
      /**
          \brief Next link pointer.
          \details  Pointer to next link or NULL if last link.
      **/ \
      struct struct##typebasename##LINK *pNext; \
      /**
          \brief User data.
          \details User defined data.
      **/ \
      usertype                      Data; \
    } typebasename##LINK_T; \
    /**
        \brief Singly linked list.
        \details Singly linked list structure.
    **/ \
    typedef struct struct##typebasename \
    { \
      /**
          \brief Head link pointer.
          \details Pointer to the first link in the singly linked list or NULL
              if the list is empty.
      **/ \
      typebasename##LINK_T  *pHead; \
      /**
          \brief Tail link pointer.
          \details Pointer to the last link in the singly linked list or NULL
              if the link is invalid or the list is empty.
      **/ \
      typebasename##LINK_T  *pTail; \
    } typebasename##_T; \
    /**
        \brief Iterator.
        \details Singly linked list iterator.
    **/ \
    typedef typebasename##LINK_T typebasename##ITERATOR_T;

/**
*** \hideinitializer
*** \brief AllocateLink() prototype template.
*** \details Template to define the prototype for AllocateLink().
*** \param listname Prefix for the function name (listname_AllocateLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_PROTOTYPE_ALLOCATELINK(listname,typebasename) \
    /**
        \brief Allocate a new link.
        \details Allocates memory for a singly linked list entry and
            clears the structure.
        \param ppNewLink Pointer to storage for new link pointer.
        \retval >0 Success.
        \retval <0 Failure.
        \note Typically this function should not be called directly. It is
            used by other functions in the SLList module.
    **/ \
    ERRORCODE_T listname##_AllocateLink(typebasename##LINK_T **ppNewLink)

/**
*** \hideinitializer
*** \brief AllocateLink() function template.
*** \details Template to define the function AllocateLink().
*** \param listname Prefix for the function name (listname_AllocateLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \note Typically this function should not be called directly. It is
***   mainly used by other functions in the SLList module.
**/
#define   SLLIST_FUNCTION_ALLOCATELINK(listname,typebasename) \
    SLLIST_PROTOTYPE_ALLOCATELINK(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#listname"_AllocateLink(%p)",ppNewLink); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppNewLink==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Allocate link space. */ \
        *ppNewLink=(typebasename##LINK_T*)malloc(sizeof(**ppNewLink)); \
        if (*ppNewLink==NULL) \
          ErrorCode=ERRORCODE_SYSTEMFAILURE; \
        else \
        { \
          /* Clear memory. */ \
          memset(*ppNewLink,0,sizeof(**ppNewLink)); \
    \
          ErrorCode=ERRORCODE_SUCCESS; \
        } \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief AppendLink() prototype template.
*** \details Template to define the prototype for AppendLink().
*** \param listname Prefix for the function name (listname_AppendLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_PROTOTYPE_APPENDLINK(listname,typebasename,usertype) \
    /**
        \brief Add new data to the end of the singly linked list.
        \details Allocates a singly linked list entry, sets its data, and adds
            the link to the end of the singly linked list.
        \param pList Pointer to the singly linked list structure.
        \param Data Data to store in the link.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_AppendLink(typebasename##_T *pList,usertype Data)

/**
*** \hideinitializer
*** \brief AppendLink() function template.
*** \details Template to define the function AppendLink().
*** \param listname Prefix for the function name (listname_AppendLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_FUNCTION_APPENDLINK(listname,typebasename,usertype) \
    SLLIST_PROTOTYPE_APPENDLINK(listname,typebasename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##LINK_T  *pNewLink; \
      typebasename##LINK_T  **ppLastLink; \
    \
    \
      DEBUGLOG_Printf2(#listname"_AppendLink(%p,%p)",pList,&Data); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      {\
        /* Allocate a link. */ \
        ErrorCode=listname##_AllocateLink(&pNewLink); \
        if (ErrorCode>0) \
        { \
          /* If any empty list, set the head link. */ \
          if (pList->pHead==NULL) \
            pList->pHead=pNewLink;  \
    \
          /* Get the tail. */ \
          if (pList->pTail==NULL) \
            ppLastLink=&pList->pTail; \
          else \
            ppLastLink=&(pList->pTail->pNext); \
    \
          /* Make the new link the last link and copy the data. */ \
          *ppLastLink=pNewLink; \
          memcpy(&pNewLink->Data,&Data,sizeof(usertype)); \
    \
          /* Set the last element pointer. */ \
          pList->pTail=pNewLink; \
    \
          ErrorCode=ERRORCODE_SUCCESS; \
        } \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief AppendList() prototype template.
*** \details Template to define the prototype for AppendList().
*** \param listname Prefix for the function name (listname_AppendList()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_PROTOTYPE_APPENDLIST(listname,typebasename)  \
    /**
        \brief Append one list to another list.
        \details Moves one singly linked list to the end of another singly
            linked list.
        \param pList Pointer to the destination singly linked list structure.
        \param pListToAppend Pointer to the source singly linked list
            structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_AppendList( \
    typebasename##_T *pList,typebasename##_T *pListToAppend)

/**
*** \hideinitializer
*** \brief AppendList() function template.
*** \details Template to define the function AppendList().
*** \param listname Prefix for the function name (listname_AppendList()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_FUNCTION_APPENDLIST(listname,typebasename) \
    SLLIST_PROTOTYPE_APPENDLIST(listname,typebasename)  \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##LINK_T  **ppLastLink; \
    \
    \
      DEBUGLOG_Printf2( \
          #listname"_AppendList(%p,%p)",pList,pListToAppend);  \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (pList==NULL) || (pListToAppend==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* If any empty list, set the head link. */ \
        if (pList->pHead==NULL) \
          pList->pHead=pListToAppend->pHead;  \
    \
        /* Get the tail. */ \
        if (pList->pTail==NULL) \
          ppLastLink=&pList->pTail; \
        else \
          ppLastLink=&(pList->pTail->pNext); \
    \
        /* Set the tail of the list to the head of the other list. */ \
        *ppLastLink=pListToAppend->pHead; \
        pList->pTail=pListToAppend->pTail;  \
    \
        /* "Clear" the other list. */ \
        pListToAppend->pHead=NULL;  \
        pListToAppend->pTail=NULL;  \
    \
        ErrorCode=ERRORCODE_SUCCESS;  \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Begin() prototype template.
*** \details Template to define the prototype for Begin().
*** \param listname Prefix for the function name (listname_Begin()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLIST_PROTOTYPE_BEGIN(listname,typebasename) \
    /**
        \brief First element in singly linked list.
        \details Returns the first element in a singly linked list.
        \param pList Pointer to the singly linked list structure.
        \returns Start element in list or NULL if list is empty.
    **/ \
    typebasename##ITERATOR_T * listname##_Begin(typebasename##_T *pList)

/**
*** \hideinitializer
*** \brief Begin() function template.
*** \details Template to define the function Begin().
*** \param listname Prefix for the function name (listname_Begin()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLIST_FUNCTION_BEGIN(listname,typebasename) \
    SLLIST_PROTOTYPE_BEGIN(listname,typebasename) \
    { \
      typebasename##ITERATOR_T *pHead; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Begin(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      pHead=pList->pHead; \
    \
      DEBUGLOG_LogOut(); \
      return(pHead); \
    }

/**
*** \hideinitializer
*** \brief Create() prototype template.
*** \details Template to define the prototype for Create().
*** \param listname Prefix for the function name (listname_Create()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_PROTOTYPE_CREATE(listname,typebasename) \
    /**
        \brief Create a singly linked list.
        \details Allocates memory for a singly linked list.
        \param ppList Pointer to the singly linked list structure pointer.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Create(typebasename##_T **ppList)

/**
*** \hideinitializer
*** \brief Create() function template.
*** \details Template to define the function Create().
*** \param listname Prefix for the function name (listname_Create()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_FUNCTION_CREATE(listname,typebasename) \
    SLLIST_PROTOTYPE_CREATE(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Create(%p)",ppList); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Allocate memory. */ \
        *ppList=(typebasename##_T*)malloc(sizeof(**ppList)); \
        if (*ppList==NULL) \
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
*** \brief DeallocateLink() prototype template.
*** \details Template to define the prototype for DeallocateLink().
*** \param listname Prefix for the function name (listname_DeallocateLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_PROTOTYPE_DEALLOCATELINK(listname,typebasename) \
    /**
        \brief Deallocate a link.
        \details Clears the memory used by singly list link entry and then
            deallocates it.
        \param ppLink Pointer to storage for the link pointer.
        \retval >0 Success.
        \retval <0 Failure.
        \note Typically this function should not be called directly. It is
            used by other functions in the SLList module.
    **/ \
    ERRORCODE_T listname##_DeallocateLink(typebasename##LINK_T **ppLink)

/**
*** \hideinitializer
*** \brief DeallocateLink() function template.
*** \details Template to define the function DeallocateLink().
*** \param listname Prefix for the function name (listname_DeallocateLink()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \note Typically this function should not be called directly. It is
***   mainly used by other functions in the SLList module.
**/
#define   SLLIST_FUNCTION_DEALLOCATELINK(listname,typebasename) \
    SLLIST_PROTOTYPE_DEALLOCATELINK(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
      \
      \
      DEBUGLOG_Printf1(#listname"_DeallocateLink(%p)",ppLink); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppLink==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else if ((*ppLink)==NULL) \
        ErrorCode=ERRORCODE_INVALIDDATA; \
      else \
      { \
        /* Clear memory. */ \
        memset(*ppLink,0,sizeof(**ppLink)); \
    \
        /* Free link space. */ \
        free(*ppLink); \
        *ppLink=NULL; \
        ErrorCode=ERRORCODE_SUCCESS; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Delete() prototype template.
*** \details Template to define the prototype for Delete().
*** Template for prototype declaration of SLLIST_FUNCTION_DELETE().
*** \param listname Prefix for the function name (listname_Delete()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_PROTOTYPE_DELETE(listname,typebasename,usertype) \
    /**
        \brief Delete the links in a singly linked list.
        \details Deletes all of the links in a singly linked list.  Any memory
          allocated by the user may be free()'d in the callback function.
        \param pList Pointer to the singly linked list structure.
        \param FreeCallback Function used to free any data in the link. All
          elements are iterated regardless of the callback return value. The
          first return value indicating an error is saved and returned via
          the function (any subsequent error values are ignored).
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Delete( \
        typebasename##_T *pList,ERRORCODE_T (*FreeCallback)(usertype *))

/**
*** \hideinitializer
*** \brief Delete() function template.
*** \details Template to define the function Delete().
*** \param listname Prefix for the function name (listname_Delete()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype
***   Data type for list.
**/
#define   SLLIST_FUNCTION_DELETE(listname,typebasename,usertype) \
    SLLIST_PROTOTYPE_DELETE(listname,typebasename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      ERRORCODE_T TempErrorCode; \
      typebasename##LINK_T *pCurrent; \
      typebasename##LINK_T *pNext; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Delete(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        ErrorCode=ERRORCODE_SUCCESS; \
        pCurrent=pList->pHead; \
        while(pCurrent!=NULL) \
        { \
          pNext=pCurrent->pNext; \
          ErrorCode=ERRORCODE_SUCCESS; \
          TempErrorCode=ERRORCODE_SUCCESS; \
          if (FreeCallback!=NULL) \
            TempErrorCode=FreeCallback(&pCurrent->Data); \
          ERRORCODE_ConditionalCopyError(TempErrorCode,ErrorCode); \
          TempErrorCode=listname##_DeallocateLink(&pCurrent); \
          ERRORCODE_ConditionalCopyError(TempErrorCode,ErrorCode); \
          pCurrent=pNext; \
        } \
        pList->pHead=NULL; \
        pList->pTail=NULL; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief DeleteLink() prototype template.
*** \details Template to define the prototype for DeleteLink().
*** \param listname Prefix for the function name (listname_DeleteLink()).
*** \param typebasename Prefix for type names (typebasename_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_PROTOTYPE_DELETELINK(listname,typebasename,usertype) \
    /**
        \brief Delete list item.
        \details Delete an item from the singly linked list.
        \param pList Pointer to the destination singly linked list structure.
        \param pIterator Iterator pointing to item to remove.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_DeleteLink( \
        typebasename##_T *pList,typebasename##ITERATOR_T *pIterator)

/**
*** \hideinitializer
*** \brief DeleteLink() prototype template.
*** \details Template to define the prototype for DeleteLink().
*** \param listname Prefix for the function name (listname_DeleteLink()).
*** \param typebasename Prefix for type names (typebasename_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_FUNCTION_DELETELINK(listname,typebasename,usertype) \
    SLLIST_PROTOTYPE_DELETELINK(listname,typebasename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##ITERATOR_T *pIt; \
      BOOLEAN_T FoundFlag; \
    \
    \
      DEBUGLOG_Printf2(#listname"_DeleteLink(%p,%p).",pList,pIterator); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (pList==NULL) || (pIterator==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        ErrorCode=ERRORCODE_SUCCESS; \
        FoundFlag=BOOLEAN_FALSE; \
        pIt=listname##_Begin(pList); \
        while( (pIt!=NULL) && (pIt->pNext!=NULL) && (ErrorCode>=0) ) \
        { \
          if (pIt->pNext==pIterator) \
          { \
            pIt->pNext=pIterator->pNext; \
            ErrorCode=listname##_DeallocateLink(&pIterator); \
            FoundFlag=BOOLEAN_TRUE; \
            break; \
          } \
          pIt=listname##_Next(pIt); \
        } \
        if ( (ErrorCode>=0) && (FoundFlag==BOOLEAN_FALSE) ) \
          ErrorCode=ERRORCODE_INVALIDDATA; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Destroy() prototype template.
*** \details Template to define the prototype for Destroy().
*** \param listname Prefix for the function name (listname_Destroy()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_PROTOTYPE_DESTROY(listname,typebasename) \
    /**
        \brief Destroy a singly linked list.
        \details Deallocates memory for the singly linked list.
        \param ppList Pointer to the singly linked list structure pointer.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Destroy(typebasename##_T **ppList)

/**
*** \hideinitializer
*** \brief Destroy() function template.
*** \details Template to define the function Destroy().
*** \param listname Prefix for the function name (listname_Destroy()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_FUNCTION_DESTROY(listname,typebasename) \
    SLLIST_PROTOTYPE_DESTROY(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Destroy(%p)",ppList); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (ppList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else if ((*ppList)==NULL) \
        ErrorCode=ERRORCODE_INVALIDPARAMETER; \
      else \
      { \
        /* Free structure. */ \
        free(*ppList); \
        *ppList=NULL; \
        ErrorCode=ERRORCODE_SUCCESS;  \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief End() prototype template.
*** \details Template to define the prototype for End().
*** \param listname Prefix for the function name (listname_End()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLIST_PROTOTYPE_END(listname,typebasename) \
    /**
        \brief End of singly linked list.
        \details Returns the end of a singly linked list.
        \param pList Pointer to the singly linked list structure.
        \returns NULL.
    **/ \
    typebasename##ITERATOR_T * listname##_End(typebasename##_T *pList)

/**
*** \hideinitializer
*** \brief End() prototype template.
*** \details Template to define the function End().
*** \param listname Prefix for the function name (listname_End()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLIST_FUNCTION_END(listname,typebasename) \
    SLLIST_PROTOTYPE_END(listname,typebasename) \
    { \
      DEBUGLOG_Printf1(#listname"_End(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      DEBUGLOG_LogOut(); \
      return(NULL); \
    }

/**
*** \hideinitializer
*** \brief GetLinkCount() prototype template.
*** \details Template to define the prototype for GetLinkCount().
*** Template for prototype declaration of SLLIST_FUNCTION_GETLINKCOUNT().
*** \param listname Prefix for the function name (listname_GetLinkCount()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_PROTOTYPE_GETLINKCOUNT(listname,typebasename) \
    /**
        \param pList Pointer to the singly linked list structure.
        \param *pCount Pointer to storage for count.
        \retval >0 Success.
        \retval <0 Failure.
        \returns Number of links in the list.
    **/ \
    ERRORCODE_T listname##_GetLinkCount( \
        typebasename##_T const *pList,unsigned int *pCount)

/**
*** \hideinitializer
*** \brief GetLinkCount() function template.
*** \details Template to define the function GetLinkCount().
*** \param listname Prefix for the function name (listname_GetLinkCount()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
**/
#define   SLLIST_FUNCTION_GETLINKCOUNT(listname,typebasename) \
    SLLIST_PROTOTYPE_GETLINKCOUNT(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##LINK_T  *pLink; \
    \
    \
      DEBUGLOG_Printf2(#listname"_GetLinkCount(%p,%p)",pList,pCount); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (pList==NULL) || (pCount==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Count. */ \
        pLink=pList->pHead; \
        *pCount=0; \
        while(pLink!=NULL) \
        { \
          pLink=pLink->pNext; \
          (*pCount)++; \
        } \
    \
        ErrorCode=ERRORCODE_SUCCESS; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Initialize() prototype template.
*** \details Template to define the prototype for Initialize().
*** \param listname Prefix for the function name (listname_Initialize()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_PROTOTYPE_INITIALIZE(listname,typebasename) \
    /**
        \brief Initialize a singly linked list.
        \details Initializes a singly linked list by clearing the structure.
        \param pList Pointer to the singly linked list structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Initialize(typebasename##_T *pList)

/**
*** \hideinitializer
*** \brief Initialize() function template.
*** \details Template to define the function Initialize().
*** \param listname Prefix for the function name (listname_Initialize()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_FUNCTION_INITIALIZE(listname,typebasename) \
    SLLIST_PROTOTYPE_INITIALIZE(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Initialize(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Initialize structure. */ \
        memset(pList,0,sizeof(*pList)); \
        ErrorCode=ERRORCODE_SUCCESS; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief IsEqual() prototype template.
*** \details Template to define the prototype for IsEqual().
*** \param listname Prefix for the function name (listname_IsEqual()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameITERATOR_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_PROTOTYPE_ISEQUIVALENT(listname,typebasename,usertype) \
    /**
        \brief Singly linked lists comparison.
        \details Checks equality of the data of two singly linked lists.
        \param p1 Pointer to the first singly linked list structure.
        \param p2 Pointer to the second singly linked list structure.
        \param CompareCallback Function used to compare the two lists.
        \retval >0 Lists are equal.
        \retval =0 Lists are not equal.\n
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_IsEquivalent( \
        typebasename##_T const *p1,typebasename##_T const *p2, \
        ERRORCODE_T (*CompareCallback)(const usertype *,const usertype *))

/**
*** \hideinitializer
*** \brief IsEquivalent() function template.
*** \details Template to define the function IsEquivalent().
*** \param listname Prefix for the function name (listname_IsEquovalent()).
*** \param typebasename Prefix for type names (typebasename_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_FUNCTION_ISEQUIVALENT(listname,typebasename,usertype) \
    SLLIST_PROTOTYPE_ISEQUIVALENT(listname,typebasename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##ITERATOR_T const *pI1; \
      typebasename##ITERATOR_T const *pI2; \
    \
    \
      DEBUGLOG_Printf3(#listname"_IsEqual(%p,%p,%p)",p1,p2,CompareCallback); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (p1==NULL) || (p2==NULL) || (CompareCallback==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        ErrorCode=ERRORCODE_FALSE; \
        pI1=listname##Const_Begin(p1); \
        pI2=listname##Const_Begin(p2); \
        while( (pI1!=listname##Const_End(p1)) && (pI2!=listname##Const_End(p2)) ) \
        { \
          ErrorCode=CompareCallback(&pI1->Data,&pI2->Data); \
          if (ErrorCode!=ERRORCODE_TRUE) \
            break; \
          pI1=listname##Const_Next(pI1); \
          pI2=listname##Const_Next(pI2); \
        } \
        if ( (pI1==listname##Const_End(p1)) && (pI2==listname##Const_End(p2)) ) \
          ErrorCode=ERRORCODE_TRUE; \
        else \
          ErrorCode=ERRORCODE_FALSE; \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Next() prototype template.
*** \details Template to define the prototype for Next().
*** \param listname Prefix for the function name (listname_Next()).
*** \param typebasename Prefix for type names (typebasenameITERATOR_T).
**/
#define   SLLIST_PROTOTYPE_NEXT(listname,typebasename) \
    /**
        \brief Next element in singly linked list.
        \details Returns the next element in a singly linked list.
        \param pIterator Singly linked list iterator.
        \returns Next element in list or NULL if end of list.
    **/ \
    typebasename##ITERATOR_T * listname##_Next( \
        typebasename##ITERATOR_T *pIterator)

/**
*** \hideinitializer
*** \brief Next() function template.
*** \details Template to define the function Next().
*** \param listname Prefix for the function name (listname_Next()).
*** \param typebasename Prefix for type names (typebasenameITERATOR_T).
**/
#define   SLLIST_FUNCTION_NEXT(listname,typebasename) \
    SLLIST_PROTOTYPE_NEXT(listname,typebasename) \
    { \
      typebasename##ITERATOR_T *pNext; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Next(%p)",pIterator); \
      DEBUGLOG_LogIn(); \
    \
      if (pIterator==NULL) \
        pNext=NULL; \
      else \
        pNext=pIterator->pNext; \
    \
      DEBUGLOG_LogOut(); \
      return(pNext); \
    }

/**
*** \hideinitializer
*** \brief Print() prototype template.
*** \details Template to define the prototype for Print().
*** \param listname Prefix for the function name (listname_Print()).
*** \param typebasename Prefix for type names (typebasename_T).
*** \param usertype Data type for list.
*** \param outtype Output device type.
**/
#define   SLLIST_PROTOTYPE_PRINT(listname,typebasename,usertype,outtype) \
    /**
        \brief Print the singly linked list.
        \details Prints the singly linked list to the output device.
        \param pList Pointer to the destination singly linked list structure.
        \param PrintCallback Function used to print the singly linked list.
        \param pOut Pointer to the output device.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Print(typebasename##_T const *pList, \
        ERRORCODE_T (PrintCallback)( \
        const usertype,outtype),outtype pOut)

/**
*** \hideinitializer
*** \brief Print() function template.
*** \details Template to define the function Print().
*** \param listname Prefix for the function name (listname_Print()).
*** \param typebasename Prefix for type names
***     (typebasename_T,typebasenameITERATOR_T).
*** \param usertype Data type for list.
*** \param outtype Output device type.
**/
#define   SLLIST_FUNCTION_PRINT(listname,typebasename,usertype,outtype) \
    SLLIST_PROTOTYPE_PRINT(listname,typebasename,usertype,outtype) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##ITERATOR_T const *pIterator; \
    \
    \
      DEBUGLOG_Printf3(#listname"_Print(%p,%p,%p)",pList,PrintCallback,pOut); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (pList==NULL) || (PrintCallback==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        ErrorCode=ERRORCODE_SUCCESS; \
        typebasename##CONST_For(pIterator,*pList) \
        { \
          ErrorCode=PrintCallback(pIterator->Data,pOut); \
          if (ErrorCode<0) \
            break; \
        } \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief SortLinks() prototype template.
*** \details Template to define the prototype for SortLinks().
*** \param listname Prefix for the function name (listname_SortLinks()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_PROTOTYPE_SORTLINKS(listname,typebasename,usertype) \
    /**
        \brief Sort singly linked list.
        \details Sorts the singly linked list according to a user defined
            comparison function.
        \param pList Pointer to the singly linked list structure.
        \param CompareCallback User defined function to sort the singly linked
            list. The function should return an integer according to the
            following values:\n
            <0 - Element 1 is less than element 2.\n
            =0 - Element 1 is equal to element 2.\n
            >0 - Element 1 is greater than element 2.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_SortLinks(typebasename##_T *pList, \
        int (*CompareCallback)(const usertype,const usertype))

/**
*** \hideinitializer
*** \brief SortLinks() function template.
*** \details Template to define the function SortLinks().
*** \param listname Prefix for the function name (listname_SortLinks()).
*** \param typebasename Prefix for type names
***     (typebasename_T, typebasenameLINK_T).
*** \param usertype Data type for list.
**/
#define   SLLIST_FUNCTION_SORTLINKS(listname,typebasename,usertype) \
    static MERGESORT_FUNCTION(listname,typebasename,usertype); \
\
    SLLIST_PROTOTYPE_SORTLINKS(listname,typebasename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      typebasename##LINK_T *pLink; \
    \
    \
      DEBUGLOG_Printf2(#listname"_SortLinks(%p,%p)",pList,CompareCallback); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ( (pList==NULL) || (CompareCallback==NULL) ) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        ErrorCode=listname##_MergeSort(&pList->pHead,CompareCallback); \
        if (ErrorCode>0) \
        { \
          /* Update the tail. */ \
          if (pList->pHead==NULL) \
            pList->pTail=NULL; \
          else \
          { \
            pLink=pList->pHead; \
            while(pLink->pNext!=NULL) \
              pLink=pLink->pNext; \
            pList->pTail=pLink; \
          } \
        } \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Uninitialize() prototype template.
*** \details Template to define the prototype for Uninitialize().
*** \param listname Prefix for the function name (listname_Uninitialize()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_PROTOTYPE_UNINITIALIZE(listname,typebasename) \
    /**
        \brief Uninitialize a singly linked list.
        \details Uninitializes a singly linked list by clearing the structure.
        \param pList Pointer to the singly linked list structure.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_Uninitialize(typebasename##_T *pList)

/**
*** \hideinitializer
*** \brief Uninitialize() function template.
*** \details Template to define the function Uninitialize().
*** \param listname Prefix for the function name (listname_Uninitialize()).
*** \param typebasename Prefix for type names (typebasename_T).
**/
#define   SLLIST_FUNCTION_UNINITIALIZE(listname,typebasename) \
    SLLIST_PROTOTYPE_UNINITIALIZE(listname,typebasename) \
    { \
      ERRORCODE_T ErrorCode; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Uninitialize(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if (pList==NULL) \
        ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* Clear structure. */ \
        memset(pList,0,sizeof(*pList)); \
        ErrorCode=ERRORCODE_SUCCESS;  \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
    }

/**
*** \hideinitializer
*** \brief Begin() constant prototype template.
*** \details Template to define the prototype for Begin().
*** \param listname Prefix for the function name (listnameConst_Begin()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLISTCONST_PROTOTYPE_BEGIN(listname,typebasename) \
    /**
        \brief First element in constant singly linked list.
        \details Returns the first element in a constant singly linked list.
        \param pList Pointer to the constant singly linked list structure.
        \returns Start element in list or NULL if list is empty.
    **/ \
    typebasename##ITERATOR_T const * listname##Const_Begin( \
        typebasename##_T const *pList)

/**
*** \hideinitializer
*** \brief Begin() constant function template.
*** \details Template to define the function Uninitialize().
*** \details Template to define a function which returns the first element in
***     a constant singly linked list.
*** \param listname Prefix for the function name (listnameConst_Begin()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLISTCONST_FUNCTION_BEGIN(listname,typebasename) \
    SLLISTCONST_PROTOTYPE_BEGIN(listname,typebasename) \
    { \
      typebasename##ITERATOR_T const *pHead; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Begin(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      pHead=pList->pHead; \
    \
      DEBUGLOG_LogOut(); \
      return(pHead); \
    }

/**
*** \hideinitializer
*** \brief End() constant prototype template.
*** \details Template to define the prototype for constant End().
*** \param listname Prefix for the function name (listnameConst_End()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLISTCONST_PROTOTYPE_END(listname,typebasename) \
    /**
        \brief End of constant singly linked list.
        \details Returns the end of a constant singly linked list.
        \param pList Pointer to the singly linked list structure.
        \returns Last element in list (NULL).
    **/ \
    typebasename##ITERATOR_T const * listname##Const_End( \
        typebasename##_T const *pList)

/**
*** \hideinitializer
*** \brief End() constant function template.
*** \details Template to define the function constant End().
*** \param listname Prefix for the function name (listnameConst_End()).
*** \param typebasename Prefix for type names
***   (typebasename_T, typebasenameITERATOR_T).
**/
#define   SLLISTCONST_FUNCTION_END(listname,typebasename) \
    SLLISTCONST_PROTOTYPE_END(listname,typebasename) \
    { \
      DEBUGLOG_Printf1(#listname"_End(%p)",pList); \
      DEBUGLOG_LogIn(); \
    \
      DEBUGLOG_LogOut(); \
      return(NULL); \
    }

/**
*** \hideinitializer
*** \brief Next() constant prototype template.
*** \details Template to define the prototype for constant Next().
*** \param listname Prefix for the function name (listnameConst_Next()).
*** \param typebasename Prefix for type names (typebasenameITERATOR_T).
**/
#define   SLLISTCONST_PROTOTYPE_NEXT(listname,typebasename) \
    /**
        \brief Next element in constant singly linked list.
        \details Returns the next element in a constant singly linked list.
        \param pIterator Constant singly linked list iterator.
        \returns Next element in list or NULL if end of list.
    **/ \
    typebasename##ITERATOR_T const * listname##Const_Next( \
        typebasename##ITERATOR_T const * pIterator)

/**
*** \hideinitializer
*** \brief Next() constant function template.
*** \details Template to define the function constant Next().
*** \param listname Prefix for the function name (listnameConst_Next()).
*** \param typebasename Prefix for type names (typebasenameITERATOR_T).
**/
#define   SLLISTCONST_FUNCTION_NEXT(listname,typebasename) \
    SLLISTCONST_PROTOTYPE_NEXT(listname,typebasename) \
    { \
      typebasename##ITERATOR_T *pNext; \
    \
    \
      DEBUGLOG_Printf1(#listname"_Next(%p)",pIterator); \
      DEBUGLOG_LogIn(); \
    \
      if (pIterator==NULL) \
        pNext=NULL; \
      else \
        pNext=pIterator->pNext; \
    \
      DEBUGLOG_LogOut(); \
      return(pNext); \
    }


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


#endif    /* SLLIST_H */
