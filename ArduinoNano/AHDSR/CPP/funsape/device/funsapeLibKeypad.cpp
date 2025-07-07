//!
//! \file           funsapeLibKeypad.cpp
//! \brief          Matrix keypad module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        Matrix keypad controller with support to 4x3, 4x4 and 5x3
//!                     keypads and configurable debounce time
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibKeypad.hpp"
#if !defined(__FUNSAPE_LIB_KEYPAD_HPP)
#   error "Header file is corrupted!"
#elif __FUNSAPE_LIB_KEYPAD_HPP != 2407
#   error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

void turnLedOn(void);
void turnLedOff(void);
void doWrite(uint16_t value_p);

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Keypad::Keypad(void)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::Keypad(void)", Debug::CodeIndex::KEYPAD_MODULE);

    // Reset data members
    this->_gpioLines                    = nullptr;
    this->_gpioColumns                  = nullptr;
    this->_type                         = Type::KEYPAD_4X4;
    this->_columnsMax                   = 0;
    this->_linesMax                     = 0;
    this->_isPortsSet                   = false;
    this->_isKeyValuesSet               = false;
    this->_isInitialized                = false;
    this->_debounceTime                 = constKeypadDefaultDebounceTime;
    this->_keyValue                     = nullptr;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return;
}

