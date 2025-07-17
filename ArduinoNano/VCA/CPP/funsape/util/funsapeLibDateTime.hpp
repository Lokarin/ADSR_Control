//!
//! \file           funsapeLibDateTime.hpp
//! \brief          Date and Time definitions to Funsape AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        This file provides date ans time support to rtc modules.
//! \note           The class always stores the hour in 24 Hours format.
//!                     Functions to convert between formats are provided and
//!                     are automatically called when needed.
//!

// =============================================================================
// Include guard (START)
// =============================================================================

// =============================================================================
// Include guard
// =============================================================================

#ifndef __FUNSAPE_LIB_DATETIME_HPP
#define __FUNSAPE_LIB_DATETIME_HPP              2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_DATETIME_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_DATETIME_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// DateTime Class
// =============================================================================

//!
//! \brief          Brief description
//! \details        Long description
//!
class DateTime
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:
    //     /////////////////////     AM/PM FLAG    //////////////////////     //
    //!
    //! \brief          AM/PM flag for 12-Hours time format
    //! \details        Long description
    //!
    enum class AmPmFlag : bool_t {
        AM                  = false,
        PM                  = true,
    };

    //     ////////////////////////    MONTH    /////////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    enum class Month : uint8_t {
        UNDEFINED           = 0,        //!< Used to test if the variable was previously setted
        JANUARY             = 1,
        FEBRUARY            = 2,
        MARCH               = 3,
        APRIL               = 4,
        MAY                 = 5,
        JUNE                = 6,
        JULY                = 7,
        AUGUST              = 8,
        SEPTEMBER           = 9,
        OCTOBER             = 10,
        NOVEMBER            = 11,
        DECEMBER            = 12
    };

    //     /////////////////////    TIME FORMAT    //////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    enum class TimeFormat : bool_t {
        FORMAT_24_HOURS     = false,    //!< 24-hours format (0-23)
        FORMAT_12_HOURS     = true,     //!< 12-hours format (1-12 AM/PM)
    };

    //     //////////////////////    TIME ZONE    ///////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    enum class TimeZone : uint8_t {
        UNDEFINED           = 0,        //!< Used to test if the variable was previously setted
        UTC_MINUS_1200      = 1,        //! USA (Baker Island, Howland Island)
        UTC_MINUS_1100      = 2,        //! New Zealand (Niu), USA (Jarvis Island, Kingman Reef, Midway Atoll, Palmyra Atoll)
        UTC_MINUS_1000      = 3,        //! France (French Poynesia), New Zealand (Cook Islands), USA (Hawaii, Johnston Atoll)
        UTC_MINUS_0930      = 4,        //! France (Marquesas Islands)
        UTC_MINUS_0900      = 5,        //! France (Gambier Islands), USA (Alaska)
        UTC_MINUS_0800      = 6,        //! Canada (British Columbia, Yukon), France (Clipperton Island), USA (Pacific Time Zone)
        UTC_MINUS_0700      = 7,        //! Canada (Alberta, Nortwest Territories), Mexico (Chinhuahua, Nayarit, Sinaloa, Sonora), USA (Mountain Time Zone)
        UTC_MINUS_0600      = 8,        //! Belize, Canada (Central Time Zone), Chile (Easter Island), Costa Rica, El Salvador, Guatemala, Honduras, Mexico, USA (Central Time Zone)
        UTC_MINUS_0500      = 9,        //! Bahamas, Brazil (Acre, Amazonas - western part), Colombia, Cuba, Ecuador, Haiti, Jamaica, Panama, Peru, USA (Esatern Time Zone)
        UTC_MINUS_0400      = 10,       //! Antigua e Barbuda, Barbados, Bolivia, Brazil (Amazonas, Mato Grosso, Mato Grosso do Sul, Rondonia, Roraima), Canada (Atlantic Time Zone), Chile, Dominica, Guyana, Paraguay, Venezuela
        UTC_MINUS_0330      = 11,       //! Canada (Newfoundland)
        UTC_MINUS_0300      = 12,       //! Argentina, Brazil (Brazilia Official Timezone), Suriname, Uruguay
        UTC_MINUS_0230      = 13,       //! St. John's
        UTC_MINUS_0200      = 14,       //! Brazil (Fernando de Noronha), United Kingdom (South Georgia, South Sandwich Islands)
        UTC_MINUS_0100      = 15,       //! Cape Verde, Portugal (Azores)
        UTC_EQUAL_0000      = 16,       //! Burkina Faso, Cote d'Ivoire, Gambia, Ghana, Guinea, Guinea-Bissau, Iceland, Ireland, Liberia, Mali, Mauritania, Marocco, Portugal, Senegal, Sierra Leone, Togo, United Kingdom, Western Sahara
        UTC_PLUS_0100       = 17,       //! Albania, Algeria, Andorra, Angola, Austria, Belgium, Benin, Bosnia and Herzegovina, Cameroon, Central African Republic, Chad, Congo, Croatia, Czech Republic, Denmark, France, Gabon, Gemany, Hungary, Italy, Kosovo, Liechtenstein, Luxembourg, Macedonia, Malta, Monaco, Montenegro, Netherlands, Niger, Nigeria, Poland, San Marino, Serbia,  Slovakia, Slovenia, Spain, Sweeden, Switzerland, Tunisia, Vatican City
        UTC_PLUS_0200       = 18,       //! Botswana, Bulgaria, Burundi, Cyprus, Egypt, Estonia, Finland, Greece, Israel, Jordan, Latvia, Lebanon, Lesotho, Lithuania, Libya, Malawi, Moldova, Mozambique, Namibia, State of Palestine, Romania, Rwanda, South Africa, Sudan, Swaziland, Syria, Ukraine, Zambia, Zimbabwe
        UTC_PLUS_0300       = 19,       //! Bahrain, Belarus, Comoros, Djibouti, Eritrea, Iraq, Kenya, Kuwait, Madagascar, Qatar, Russia (Moscow Time), Saudi Arabia, Somalia, South Sudan, Tanzania, Turkey, Uganda, Yemen
        UTC_PLUS_0330       = 20,       //! Iran
        UTC_PLUS_0400       = 21,       //! Armenia, Azerbaijan, Mauritius, Oman, Russia (Samara Time), Seychelles, United Arab Emirates
        UTC_PLUS_0430       = 22,       //! Afghanistan
        UTC_PLUS_0500       = 23,       //! Maldives, Pakistan, Russia (Yekaterinburg Time), Tajikistan, Turkmenistan, Uzbekistan
        UTC_PLUS_0530       = 24,       //! India, Sri Lanka
        UTC_PLUS_0545       = 25,       //! Nepal
        UTC_PLUS_0600       = 26,       //! Bangladesh, Bhutan, Kazakhstan, Kyrgyzstan, Russia (Omsk Time), United Kingdom (British Indian Ocean Territory)
        UTC_PLUS_0630       = 27,       //! Myanmar
        UTC_PLUS_0700       = 28,       //! Cambodia, Laos, Mongolia, Russia (Krasnoyarsk Time), Thailand, Vietnam
        UTC_PLUS_0800       = 29,       //! Brunei, China, Malaysia, Philippines, Russia (Irkutsk Time), Singapore, Taiwan
        UTC_PLUS_0830       = 30,       //! North Korea
        UTC_PLUS_0845       = 31,       //! Australia (Eucla)
        UTC_PLUS_0900       = 32,       //! Japan, South Korea, Palau, Russia (Amur, Siberia), Timor-Leste
        UTC_PLUS_0930       = 33,       //! Australia (Broken Hill, New South Wales, Northern Territory, South Australia)
        UTC_PLUS_1000       = 34,       //! Australia (Australian Capital Territory), Papua New Guinea, Russia (Vladivostok Time)
        UTC_PLUS_1030       = 35,       //! Australia (Lord Howe Island)
        UTC_PLUS_1100       = 36,       //! Russia (Srednekolymsk Time), Salomon Islands, Vanuatu
        UTC_PLUS_1200       = 37,       //! Fiji, Kiribati (Gilbert Islands), Marshall Islands, Nauru, New Zealand, Russia (Kamchatka Time), Tuvalu
        UTC_PLUS_1245       = 38,       //! New Zealand (Chatham Islands)
        UTC_PLUS_1300       = 39,       //! Kiribati (Phoenix Islands), New Zealand (Tokelau), Samoa, Tonga
        UTC_PLUS_1400       = 40        //! Kiribati (Line Islands)
    };

    //     ///////////////////////    WEEKDAY    ////////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    enum class WeekDay : uint8_t {
        UNDEFINED           = 0,        //! Used to test if the variables was previously setted
        SUNDAY              = 1,
        MONDAY              = 2,
        TUESDAY             = 3,
        WEDNESDAY           = 4,
        THURSDAY            = 5,
        FRIDAY              = 6,
        SATURDAY            = 7
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:
    DateTime(
            void
    );
    ~DateTime(
            void
    );

    // -------------------------------------------------------------------------
    // Operator overloading ----------------------------------------------------
