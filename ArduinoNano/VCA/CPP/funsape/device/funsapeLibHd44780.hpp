//!
//! \file           funsapeLibHd44780.hpp
//! \brief          Hd44780 LCD module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Character LCD controller using 8- or 4-bits interface with
//!                     support to busy flag or delay-driven
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_HD44780_HPP
#define __FUNSAPE_LIB_HD44780_HPP                       2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_HD44780_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../peripheral/funsapeLibGpioBus.hpp"
#if !defined(__FUNSAPE_LIB_GPIO_BUS_HPP)
#   error "Header file (funsapeLibGpioBus.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_BUS_HPP != __FUNSAPE_LIB_HD44780_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioBus.hpp)!"
#endif

#include "../peripheral/funsapeLibGpioPin.hpp"
#if !defined(__FUNSAPE_LIB_GPIO_PIN_HPP)
#   error "Header file (funsapeLibGpioPin.hpp) is corrupted!"
#elif __FUNSAPE_LIB_GPIO_PIN_HPP != __FUNSAPE_LIB_HD44780_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibGpioPin.hpp)!"
#endif

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_HD44780_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

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
// Classes
// =============================================================================

//!
//! \brief          Hd44780 class
//! \details        Hd44780 class.
//!
class Hd44780
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     //////////////////////     LCD SIZE     //////////////////////     //

    //!
    //! \brief      Display size
    //! \details    Display size enumeration.
    //!
    enum class Size : uint8_t {
        LCD_SIZE_UNDEFINED = 0,
        LCD_8X1     = 54,
        LCD_8X2     = 104,
        LCD_10x2    = 105,
        LCD_12X2    = 106,
        LCD_12X4    = 206,
        LCD_16X1    = 58,
        LCD_16X2    = 108,
        LCD_16X4    = 208,
        LCD_20X1    = 60,
        LCD_20X2    = 110,
        LCD_20X4    = 210,
        LCD_24X1    = 62,
        LCD_24X2    = 112,
        LCD_30X2    = 115,
        LCD_32X2    = 116,
        LCD_40X1    = 70,
        LCD_40X2    = 120
    };

    //     ////////////////////    LCD FONT SIZE     ////////////////////     //

    //!
    //! \brief      Font size
    //! \details    Font size enumeration.
    //!
    enum class Font : bool_t {
        FONT_5X8    = false,
        FONT_5X10   = true
    };

    //     /////////////////     DISPLAY ENTRY MODE     /////////////////     //

    //!
    //! \brief      Display mode
    //! \details    Display mode enumeration.
    //!
    enum class DisplayMode : bool_t {
        OVERWRITE   = false,
        SHIFT       = true,
    };

    //     /////////////////     DISPLAY ENTRY STEP     /////////////////     //

    //!
    //! \brief      Step
    //! \details    Step enumeration.
    //!
    enum class Step : bool_t {
        DECREMENT   = false,
        INCREMENT   = true,
    };

    //     ////////////////////    DISPLAY STATE     ////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //!
    enum class DisplayState {
        DISPLAY_OFF                     = 0,
        CURSOR_OFF                      = 1,
        CURSOR_ON                       = 2,
        BLINK_ON                        = 3
    };

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Hd44780 class constructor
    //! \details    Creates a Hd44780 object.
    //!
    Hd44780(
            void
    );

    //!
    //! \brief      Hd44780 class destructor
    //! \details    Destroys a Hd44780 object.
    //!
    ~Hd44780(
            void
    );

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------
public:

    // NONE

private:

    // NONE

protected:

    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------
