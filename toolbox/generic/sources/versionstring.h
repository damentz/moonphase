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
*** \file versionstring.h
*** \brief TODO
*** \details TODO
**/


#ifndef   VERSIONSTRING_H
#define   VERSIONSTRING_H


/****
*****
***** INCLUDES
*****
****/

#include  "errorcode.h"


/****
*****
***** DEFINES
*****
****/

#define   DIGITS_MAXIMUMCOUNT   (8)   /* Should be more than enough. */


/****
*****
***** DATA TYPES
*****
****/

typedef struct structVERSIONSTRING
{
  short Digits[DIGITS_MAXIMUMCOUNT];
} VERSIONSTRING_T;

#ifdef    __cplusplus
extern "C" {
#endif    /* __cplusplus */

ERRORCODE_T VersionString_Compare(
    VERSIONSTRING_T const *pLHS,VERSIONSTRING_T const *pRHS);
ERRORCODE_T VersionString_Set(
    VERSIONSTRING_T *pVersionString,char const *pString);

#ifdef    __cplusplus
}
#endif    /* __cplusplus */

#ifdef    __cplusplus
ERRORCODE_T VersionString_Compare(
    VERSIONSTRING_T *pLHS,VERSIONSTRING_T *pRHS);
ERRORCODE_T VersionString_Set(
    VERSIONSTRING_T *pVersionString,char const *pString);
class VERSIONSTRING_C
{
  public:
    VERSIONSTRING_C(void)
        { VersionString_Set(&m_VersionString,""); return; };
    VERSIONSTRING_C(char const *pString)
        { VersionString_Set(&m_VersionString,pString); return; };
    ~VERSIONSTRING_C(void)
        { };

    void Set(char const *pString) { VersionString_Set(&m_VersionString,pString); return; }
    bool operator<(const VERSIONSTRING_C &RHS) const
        { return(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)<0); };
    bool operator<=(const VERSIONSTRING_C &RHS) const
        { return(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)<=0); };
    bool operator==(const VERSIONSTRING_C &RHS) const
        { return(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)==0); };
    bool operator!=(const VERSIONSTRING_C &RHS) const
        { return(!(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)==0)); };
    bool operator>=(const VERSIONSTRING_C &RHS) const
        { return(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)>=0); };
    bool operator>(const VERSIONSTRING_C &RHS) const
        { return(VersionString_Compare(&this->m_VersionString,&RHS.m_VersionString)>0); };

  private:
    VERSIONSTRING_T m_VersionString;
};
#endif    /* __cplusplus */


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


#endif    /* VERSIONSTRING_H */
