//!
//! \file           funsapeLibHd44780.cpp
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
// System file dependencies
// =============================================================================

#include "funsapeLibHd44780.hpp"
#if !defined(__FUNSAPE_LIB_HD44780_HPP)
#   error "Header file is corrupted!"
#elif __FUNSAPE_LIB_HD44780_HPP != 2407
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

void doWrite(uint16_t value_p);

#define LCD_CLEAR_DISPLAY               0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_ENTRY_MODE_SET              0x04
#define LCD_DISPLAY_CONTROL             0x08
#define LCD_MOVE_CURSOR_OR_DISPLAY      0x10
#define LCD_FUNCTION_SET                0x20
#define LCD_CGRAM_ADDRESS_SET           0x40
#define LCD_DDRAM_ADDRESS_SET           0x80

#define LCD_FUNCTION_SET_8_BITS_INTERFACE       0x10
#define LCD_FUNCTION_SET_4_BITS_INTERFACE       0x00
#define LCD_FUNCTION_SET_2_LINES                0x08
#define LCD_FUNCTION_SET_1_LINE                 0x00
#define LCD_FUNCTION_SET_5x10_FONT              0x04
#define LCD_FUNCTION_SET_5x8_FONT               0x00

#define LCD_DISPLAY_CONTROL_DISPLAY_ON          0x04
#define LCD_DISPLAY_CONTROL_DISPLAY_OFF         0x00
#define LCD_DISPLAY_CONTROL_CURSOR_ON           0x02
#define LCD_DISPLAY_CONTROL_CURSOR_OFF          0x00
#define LCD_DISPLAY_CONTROL_CURSOR_BLINK_ON     0x01
#define LCD_DISPLAY_CONTROL_CURSOR_BLINK_OFF    0x00

#define LCD_ENTRY_MODE_SET_INCREMENT            0x02
#define LCD_ENTRY_MODE_SET_DECREMENT            0x00
#define LCD_ENTRY_MODE_SET_SHIFT                0x01
#define LCD_ENTRY_MODE_SET_OVERWRITE            0x00

#define LCD_MOVE_CURSOR_OR_DISPLAY_SHIFT_DISPLAY    0x80
#define LCD_MOVE_CURSOR_OR_DISPLAY_MOVE_CURSOR      0x00
#define LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT            0x40
#define LCD_MOVE_CURSOR_OR_DISPLAY_LEFT             0x00

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// Static function declarations
// =============================================================================

static int lcdWriteStd(char character, FILE *stream);

// =============================================================================
// File exclusive - Global variables
// =============================================================================

FILE lcdStream                          = {0};
Hd44780 *defaultDisplay                 = nullptr;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Hd44780::Hd44780()
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::Hd44780(void)", Debug::CodeIndex::Hd44780_MODULE);

    fdev_setup_stream(&lcdStream, lcdWriteStd, nullptr, _FDEV_SETUP_WRITE);

    // Reset data members
    this->_gpioControlE                 = nullptr;
    this->_gpioControlRs                = nullptr;
    this->_gpioControlRw                = nullptr;
    this->_gpioDataBus                  = nullptr;
    this->_use4LinesData                = false;
    this->_useBusyFlag                  = false;
    this->_columns                      = 0;
    this->_lines                        = 0;
    this->_font                         = Font::FONT_5X8;
    this->_entryIncDec                  = Step::INCREMENT;
    this->_entryShiftDisplay            = DisplayMode::OVERWRITE;
    this->_cursorBlink                  = false;
    this->_cursorColumn                 = 0;
    this->_cursorLine                   = 0;
    this->_cursorOn                     = false;
    this->_displayOn                    = false;
    this->_isBusyInitialized            = false;
    this->_isInterfaceInitialized       = false;
    this->_isControlPortSet             = false;
    this->_isDataPortSet                = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return;
}