Keypad::~Keypad(void)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::~Keypad(void)", Debug::CodeIndex::KEYPAD_MODULE);

    // Deallocate memory
    if(isPointerValid(this->_keyValue)) {
        free(this->_keyValue);
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

bool_t Keypad::init(cuint8_t debounceTime_p)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::init(cuint8_t)", Debug::CodeIndex::KEYPAD_MODULE);

    // Check for errors - PORTS NOT SET
    if(!this->_isPortsSet) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_NOT_SET;
        debugMessage(Error::GPIO_PORT_NOT_SET, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    // Check for errors - KEY VALUES NOT SET
    if(!this->_isKeyValuesSet) {
        // Returns error
        this->_lastError = Error::KEY_VALUES_NOT_SET;
        debugMessage(Error::KEY_VALUES_NOT_SET, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    // Check for errors - BUS SIZE INVALID
    if(this->_gpioLines->getBusSize() != (this->_linesMax + 1)) {
        // Returns error
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    if(this->_gpioColumns->getBusSize() != (this->_columnsMax + 1)) {
        // Returns error
        this->_lastError = Error::GPIO_BUS_SIZE_INVALID;
        debugMessage(Error::GPIO_BUS_SIZE_INVALID, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }

    // Configures GPIOs
    this->_gpioLines->setMode(GpioBus::Mode::INPUT_PULLED_UP);
    this->_gpioColumns->high();
    this->_gpioColumns->setMode(GpioBus::Mode::OUTPUT_PUSH_PULL);

    // Update data members
    this->_debounceTime = debounceTime_p;
    this->_isInitialized = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return true;
}

bool_t Keypad::setPorts(const GpioBus *gpioLines_p, const GpioBus *gpioColumns_p)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::setPorts(const GpioBus *, const GpioBus *)", Debug::CodeIndex::KEYPAD_MODULE);

    // Local variables
    GpioBus *auxBus;

    // Resets data members
    this->_gpioLines                    = nullptr;
    this->_gpioColumns                  = nullptr;
    this->_isPortsSet                   = false;

    // Check for errors
    if(!isPointerValid(gpioLines_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    if(!isPointerValid(gpioColumns_p)) {
        // Returns error
        this->_lastError = Error::GPIO_PORT_INVALID;
        debugMessage(Error::GPIO_PORT_INVALID, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    auxBus = (GpioBus *)gpioLines_p;
    if(!(auxBus->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    auxBus = (GpioBus *)gpioColumns_p;
    if(!(auxBus->isInitialized())) {
        // Returns error
        this->_lastError = Error::GPIO_NOT_INITIALIZED;
        debugMessage(Error::GPIO_NOT_INITIALIZED, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }

    // Updates data members
    this->_gpioLines                    = (GpioBus *)gpioLines_p;
    this->_gpioColumns                  = (GpioBus *)gpioColumns_p;
    this->_isPortsSet                   = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return true;
}

bool_t Keypad::setKeyValues(Type type_p, ...)
{
    // Marks passage for debugging purpose
    debugMark("Keypad::setKeyValues(Keypad::Type, ...)", Debug::CodeIndex::KEYPAD_MODULE);

    // Resets data members
    this->_isKeyValuesSet               = false;
    if(isPointerValid(this->_keyValue)) {
        free(this->_keyValue);
    }
    this->_keyValue                     = nullptr;

    // Updates data members
    switch(type_p) {
    case Type::KEYPAD_4X4:  this->_linesMax = 3;    this->_columnsMax = 3;  break;
    case Type::KEYPAD_4X3:  this->_linesMax = 3;    this->_columnsMax = 2;  break;
    case Type::KEYPAD_5X3:  this->_linesMax = 4;    this->_columnsMax = 2;  break;
    default:
        // Returns error
        this->_lastError = Error::KEYPAD_TYPE_UNSUPPORTED;
        debugMessage(Error::KEYPAD_TYPE_UNSUPPORTED, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    this->_type                         = type_p;

    // Allocates memory
    this->_keyValue = (uint8_t *)realloc(this->_keyValue, (this->_linesMax + 1) * (this->_columnsMax + 1));
    if(!isPointerValid(this->_keyValue)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION;
        debugMessage(Error::MEMORY_ALLOCATION, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }

    // Updates key values
    do {
        va_list auxArgs;
        va_start(auxArgs, type_p);
        for(uint8_t i = 0; i < (this->_linesMax + 1); i++) {
            for(uint8_t j  = 0; j < (this->_columnsMax + 1); j++) {
                this->_keyValue[((this->_linesMax + 1) *  i) + j] = (uint8_t)va_arg(auxArgs, int16_t);
            }
        }
        va_end(auxArgs);
        this->_isKeyValuesSet = true;
    } while(0);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return true;
}

bool_t Keypad::readKeyPressed(uint8_t *keyPressedValue_p)
{
    // Local variables
    uint8_t auxKey                      = 0xFF;

    // Checks for errors
    if(!this->_isInitialized) {
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }
    if(!isPointerValid(keyPressedValue_p)) {
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::KEYPAD_MODULE);
        return false;
    }

    // Keypad sweep
    for(uint8_t i = 0; i <= this->_columnsMax; i++) {                   // For each column
        this->_gpioColumns->clr(i);                                     // Clear one column
        __builtin_avr_delay_cycles(5);                                  // Wait for syncronization
        uint8_t aux8 = this->_gpioLines->read();                        // Reads lines
        for(uint8_t j = 0; j <= this->_linesMax; j++) {                 // For each line
            if(isBitClr(aux8, j)) {                                     // Tests if the key is pressed
                auxKey = this->_keyValue[((this->_linesMax + 1) * j) + i];      // Decodes the key using the table
                for(uint8_t k = 0; k < this->_debounceTime; k++) {
                    _delay_ms(1);                                       // Debounce time
                }
            }
            // Wait until key is released
            do {
                aux8 = this->_gpioLines->read();
            } while(isBitClr(aux8, j));
        }
        this->_gpioColumns->set();                                      // Restore column value
    }

    // Update function arguments
    *keyPressedValue_p = auxKey;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::KEYPAD_MODULE);
    return true;
}

Error Keypad::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// =============================================================================
// Class private methods
// =============================================================================

// NONE

// =============================================================================
// Class protected methods
// =============================================================================

// NONE

// =============================================================================
// General public functions definitions
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Interrupt handlers
// =============================================================================

// NONE

// =============================================================================
// END OF FILE
// =============================================================================