public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         Error              Return info
    //!
    Error getLastError(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         bool_t              Return info
    //!
    bool_t isDateSet(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         bool_t              Return info
    //!
    bool_t isTimeSet(
            void
    );

    //     ////////////////     DATE RELATED METHODS ////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          year_p             Param description
    //! \param          month_p             Param description
    //! \param          day_p             Param description
    //! \param          weekDay_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getDate(
            uint16_t *year_p,
            Month *month_p,
            uint8_t *day_p,
            WeekDay *weekDay_p          = nullptr
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          weekDay_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getWeekDay(
            WeekDay *weekDay_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         bool_t              Return info
    //!
    bool_t isLeapYear(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          year_p             Param description
    //! \param          month_p             Param description
    //! \param          day_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t setDate(
            cuint16_t year_p,
            const Month month_p,
            cuint8_t day_p
    );

    //     ////////////////     TIME RELATED METHODS ////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          minutes_p             Param description
    //! \param          seconds_p             Param description
    //! \param          timeFormat             Param description
    //! \param          amPmFlag_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getTime(
            uint8_t *hours_p,
            uint8_t *minutes_p,
            uint8_t *seconds_p,
            const TimeFormat timeFormat = TimeFormat::FORMAT_24_HOURS,
            AmPmFlag *amPmFlag_p        = nullptr
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          minutes_p             Param description
    //! \param          seconds_p             Param description
    //! \param          milliseconds_p             Param description
    //! \param          timeFormat             Param description
    //! \param          amPmFlag_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getTime(
            uint8_t *hours_p,
            uint8_t *minutes_p,
            uint8_t *seconds_p,
            uint16_t *milliseconds_p,
            const TimeFormat timeFormat = TimeFormat::FORMAT_24_HOURS,
            AmPmFlag *amPmFlag_p        = nullptr
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          timeFormat_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getTimeFormat(
            TimeFormat *timeFormat_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          timeZone_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t getTimeZone(
            TimeZone *timeZone_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          minutes_p             Param description
    //! \param          seconds_p             Param description
    //! \param          timeFormat_p             Param description
    //! \param          amPmFlag_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t setTime(
            cuint8_t hours_p,
            cuint8_t minutes_p,
            cuint8_t seconds_p,
            const TimeFormat timeFormat_p       = TimeFormat::FORMAT_24_HOURS,
            const AmPmFlag amPmFlag_p           = AmPmFlag::AM
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          minutes_p             Param description
    //! \param          seconds_p             Param description
    //! \param          milliseconds_p             Param description
    //! \param          timeFormat_p             Param description
    //! \param          amPmFlag_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t setTime(
            cuint8_t hours_p,
            cuint8_t minutes_p,
            cuint8_t seconds_p,
            cuint16_t milliseconds_p,
            const TimeFormat timeFormat_p       = TimeFormat::FORMAT_24_HOURS,
            const AmPmFlag amPmFlag_p           = AmPmFlag::AM
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          timeFormat_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t setTimeFormat(
            const TimeFormat timeFormat_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          timeZone_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t setTimeZone(
            const TimeZone timeZone_p
    );

private:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    void _clearData(
            void
    );

    //     ////////////////     DATE RELATED METHODS ////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         DateTime::WeekDay              Return info
    //!
    DateTime::WeekDay _evaluateDayOfWeek(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          year_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t _isLeapYear(
            cuint16_t year_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          year_p             Param description
    //! \param          month_p             Param description
    //! \param          day_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t _isValidDate(
            cuint16_t year_p,
            const Month month_p,
            cuint8_t day_p
    );

    //     ////////////////     TIME RELATED METHODS ////////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          amPmFlag_p             Param description
    //! \param          fromFormat_p             Param description
    //! \param          toFormat_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t _convertTimeFormat(
            uint8_t *hours_p,
            AmPmFlag *amPmFlag_p,
            const TimeFormat fromFormat_p,
            const TimeFormat toFormat_p
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \param          hours_p             Param description
    //! \param          minutes_p             Param description
    //! \param          seconds_p             Param description
    //! \param          timeFormat_p             Param description
    //! \return         bool_t              Return info
    //!
    bool_t _isValidTime(
            cuint8_t hours_p,
            cuint8_t minutes_p,
            cuint8_t seconds_p,
            const TimeFormat timeFormat_p
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:
    // NONE

private:
    //     /////////////////    CONTROL AND STATUS     //////////////////     //
    bool_t          _dateSet            : 1;
    bool_t          _timeSet            : 1;
    Error           _lastError;

    //     /////////////////     DATE DATA MEMBERS     //////////////////     //
    uint8_t         _day            : 5;    // Month day number; valid values in range [1 to 31], 0 is NOT DEFINED
    bool_t          _leapYear       : 1;    // If the year is a leap year
    Month           _month;                 // Month number; valid values in range [1 to 12], 0 is NOT DEFINED
    uint16_t        _year           : 14;   // Year in four digits valid values in range [1 to 9999], 0 is NOT DEFINED
    WeekDay         _weekDay;               // Week day number; valid values in range [1 to 7], 0 is NOT DEFINED

    //     /////////////////     TIME DATA MEMBERS     //////////////////     //
    AmPmFlag        _amPmFlag;              // Time flag if AM/PM mode is set
    uint8_t         _hours          : 5;    // Hour in 24-hours format; valid values in range [0 to 24], 25 is NOT DEFINED
    uint16_t        _milliseconds   : 10;   // Milliseconds; valid values in range [0 to 999]
    uint8_t         _minutes        : 6;    // Minutes; valid values in range [0 to 59]
    uint8_t         _seconds        : 6;    // Seconds; valid values in range [0 to 59]
    TimeFormat      _timeFormat;            // Time format
    TimeZone        _timeZone;              // Current time zone

protected:
    // NONE

}; // class DateTime

// =============================================================================
// DateTime - Class overloading operators
// =============================================================================

// -----------------------------------------------------------------------------
// Month enumeration -----------------------------------------------------------

inlined bool_t operator >(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) > static_cast<int>(b));
}

inlined bool_t operator >=(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) >= static_cast<int>(b));
}

inlined bool_t operator <(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) < static_cast<int>(b));
}

inlined bool_t operator <=(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) <= static_cast<int>(b));
}

inlined bool_t operator ==(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) == static_cast<int>(b));
}

inlined bool_t operator !=(DateTime::Month a, int b)
{
    return static_cast<bool_t>(static_cast<int>(a) != static_cast<int>(b));
}

// =============================================================================
// Global variables
// =============================================================================

// -----------------------------------------------------------------------------
// Externally defined global variables -----------------------------------------

// NONE

// -----------------------------------------------------------------------------
// Internally defined global variables -----------------------------------------

// NONE

// =============================================================================
// DateTime - Class inline function definitions
// =============================================================================

// NONE

// =============================================================================
// General public functions declarations
// =============================================================================

// NONE

// =============================================================================
// General inline functions definitions
// =============================================================================

// NONE

// =============================================================================
// External default objects
// =============================================================================

// NONE

#endif // defined(_FUNSAPE_PLATFORM_AVR)

#endif // __FUNSAPE_LIB_DATETIME_HPP

// =============================================================================
// END OF FILE
// =============================================================================