Hd44780::~Hd44780()
{
    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //

bool_t Hd44780::init(const Size size_p, const Font font_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::init(const Size, const Font)", Debug::CodeIndex::Hd44780_MODULE);

    // Local variables
    uint8_t auxCmd                      = 0;

    // Updates some member variables
    this->_font                         = font_p;
    this->_isBusyInitialized            = false;
    this->_isInterfaceInitialized       = false;

    // Checks for errors
    if(!this->_isControlPortSet) {
        // Returns error
        this->_lastError = Error::LCD_CONTROL_PORT_NOT_SET;
        debugMessage(Error::LCD_CONTROL_PORT_NOT_SET, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    if(!this->_isDataPortSet) {
        // Returns error
        this->_lastError = Error::LCD_DATA_PORT_NOT_SET;
        debugMessage(Error::LCD_DATA_PORT_NOT_SET, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // I/O initialization
    this->_gpioDataBus->setMode(GpioBus::Mode::OUTPUT_PUSH_PULL);
    this->_gpioControlE->low();
    this->_gpioControlE->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    this->_gpioControlRs->low();
    this->_gpioControlRs->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    if(this->_useBusyFlag) {
        this->_gpioControlRw->low();
        this->_gpioControlRw->setMode(GpioPin::Mode::OUTPUT_PUSH_PULL);
    }

    // Reset the controller, must be sent 3 times
    delayMs(15);
    if(this->_use4LinesData) {
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayMs(5);
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayUs(100);
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    } else {
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayMs(5);
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
        delayUs(100);
        this->_writeCommand(LCD_FUNCTION_SET | LCD_FUNCTION_SET_8_BITS_INTERFACE);
    }
    delayUs(100);

    // Configures the LCD to 4-bits interface
    if(this->_use4LinesData) {
        this->_functionSet8Bits(LCD_FUNCTION_SET | LCD_FUNCTION_SET_4_BITS_INTERFACE);
        delayUs(100);
    }

    // Function set
    auxCmd = LCD_FUNCTION_SET;
    auxCmd |= (this->_use4LinesData) ? LCD_FUNCTION_SET_4_BITS_INTERFACE : LCD_FUNCTION_SET_8_BITS_INTERFACE;
    auxCmd |= (font_p == Font::FONT_5X8) ? LCD_FUNCTION_SET_5x8_FONT : LCD_FUNCTION_SET_5x10_FONT;
    auxCmd |= (((uint8_t)size_p) < 100) ? LCD_FUNCTION_SET_1_LINE : LCD_FUNCTION_SET_2_LINES;
    this->_writeCommand(auxCmd);
    this->_isBusyInitialized = true;
    this->_writeCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_CONTROL_DISPLAY_OFF);
    this->_writeCommand(LCD_CLEAR_DISPLAY);

    auxCmd = LCD_ENTRY_MODE_SET;
    if(this->_entryIncDec == Step::INCREMENT) {
        auxCmd |= LCD_ENTRY_MODE_SET_INCREMENT;
    } else {
        auxCmd |= LCD_ENTRY_MODE_SET_DECREMENT;
    }
    if(this->_entryShiftDisplay == DisplayMode::SHIFT) {
        auxCmd |= LCD_ENTRY_MODE_SET_SHIFT;
    } else {
        auxCmd |= LCD_ENTRY_MODE_SET_OVERWRITE;
    }
    this->_writeCommand(auxCmd);

    this->_writeCommand(LCD_DISPLAY_CONTROL | LCD_DISPLAY_CONTROL_DISPLAY_ON);

    // Updates the rest of the struct variables
    this->_displayOn                    = true;
    this->_cursorOn                     = false;
    this->_cursorBlink                  = false;
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;
    this->_lines                        = ((((uint8_t)size_p) * 2) / 100) - 1;
    this->_columns                      = ((((uint8_t)size_p) * 2) % 100) - 1;
    this->_isInterfaceInitialized       = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

// -------------------------------------------------------------------------
// Methods -----------------------------------------------------------------

bool_t Hd44780::setControlPort(const GpioPin *controlE_p, const GpioPin *controlRs_p, const GpioPin *controlRw_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setControlPort(const GpioPin *, const GpioPin *, const GpioPin *)",
            Debug::CodeIndex::Hd44780_MODULE);

    // Updates data members
    this->_isControlPortSet             = false;
    this->_isInterfaceInitialized       = false;

    // Local variables
    GpioPin *auxGpioPin                 = nullptr;
    bool_t auxUseBusyFlag               = false;

    // Check for errors
    if((!isPointerValid(controlE_p)) || (!isPointerValid(controlRs_p))) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)controlE_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioPin = (GpioPin *)controlRs_p;
    if(!(auxGpioPin->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    if(isPointerValid(controlRw_p)) {
        auxGpioPin = (GpioPin *)controlRw_p;
        if(!(auxGpioPin->isInitialized())) {
            // Returns error
            this->_lastError = Error::GPIO_NOT_INITIALIZED;
            debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
            return false;
        }
        auxUseBusyFlag = true;
    }

    // Updates data members
    this->_gpioControlE                 = (GpioPin *)controlE_p;
    this->_gpioControlRs                = (GpioPin *)controlRs_p;
    this->_gpioControlRw                = (GpioPin *)controlRw_p;
    this->_useBusyFlag                  = auxUseBusyFlag;
    this->_isControlPortSet             = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::setDataPort(const GpioBus *dataBus_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setDataPort(GpioBus *)", Debug::CodeIndex::Hd44780_MODULE);

    // Updates data members
    this->_isDataPortSet                = false;
    this->_isInterfaceInitialized       = false;

    // Local variables
    GpioBus *auxGpioBus                 = nullptr;
    uint8_t auxBusSize                  = 0;
    bool_t auxUse4LinesData             = false;

    // Check for errors
    if(!isPointerValid(dataBus_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxGpioBus = (GpioBus *)dataBus_p;
    if(!(auxGpioBus->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    auxBusSize = auxGpioBus->getBusSize();

    switch(auxBusSize) {
    case 4: auxUse4LinesData = true;    break;
    case 8: auxUse4LinesData = false;   break;
    default:
        // Returns error
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Updates data members
    this->_gpioDataBus                  = (GpioBus *)dataBus_p;
    this->_use4LinesData                = auxUse4LinesData;
    this->_isDataPortSet                = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

//     //////////////////////    COMMANDS     ///////////////////////     //

bool_t Hd44780::clearScreen(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::clearScreen(void)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Sends command
    if(!this->_writeCommand(LCD_CLEAR_DISPLAY)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::cursorGoTo(cuint8_t line_p, cuint8_t column_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorGoTo(cuint8_t, cuint8_t)", Debug::CodeIndex::Hd44780_MODULE);

    // Local variables
    uint8_t address                     = 0xFF;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    switch(line_p) {
    case 0:     // Go to line 0
        address = column_p;
        break;
    case 1:     // Go to line 1
        address = (this->_lines >= 1) ? (0x40 + column_p) : 0xFF;
        break;
    case 2:     // Go to line 2
        if((this->_lines == 3) && (this->_columns == 11)) {             // Display 12x4
            address = 0x0C + column_p;
        } else if((this->_lines == 3) && (this->_columns == 15)) {      // Display 16x4
            address = 0x10 + column_p;
        } else if((this->_lines == 3) && (this->_columns == 19)) {      // Display 20x4
            address = 0x14 + column_p;
        }
        break;
    case 3:     // Go to line 3
        if((this->_lines == 3) && (this->_columns == 11)) {             // Display 12x4
            address = 0x4C + column_p;
        } else if((this->_lines == 3) && (this->_columns == 15)) {      // Display 16x4
            address = 0x50 + column_p;
        } else if((this->_lines == 3) && (this->_columns == 19)) {      // Display 20x4
            address = 0x54 + column_p;
        }
        break;
    }

    if(address != 0xFF) {
        this->_cursorLine               = line_p;
        this->_cursorColumn             = column_p;
        this->_writeCommand((LCD_DDRAM_ADDRESS_SET | address));
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::cursorHome(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorHome(void)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::cursorMove(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMove(const Direction)", Debug::CodeIndex::Hd44780_MODULE);

    // Local variables
    uint8_t auxCommand = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_MOVE_CURSOR;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::cursorMoveFirstLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveFirstLine(void)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    if(!this->_writeCommand(LCD_RETURN_HOME)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }
    this->_cursorLine                   = 0;
    this->_cursorColumn                 = 0;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::cursorMoveNextLine(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::cursorMoveNextLine(void)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t currentLine                 = (this->_cursorLine + 1);

    currentLine %= (this->_lines + 1);
    if(!this->cursorGoTo(currentLine, 0)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::setDisplayState(const DisplayState displayState_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setDisplayState(const DisplayState)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = 0;
    bool_t auxDisplayOn                 = false;
    bool_t auxCursorOn                  = false;
    bool_t auxBlinkOn                   = false;

    // Decodes display state
    switch(displayState_p) {
    case DisplayState::BLINK_ON:    auxDisplayOn = true;    auxCursorOn = true;     auxBlinkOn = true;  break;
    case DisplayState::CURSOR_ON:   auxDisplayOn = true;    auxCursorOn = true;     auxBlinkOn = false; break;
    case DisplayState::CURSOR_OFF:  auxDisplayOn = true;    auxCursorOn = false;    auxBlinkOn = false; break;
    case DisplayState::DISPLAY_OFF: auxDisplayOn = false;   auxCursorOn = false;    auxBlinkOn = false; break;
    }

    // Creates command
    auxCommand = LCD_DISPLAY_CONTROL;
    auxCommand |= (auxDisplayOn) ? LCD_DISPLAY_CONTROL_DISPLAY_ON : LCD_DISPLAY_CONTROL_DISPLAY_OFF;
    auxCommand |= (auxCursorOn) ? LCD_DISPLAY_CONTROL_CURSOR_ON : LCD_DISPLAY_CONTROL_CURSOR_OFF;
    auxCommand |= (auxBlinkOn) ? LCD_DISPLAY_CONTROL_CURSOR_BLINK_ON : LCD_DISPLAY_CONTROL_CURSOR_BLINK_OFF;
    this->_writeCommand(auxCommand);

    // Updates data members
    this->_cursorBlink                  = auxBlinkOn;
    this->_cursorOn                     = auxCursorOn;
    this->_displayOn                    = auxDisplayOn;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::displayShift(const Direction direction_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::displayShift(const Direction)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = LCD_MOVE_CURSOR_OR_DISPLAY | LCD_MOVE_CURSOR_OR_DISPLAY_SHIFT_DISPLAY;

    auxCommand |= (direction_p == Direction::LEFT) ? LCD_MOVE_CURSOR_OR_DISPLAY_LEFT : LCD_MOVE_CURSOR_OR_DISPLAY_RIGHT;
    if(direction_p == Direction::LEFT) {
        this->_cursorColumn--;
    } else {
        this->_cursorColumn++;
    }
    this->_writeCommand(auxCommand);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::setEntryMode(const Step incDec_p, const DisplayMode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setEntryMode(const Step, const DisplayMode)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    // Local variables
    uint8_t auxCommand                  = LCD_ENTRY_MODE_SET;

    auxCommand |= (this->_entryIncDec == Step::INCREMENT) ? LCD_ENTRY_MODE_SET_INCREMENT : LCD_ENTRY_MODE_SET_DECREMENT;
    auxCommand |= (this->_entryShiftDisplay == DisplayMode::SHIFT) ? LCD_ENTRY_MODE_SET_SHIFT :
            LCD_ENTRY_MODE_SET_OVERWRITE;
    this->_writeCommand(auxCommand);

    this->_entryIncDec                  = incDec_p;
    this->_entryShiftDisplay            = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::stdio(void)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::stdio(void)", Debug::CodeIndex::Hd44780_MODULE);

    stdin = stdout = stderr             = &lcdStream;
    defaultDisplay                      = this;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::setCustomCharacter(cuint8_t charAddress_p, cuint8_t *charData_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::setCustomCharacter(cuint8_t, cuint8_t *)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    if(this->_font == Font::FONT_5X8) {
        if(charAddress_p > 7) {
            return false;
        }
        this->_writeCommand(LCD_CGRAM_ADDRESS_SET | (charAddress_p * 8));
        for(uint8_t i = 0; i < 8; i++) {
            this->_writeCharacter(charData_p[i], false);
        }
    } else {
        if(charAddress_p > 3) {
            return false;
        }
        this->_writeCommand(LCD_CGRAM_ADDRESS_SET | (charAddress_p * 10));
        for(uint8_t i = 0; i < 10; i++) {
            this->_writeCharacter(charData_p[i], false);
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::print(cchar_t character_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::print(cchar_t)", Debug::CodeIndex::Hd44780_MODULE);

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    if(character_p == '\n') {
        for(uint8_t i = this->_cursorColumn; i < (this->_columns + 1); i++) {
            this->_writeCharacter(' ', true);
        }
        this->cursorMoveNextLine();
    } else {
        this->_writeCharacter(character_p, true);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

bool_t Hd44780::print(cchar_t *string_p)
{
    // Mark passage for debugging purpose
    debugMark("Hd44780::print(cchar_t *)", Debug::CodeIndex::Hd44780_MODULE);

    // Local variables
    uint8_t i = 0;

    // Check for errors
    if(!this->_isInterfaceInitialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::Hd44780_MODULE);
        return false;
    }

    while(string_p[i]) {
        this->print(string_p[i]);
        i++;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::Hd44780_MODULE);
    return true;
}

Error Hd44780::getLastError(void)
{
    // Returns error
    return this->_lastError;
}

// =============================================================================
// Class private methods
// =============================================================================

bool_t Hd44780::_functionSet8Bits(uint8_t command_p)
{
    if(this->_useBusyFlag) {
        this->_gpioControlRw->low();                            // LCD in write mode
    }
    this->_gpioControlRs->low();                                // LCD in command mode
    this->_gpioControlE->low();                                 // Makes sure enable is LOW
    this->_gpioDataBus->write(command_p >> 4);                  // Writes data
    this->_gpioControlE->high();                                // Enable pulse start
    delayUs(1);
    this->_gpioControlE->low();                                 // Enable pulse end
    delayUs(1);

    if((!this->_useBusyFlag) || (!this->_isBusyInitialized)) {
        delayUs(40);
    }

    // Returns successfully
    return true;
}

bool_t Hd44780::_writeCommand(uint8_t command_p)
{
    if(this->_useBusyFlag) {
        if(this->_isBusyInitialized) {
            this->_waitUntilReady();
        }
        this->_gpioControlRw->low();                            // LCD in write mode
    }
    this->_gpioControlRs->low();                                // LCD in command mode
    this->_gpioControlE->low();                                 // Makes sure enable is LOW

    if(this->_use4LinesData) {
        this->_gpioDataBus->write(command_p >> 4);              // Writes data (higher nibble)
        this->_gpioControlE->high();                            // Enable pulse start
        delayUs(1);
        this->_gpioControlE->low();                             // Enable pulse end
        delayUs(1);
        this->_gpioDataBus->write(command_p & 0x0F);            // Writes data (lower nibble)
    } else {
        this->_gpioDataBus->write(command_p);                   // Writes data
    }
    this->_gpioControlE->high();                                // Enable pulse start
    delayUs(1);
    this->_gpioControlE->low();                                 // Enable pulse end
    delayUs(1);

    if(!this->_useBusyFlag) {
        if((command_p == LCD_CLEAR_DISPLAY) || (command_p == LCD_RETURN_HOME)) {
            delayMs(2);
        } else {
            delayUs(40);
        }
    }

    // Returns successfully
    return true;
}

bool_t Hd44780::_waitUntilReady(void)
{
    uint8_t auxBusyFlag                 = 0;

    this->_gpioDataBus->setMode(GpioBus::Mode::INPUT_FLOATING);         // Data bus in input mode
    this->_gpioControlRs->low();                                        // LCD in command mode
    this->_gpioControlRw->high();                                       // LCD in read mode
    this->_gpioControlE->low();                                         // Makes sure enable is LOW

    do {
        this->_gpioControlE->high();                                    // Enable pulse start
        delayUs(1);
        auxBusyFlag =  this->_gpioDataBus->read();                      // Reads data bus
        if(this->_use4LinesData) {
            auxBusyFlag &= 0x08;
            this->_gpioControlE->low();                                 // Enable pulse end
            delayUs(1);
            this->_gpioControlE->high();                                // Enable pulse start
            delayUs(1);
        } else {
            auxBusyFlag &= 0x80;
        }
        this->_gpioControlE->low();                                     // Enable pulse end
        delayUs(1);
    } while(auxBusyFlag);

    // Restore LCD status
    this->_gpioControlRw->low();                                        // LCD in write mode
    this->_gpioDataBus->setMode(GpioBus::Mode::OUTPUT_PUSH_PULL);       // Data bus in output mode

    // Returns successfully
    return true;
}

bool_t Hd44780::_writeCharacter(uint8_t character_p, bool_t ddramChar_p)
{
    if((this->_cursorColumn < 40) || (!ddramChar_p)) {
        if(this->_useBusyFlag) {
            this->_waitUntilReady();
            this->_gpioControlRw->low();                                // LCD in write mode
        }
        this->_gpioControlRs->high();                                   // LCD in data mode
        this->_gpioControlE->low();                                     // Makes sure enable is LOW

        if(this->_use4LinesData) {
            this->_gpioDataBus->write(character_p >> 4);                // Writes data (higher nibble)
            this->_gpioControlE->high();                                // Enable pulse start
            delayUs(1);
            this->_gpioControlE->low();                                 // Enable pulse end
            delayUs(1);
            this->_gpioDataBus->write(character_p & 0x0F);              // Writes data (lower nibble)
        } else {
            this->_gpioDataBus->write(character_p);                     // Writes data
        }
        this->_gpioControlE->high();                                    // Enable pulse start
        delayUs(1);
        this->_gpioControlE->low();                                     // Enable pulse end
        delayUs(1);

        if(!this->_useBusyFlag) {
            delayUs(40);
        }
        if(ddramChar_p) {
            this->_cursorColumn++;
        }
    }

    // Returns successfully
    return true;
}

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// Static functions definitions
// =============================================================================

static int lcdWriteStd(char character, FILE *stream)
{
    /*
    uint8_t columns                     = defaultDisplay->_columns + 1;
    uint8_t i                           = 0;

    if(character == '\n') {
        for(i = defaultDisplay->_cursorColumn; i < columns; i++) {
            defaultDisplay->print(' ');
        }
        defaultDisplay->cursorMoveNextLine();
    } else {
        defaultDisplay->print(character);
    }
    */

    defaultDisplay->print(character);

    return 0;
}

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interruption handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
