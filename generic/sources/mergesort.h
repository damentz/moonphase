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
*** \file mergesort.h
*** \brief MergeSort() function.
*** \details Macro expansion of MergeSort() function.
**/


#ifndef   MERGESORT_H
#define   MERGESORT_H


/****
*****
***** INCLUDES
*****
****/

#include  "errorcode.h"
#include  "debuglog.h"


/****
*****
***** DEFINES
*****
****/

/**
*** \hideinitializer
*** \brief MergeSort() prototype template.
*** \details Template to define a prototype to merge sort user defined data in
***   a singly linked list. The rough prototype is:\n
***   ERRORCODE_T listname_MergeSort(typenameLINK_T **ppList,
***   int (*CompareCallback)(usertype,usertype))
*** \param listname Prefix for the function name (listname_MergeSort).
*** \param typename Prefix for type name (typenameLINK_T).
*** \param usertype Data type for list. The type MUST contain at least two
***   fields:\n
***   typenameLINK_T *pNext - pointer to next link.\n
***   usertype Data - Link data.
**/
#define MERGESORT_PROTOTYPE(listname,typename,usertype) \
    /**
        \brief Sorts a singly linked list.
        \details Sorts the singly linked list according to a user defined
          comparison function.
        \param ppList Pointer to the first element pointer in a singly linked
          list.
        \param CompareCallback User defined function to sort the list. The
          function should return an integer according to the following
          values:\n
          <0 - Element 1 is less than element 2.\n
          =0 - Element 1 is equal to element 2.\n
          >0 - Element 1 is greater than element 2.
        \retval >0 Success.
        \retval <0 Failure.
    **/ \
    ERRORCODE_T listname##_MergeSort(typename##LINK_T **ppList, \
        int (*CompareCallback)(const usertype,const usertype))

/**
*** \hideinitializer
*** \brief MergeSort() function template.
*** \details Template to define a function to merge sort user defined data in
***   a singly linked list. The rough prototype is:\n
***   ERRORCODE_T listname_MergeSort(typenameLINK_T **ppList,
***   int (*CompareCallback)(usertype,usertype))
*** \param listname Prefix for the function name (listname_MergeSort).
*** \param typename Prefix for type name (typenameLINK_T).
*** \param usertype Data type for list. The type MUST contain at least two
***   fields:\n
***   typenameLINK_T *pNext - pointer to next link.\n
***   usertype Data - Link data.
**/
#define MERGESORT_FUNCTION(listname,typename,usertype) \
    MERGESORT_PROTOTYPE(listname,typename,usertype) \
    { \
      ERRORCODE_T ErrorCode; \
      typename##LINK_T *pList1Start; \
      typename##LINK_T *pFullListEnd; \
      typename##LINK_T *pList1End; \
      typename##LINK_T *pList2Start; \
      typename##LINK_T **ppHead; \
      typename##LINK_T *pHead; \
    \
    \
      DEBUGLOG_Printf2(#listname "_MergeSort(%p,%p)",ppList,CompareCallback); \
      DEBUGLOG_LogIn(); \
    \
      /* Parameter checking. */ \
      if ((ppList==NULL) || (CompareCallback==NULL) ) \
          ErrorCode=ERRORCODE_NULLPARAMETER; \
      else \
      { \
        /* No links - done sorting... */ \
        if (*ppList==NULL) \
          ErrorCode=ERRORCODE_INVALIDDATA; \
        else \
        { \
          /* One link - done sorting... */ \
          if ((*ppList)->pNext==NULL) \
            ErrorCode=ERRORCODE_SUCCESS; \
          else \
          { \
            /* Break the full list into halves. */ \
            pList1Start=*ppList; \
            pFullListEnd=*ppList; \
            pList2Start=*ppList; \
            do \
            { \
              pList1End=pList2Start; \
              pList2Start=pList2Start->pNext; \
              pFullListEnd=pFullListEnd->pNext; \
              if (pFullListEnd!=NULL) \
                pFullListEnd=pFullListEnd->pNext; \
            } while (pFullListEnd); \
    \
            /* Terminate first list. */ \
            pList1End->pNext=NULL; \
    \
            /* Recursively call mergesort on each half. */ \
            ErrorCode=listname##_MergeSort(&pList1Start,CompareCallback); \
            if (ErrorCode>0) \
            { \
              ErrorCode=listname##_MergeSort(&pList2Start,CompareCallback); \
              if (ErrorCode>0) \
              { \
                /* Store the head in a temporary storage location. */ \
                ppHead=&pHead; \
    \
                /* While we haven't reached the end of either list. */ \
                while( (pList1Start!=NULL) && (pList2Start!=NULL) ) \
                { \
                  /* Find which link goes first. */ \
                  if (CompareCallback(pList1Start->Data,pList2Start->Data) \
                      <=0) \
                  { \
                    /* Add the link from the first list to the sorted list, \
                       and advance first list pointer. */ \
                    *ppHead=pList1Start; \
                    pList1Start=pList1Start->pNext; \
                  } \
                  else \
                  { \
                    /* Add the link from the second list to the sorted list, \
                       and advance second list pointer. */ \
                    *ppHead=pList2Start; \
                    pList2Start=pList2Start->pNext; \
                  } \
    \
                  /* Set up storage for next link. */ \
                  ppHead=&(*ppHead)->pNext; \
                }\
    \
                /* Append the remaining non-empty (probably) list to the \
                   sorted list. */ \
                if (pList1Start!=NULL) \
                  *ppHead=pList1Start; \
                else \
                  *ppHead=pList2Start; \
    \
                /* Return the sorted list. */ \
                *ppList=pHead; \
              } \
            } \
          } \
        } \
      } \
    \
      DEBUGLOG_LogOut(); \
      return(ErrorCode); \
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

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

#ifdef    __cplusplus
}
#endif    /* __cplusplus */


#endif    /* MERGESORT_H */