public:

    //     ////////////////////    CONFIGURATION     ////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      size_p                  Param description
    //! \param      font_p                  Param description
    //! \return     bool_t                  Return info
    //!
    bool_t init(
            const Size size_p,
            const Font font_p           = Font::FONT_5X8
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      controlE_p              Param description
    //! \param      controlRs_p             Param description
    //! \param      controlRw_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setControlPort(
            const GpioPin *controlE_p,
            const GpioPin *controlRs_p,
            const GpioPin *controlRw_p          = nullptr
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      dataBus_p               Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setDataPort(
            const GpioBus *dataBus_p
    );

    //     //////////////////////     COMMANDS     //////////////////////     //

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t              Return info
    //!
    bool_t clearScreen(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      line_p                  Param description
    //! \param      column_p                Param description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorGoTo(
            cuint8_t line_p,
            cuint8_t column_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorHome(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      direction_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMove(
            const Direction direction_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMoveFirstLine(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t cursorMoveNextLine(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      displayState_p      Param description
    //! \return     bool_t              Return info
    //!
    bool_t setDisplayState(
            const DisplayState displayState_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      direction_p             Param description
    //! \return     bool_t                  Return info
    //!
    bool_t displayShift(
            const Direction direction_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      incDec_p                Param description
    //! \param      mode_p                  Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setEntryMode(
            const Step incDec_p,
            const DisplayMode mode_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t                  Return info
    //!
    bool_t stdio(
            void
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      charAddress_p           Param description
    //! \param      charData_p              Param description
    //! \return     bool_t                  Return info
    //!
    bool_t setCustomCharacter(
            cuint8_t charAddress_p,
            cuint8_t *charData_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      character_p             Param description
    //! \return     bool_t              Return info
    //!
    bool_t print(
            cchar_t character_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      string_p         Param description
    //! \return     bool_t              Return info
    //!
    bool_t print(
            cchar_t *string_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     Error               Return info
    //!
    Error getLastError(
            void
    );

private:

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      command_p           Param description
    //! \return     bool_t              Return info
    //!
    bool_t _functionSet8Bits(
            uint8_t command_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      command             Param description
    //! \return     bool_t              Return info
    //!
    bool_t _writeCommand(
            uint8_t command_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \return     bool_t              Return info
    //!
    bool_t _waitUntilReady(
            void
    );

public:

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      character_p             Param description
    //! \param      ddramChar_p             Param description
    //! \return     bool_t              Return info
    //!
    bool_t _writeCharacter(
            uint8_t character_p,
            bool_t ddramChar_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:

    // NONE

private:

    //     //////////////////     DEVICE BUS PORTS     //////////////////     //

    GpioPin         *_gpioControlE;
    GpioPin         *_gpioControlRs;
    GpioPin         *_gpioControlRw;
    GpioBus         *_gpioDataBus;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    bool_t          _isBusyInitialized          : 1;    // 0 off, 1 on
    bool_t          _isInterfaceInitialized     : 1;    // 0 off, 1 on
    bool_t          _isControlPortSet           : 1;    // 0 off, 1 on
    bool_t          _isDataPortSet              : 1;    // 0 off, 1 on
    Error           _lastError;

    //     ///////////////     HARDWARE CONFIGURATION     ///////////////     //

    bool_t          _use4LinesData              : 1;
    bool_t          _useBusyFlag                : 1;
    uint8_t         _lines                      : 2;
    Font            _font                       : 1;

    //     ////////////////     CHARACTER ENTRY MODE     ////////////////     //

    Step            _entryIncDec                : 1;
    DisplayMode     _entryShiftDisplay          : 1;

    //     //////////////     DISPLAY AND CURSOR STATE     //////////////     //

    bool_t          _cursorBlink                : 1;    // 0 off, 1 on
    uint8_t         _cursorLine                 : 2;    // 0 to 3
    bool_t          _cursorOn                   : 1;    // 0 off, 1 on
    bool_t          _displayOn                  : 1;    // 0 off, 1 on

protected:

    // NONE

public:
    uint8_t         _columns                    : 6;
    uint8_t         _cursorColumn               : 6;    // 0 to 39

}; // class Hd44780

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __FUNSAPE_LIB_HD44780_HPP

// =============================================================================
// END OF FILE - funsapeLibHd44780.hpp
// =============================================================================
