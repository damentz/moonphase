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

#include  "datetime.h"

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
    *** \brief Convert to DATETIMEOPTIONS_T format.
    *** \details COnverts from the OPTIONS_C format to the DATETIMEOPTIONS_T
    ***   format.
    *** \param pDateTimeOptions Storage for the DATETIMEOPTIONS_T data.
    **/
    void Convert(DATETIMEOPTIONS_T *pDateTimeOptions);

    /**
    *** \brief Returns the 24 hour format flag.
    *** \details Returns the 24 hour format flag.
    *** \retval 0 Use 12 hour (am/pm) format.
    *** \retval !0 Use 24 hour format.
    **/
    bool Get24HourFormatFlag(void) const;

    /**
    *** \brief Returns the 4 digit year format flag.
    *** \details Returns the 4 digit year format flag.
    *** \retval 0 Use 2 digit year format.
    *** \retval !0 Use 4 digit year format.
    **/
    bool Get4DigitYearFlag(void) const;

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
    *** \brief Returns the long day of the week format flag.
    *** \details Returns the long day of the week format flag.
    *** \retval 0 Use short day of the week format (Sun.).
    *** \retval !0 Use long day of the week format (Sunday).
    **/
    bool GetLongDayOfWeekFormatFlag(void) const;

    /**
    *** \brief Returns the month format flag.
    *** \details Returns the month format flag.
    *** \retval 0 Use short month format (Jan.).
    *** \retval !0 Use long month format (January).
    **/
    bool GetLongMonthFormatFlag(void) const;

    /**
    *** \brief Returns the margin.
    *** \details Returns the margin.
    *** \returns Margin.
    **/
    int GetMargin(void) const;

    /**
    *** \brief Returns the show the day of the week flag.
    *** \details Returns the show the day of the week flag.
    *** \retval 0 Don't show the day of the week.
    *** \retval !0 Show the day of the week.
    **/
    bool GetShowDayOfWeekFlag(void) const;

    /**
    *** \brief Returns the show the seconds flag.
    *** \details Returns the show the seconds flag.
    *** \retval 0 Don't show the seconds.
    *** \retval !0 Show the seconds.
    **/
    bool GetShowSecondsFlag(void) const;

    /**
    *** \brief Returns the text color.
    *** \details Returns the color of the text.
    *** \returns Color of the text.
    **/
    QColor GetTextColor(void) const;

    /**
    *** \brief Returns the unit or format index.
    *** \details Returns the index of the display unit or the date/time format
    ***   index.
    *** \returns Unit or format index.
    **/
    int GetUnitFormatIndex(void) const;

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
    *** \brief Sets the 24 hour format flag.
    *** \details Sets the 24 hour format flag.
    *** \param Flag 0=Use 12 hour (am/pm) format,\n
    ***   !0=Use 24 hour format.
    **/
    void Set24HourFormatFlag(bool Flag);

    /**
    *** \brief Sets the 4 digit year format flag.
    *** \details Sets the 4 digit year format flag.
    *** \param Flag 0=Use 2 digit year format,\n
    ***   !0=Use 4 digit year format.
    **/
    void Set4DigitYearFlag(bool Flag);

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
    *** \brief Sets the long day of the week format flag.
    *** \details Sets the long day of the week format flag.
    *** \param Flag 0=Use short day of the week format (Sun.),\n
    ***   !0=Use long day of the week format (Sunday).
    **/
    void SetLongDayOfWeekFormatFlag(bool Flag);

    /**
    *** \brief Sets the long month format flag.
    *** \details Sets the long month format flag.
    *** \param Flag 0=Use short month format (Jan.),\n
    ***   !0=Use long month format (January).
    **/
    void SetLongMonthFormatFlag(bool Flag);

    /**
    *** \brief Sets the margin.
    *** \details Sets the margin.
    *** \param Margin Margin.
    **/
    void SetMargin(int Margin);

    /**
    *** \brief Sets the show the day of the week flag.
    *** \details Sets the show the day of the week flag.
    *** \param Flag 0=Don't show the day of the week,\n
    ***   !0=Show the day of the week.
    **/
    void SetShowDayOfWeekFlag(bool Flag);

    /**
    *** \brief Sets the show the seconds flag.
    *** \details Sets the show the seconds.
    *** \param Flag 0=Don't show the seconds,\n
    ***   !0=Show the seconds.
    **/
    void SetShowSecondsFlag(bool Flag);

    /**
    *** \brief Sets the text color.
    *** \details Sets the color of the text.
    *** \param Color Color.
    **/
    void SetTextColor(QColor Color);

    /**
    *** \brief Sets the unit or format index.
    *** \details Sets the index of the display unit or the index of the
    ***   date/time format index.
    *** \param Index Unit or format index.
    **/
    void SetUnitFormatIndex(int Index);

    /**
    *** \brief Sets the use system background color flag.
    *** \details Sets the use system background color flag.
    *** \param Flag 0=Use user defined color,\n
    ***   !0=Use system background color.
    **/
    void SetUseSystemBackgroundColorFlag(bool Flag);

    /**
    *** \brief Sets the use system font flag.
    *** \details Sets the use system font flag.
    *** \param Flag 0=Use user defined font,\n
    ***   !0=Use system background font.
    **/
    void SetUseSystemFontFlag(bool Flag);

    /**
    *** \brief Sets the use system text color flag.
    *** \details Sets the use system text color flag.
    *** \param Flag 0=Use user defined color,\n!0=Use system text color.
    **/
    void SetUseSystemTextColorFlag(bool Flag);

    /**
    *** \brief Assignment operator (const) (=)
    *** \details Assignment operator (const) (=)
    *** \param RHS Object on right hand side of operator.
    *** \return Copy of data.
    **/
    OPTIONS_C & operator=(OPTIONS_C const &RHS);

    /**
    *** \brief Assignment operator (=)
    *** \details Assignment operator (=)
    *** \param RHS Object on right hand side of operator.
    *** \return Copy of data.
    **/
    OPTIONS_C & operator=(OPTIONS_C &RHS);

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
    *** \brief Background color.
    *** \details Background color.
    **/
    QColor m_BackgroundColor;

    /**
    *** \brief Date/time options.
    *** \details Options for the date/time print functions.
    **/
    DATETIMEOPTIONS_T m_DateTimeOptions;

    /**
    *** \brief Font.
    *** \details Font.
    **/
    QFont m_Font;

    /**
    *** \brief Margin.
    *** \details Pad area around text.
    **/
    int m_Margin;

    /**
    *** \brief Text color.
    *** \details Text color.
    **/
    QColor m_TextColor;

    /**
    *** \brief Unit or format index.
    *** \details Index of the display unit or index of the date/time format.
    **/
    int m_UnitFormatIndex;

    /**
    *** \brief Use system background color flag.
    *** \details Use system background color flag.
    **/
    bool m_UseSystemBackgroundColorFlag;

    /**
    *** \brief Use system font flag.
    *** \details Use system font flag.
    **/
    bool m_UseSystemFontFlag;

    /**
    *** \brief Use system text color flag.
    *** \details Use system text color flag.
    **/
    bool m_UseSystemTextColorFlag;
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
