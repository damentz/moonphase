/*
** This file is part of moonphase.
** Copyright (C) 2014-2015 by Alan Wise (alanwise@users.sourceforge.net)
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
*** \file options.h
*** \brief Set/manipulate options.
*** \details Set and manipulate text options.
**/


#ifndef   OPTIONS_H
#define   OPTIONS_H


/****
*****
***** INCLUDES
*****
****/

#include  <QColor>
#include  <QFont>


/****
*****
***** DEFINES
*****
****/


/****
*****
***** DATA TYPES
*****
****/

/**
*** \brief Set/manipulate options.
*** \details Set and manipulate text options.
**/
class OPTIONS_C
{
  public:
    /**
    *** \brief Constructor.
    *** \details Constructor.
    **/
    OPTIONS_C(void);
    /**
    *** \brief Constructor.
    *** \details Constructor.
    *** \param pOptions Option data.
    **/
    OPTIONS_C(OPTIONS_C *pOptions);

    /**
    *** \brief Destructor.
    *** \details Destructor.
    **/
    ~OPTIONS_C(void);

    /**
    *** \brief Build a style sheet string.
    *** \details Build a style sheet string using text and background colors.
    *** \retval Style sheet string.
    **/
    QString BuildStyleSheetString(void) const;

    /**
    *** \brief Returns the background color.
    *** \details Returns the color of the background.
    *** \returns Color of the background.
    **/
    QColor GetBackgroundColor(void) const;

    /**
    *** \brief Returns the font.
    *** \details Returns the font.
    *** \returns Font.
    **/
    QFont GetFont(void) const;

    /**
    *** \brief Returns the margin.
    *** \details Returns the margin.
    *** \returns Margin.
    **/
    int GetMargin(void) const;

    /**
    *** \brief Returns the text color.
    *** \details Returns the color of the text.
    *** \returns Color of the text.
    **/
    QColor GetTextColor(void) const;

    /**
    *** \brief Returns the unit index.
    *** \details Returns the index of the display unit.
    *** \returns Unit index.
    **/
    int GetUnitIndex(void) const;

    /**
    *** \brief Returns the use system background color flag.
    *** \details Returns the use system background color flag.
    *** \retval 0 Use user defined color.
    *** \retval !0 Use system background color.
    **/
    bool GetUseSystemBackgroundColorFlag(void) const;

    /**
    *** \brief Returns the font.
    *** \details Returns the font.
    *** \retval 0 Use user defined font.
    *** \retval !0 Use system font.
    **/
    bool GetUseSystemFontFlag(void) const;

    /**
    *** \brief Returns the use system text color flag.
    *** \details Returns the use system text color flag.
    *** \retval 0 Use user defined color.
    *** \retval !0 Use system text color.
    **/
    bool GetUseSystemTextColorFlag(void) const;

    /**
    *** \brief Sets the background color.
    *** \details Sets the color of the background.
    *** \param Color Color of the background.
    **/
    void SetBackgroundColor(QColor Color);

    /**
    *** \brief Sets the font.
    *** \details Sets the font.
    *** \param Font Font.
    **/
    void SetFont(QFont Font);

    /**
    *** \brief Sets the margin.
    *** \details Sets the margin.
    *** \param Margin Margin.
    **/
    void SetMargin(int Margin);

    /**
    *** \brief Sets the text color.
    *** \details Sets the color of the text.
    *** \param Color Color.
    **/
    void SetTextColor(QColor Color);

    /**
    *** \brief Sets the unit index.
    *** \details Sets the index of the display unit.
    *** \param Index Unit index.
    **/
    void SetUnitIndex(int Index);

    /**
    *** \brief Sets the use system background color flag.
    *** \details Sets the use system background color flag.
    *** \param SystemFlag 0=Use user defined color,\n
    ***   !0=Use system background color.
    **/
    void SetUseSystemBackgroundColorFlag(bool SystemFlag);

    /**
    *** \brief Sets the use system font flag.
    *** \details Sets the use system font flag.
    *** \param SystemFlag 0=Use user defined font,\n
    ***   !0=Use system background font.
    **/
    void SetUseSystemFontFlag(bool SystemFlag);

    /**
    *** \brief Sets the use system text color flag.
    *** \details Sets the use system text color flag.
    *** \param SystemFlag 0=Use user defined color,\n!0=Use system text color.
    **/
    void SetUseSystemTextColorFlag(bool SystemFlag);

    /**
    *** \brief Comparison operator (==).
    *** \details Comparison operator (==).
    *** \param RHS Object on right hand side of operator.
    *** \retval 0 Objects are not equivalent.
    *** \retval !0 Objects are equivalent.
    **/
    bool operator==(OPTIONS_C const RHS) const;

    /**
    *** \brief Comparison operator (!=).
    *** \details Comparison operator (!=).
    *** \param RHS Object on right hand side of operator.
    *** \retval 0 Objects are equivalent.
    *** \retval !0 Objects are not equivalent.
    **/
    bool operator!=(OPTIONS_C const RHS) const;

  private:
    /**
    *** \brief Unit index.
    *** \details Index of the display unit.
    **/
    int m_UnitIndex;

    /**
    *** \brief Margin.
    *** \details Pad area around text.
    **/
    int m_Margin;

    /**
    *** \brief Use system font flag.
    *** \details Use system font flag.
    **/
    bool m_UseSystemFontFlag;

    /**
    *** \brief Font.
    *** \details Font.
    **/
    QFont m_Font;

    /**
    *** \brief Use system text color flag.
    *** \details Use system text color flag.
    **/
    bool m_UseSystemTextColorFlag;

    /**
    *** \brief Text color.
    *** \details Text color.
    **/
    QColor m_TextColor;

    /**
    *** \brief Use system background color flag.
    *** \details Use system background color flag.
    **/
    bool m_UseSystemBackgroundColorFlag;

    /**
    *** \brief Background color.
    *** \details Background color.
    **/
    QColor m_BackgroundColor;
};


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


#endif    /* OPTIONS_H */
