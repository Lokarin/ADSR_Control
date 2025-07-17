//!
//! \file           funsapeLibDs1307.cpp
//! \brief          DS1307 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-07-10
//! \version        24.07
//! \copyright      license
//! \details        DS1307 RTC module interface
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibDs1307.hpp"
#if !defined(__FUNSAPE_LIB_DS1307_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_DS1307_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

cuint8_t constDs1307DeviceAddress       = 0x68;
cuint8_t constDs1307RamSize             = 56;

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

Ds1307::Ds1307(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::Ds1307(void)", Debug::CodeIndex::DS1307_MODULE);

    // Resets data members
    this->_clearData();

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return;
}

Ds1307::~Ds1307(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::~Ds1307(void)", Debug::CodeIndex::DS1307_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

bool_t Ds1307::clockStart(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::clockStart(void)", Debug::CodeIndex::DS1307_MODULE);

    // Set counting status
    if(!this->_setCounting(true)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::clockStop(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::clockStop(void)", Debug::CodeIndex::DS1307_MODULE);

    // Set counting status
    if(!this->_setCounting(false)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

Error Ds1307::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Ds1307::init(Bus *busHandler_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::init(Bus *)", Debug::CodeIndex::DS1307_MODULE);

    // Resets data members
    this->_clearData();

    // Check function arguments for errors
    if(!isPointerValid(busHandler_p)) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_POINTER_NULL;
        debugMessage(Error::BUS_HANDLER_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    } else if(busHandler_p->getBusType() != Bus::BusType::TWI) {
        // Returns error
        this->_lastError = Error::BUS_HANDLER_NOT_SUPPORTED;
        debugMessage(Error::BUS_HANDLER_NOT_SUPPORTED, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Update data members
    this->_busHandler = busHandler_p;

    // Try to checks if DS1307 is present
    // FIXME: Implmement this...
    // There is no way to know for sure...
    // XXXXX  Check if bus responds and if data makes sense

    // Mark device as initialized
    this->_initialized = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::setSquareWaveGenerator(const SquareWave squareWave_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::setSquareWaveGenerator(const SquareWave)", Debug::CodeIndex::DS1307_MODULE);

    // Local variables
    bool_t _squareWaveActivation;
    uint8_t _squareWaveFrequency;
    bool_t _squareWaveOffValue;
    uint8_t auxBuffer;

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Process arguments
    switch(squareWave_p) {
    case SquareWave::OFF_LOW:
        _squareWaveActivation = false;
        _squareWaveFrequency = 0;
        _squareWaveOffValue = false;
        break;
    case SquareWave::OFF_HIGH:
        _squareWaveActivation = false;
        _squareWaveFrequency = 0;
        _squareWaveOffValue = true;
        break;
    case SquareWave::CLOCK_1_HZ:
        _squareWaveActivation = true;
        _squareWaveFrequency = 0;
        _squareWaveOffValue = false;
        break;
    case SquareWave::CLOCK_4_KHZ:
        _squareWaveActivation = true;
        _squareWaveFrequency = 1;
        _squareWaveOffValue = false;
        break;
    case SquareWave::CLOCK_8_KHZ:
        _squareWaveActivation = true;
        _squareWaveFrequency = 2;
        _squareWaveOffValue = false;
        break;
    case SquareWave::CLOCK_32_KHZ:
        _squareWaveActivation = true;
        _squareWaveFrequency = 3;
        _squareWaveOffValue = false;
        break;
    default:
        // Returns error
        this->_lastError = Error::UNKNOWN;
        debugMessage(Error::UNKNOWN, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    auxBuffer =
            (_squareWaveOffValue << 7) |
            (_squareWaveActivation << 4) |
            (_squareWaveFrequency << 0);

    // Sends data to device
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_busHandler->writeReg((uint8_t)(Register::CONTROL), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Update data members
    this->_squareWave = squareWave_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

//     /////////////////    DATE HANDLING FUNCTIONS     /////////////////     //

bool_t Ds1307::getDate(uint16_t *year_p, uint8_t *month_p, uint8_t *monthDay_p, uint8_t *weekDay_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::getDate(uint16_t *, uint8_t *, uint8_t *, uint8_t *)", Debug::CodeIndex::DS1307_MODULE);

    // Local variables
    uint16_t auxYear;
    DateTime::Month auxMonth;
    uint8_t auxMonthDay;
    DateTime::WeekDay auxWeekDay;

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if((!isPointerValid(year_p)) || (!isPointerValid(month_p)) || (!isPointerValid(monthDay_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Get last data from device
    if(!this->_getData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Retrieve data
    if(isPointerValid(weekDay_p)) {
        if(!this->_dateTime.getDate(&auxYear, &auxMonth, &auxMonthDay, &auxWeekDay)) {
            // Returns error
            this->_lastError = this->_dateTime.getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
            return false;
        }
        *weekDay_p = (uint8_t)auxWeekDay;
    } else {
        if(!this->_dateTime.getDate(&auxYear, &auxMonth, &auxMonthDay)) {
            // Returns error
            this->_lastError = this->_dateTime.getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
            return false;
        }
    }
    *year_p = auxYear;
    *month_p = (uint8_t)(auxMonth);
    *monthDay_p = auxMonthDay;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::getDateTime(DateTime *dateTime_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::getDateTime(DateTime *)", Debug::CodeIndex::DS1307_MODULE);

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if(!isPointerValid(dateTime_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Get last data from device
    if(!this->_getData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Retrieve data
    *dateTime_p = this->_dateTime;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::setDate(uint16_t year_p, uint8_t month_p, uint8_t monthDay_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::setDate(uint16_t, uint8_t, uint8_t)", Debug::CodeIndex::DS1307_MODULE);

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Update data members - Date is checked inside DateTime class
    if(!this->_dateTime.setDate(year_p, (DateTime::Month)month_p, monthDay_p)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Send data to device
    if(!this->_sendData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::setDateTime(DateTime dateTime_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::setDateTime(DateTime)", Debug::CodeIndex::DS1307_MODULE);

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // Checks DateTime parameter
    if(!dateTime_p.isDateSet()) {
        // Returns error
        this->_lastError = Error::DATE_NOT_INITIALIZED;
        debugMessage(Error::DATE_NOT_INITIALIZED, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!dateTime_p.isTimeSet()) {
        // Returns error
        this->_lastError = Error::TIME_NOT_INITIALIZED;
        debugMessage(Error::TIME_NOT_INITIALIZED, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Update data members
    this->_dateTime = dateTime_p;

    // Sends data to device
    if(!this->_sendData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

//     /////////////////    TIME HANDLING FUNCTIONS     /////////////////     //

bool_t Ds1307::getTime(uint8_t *hours_p, uint8_t *minutes_p, uint8_t *seconds_p, DateTime::TimeFormat timeFormat_p,
        DateTime::AmPmFlag *amPmFlag_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::getTime(uint8_t *, uint8_t *, uint8_t *, DateTime::TimeFormat, DateTime::AmPmFlag *)"
            , Debug::CodeIndex::DS1307_MODULE);

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - invalid pointers
    if((!isPointerValid(hours_p)) || (!isPointerValid(minutes_p)) || (!isPointerValid(seconds_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if((timeFormat_p == DateTime::TimeFormat::FORMAT_12_HOURS) && (!isPointerValid(amPmFlag_p))) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Get last data from device
    if(!this->_getData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Retrieve data
    if(!this->_dateTime.getTime(hours_p, minutes_p, seconds_p, timeFormat_p, amPmFlag_p)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::setTime(uint8_t hours_p, uint8_t minutes_p, uint8_t seconds_p, DateTime::TimeFormat timeFormat_p,
        DateTime::AmPmFlag amPmFlag_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::setTime(uint8_t, uint8_t, uint8_t, DateTime::TimeFormat, DateTime::AmPmFlag)",
            Debug::CodeIndex::DS1307_MODULE);

    // Checks initialization
    if(!this->_isInitialized()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Update data members - Time is checked inside DateTime class
    if(!this->_dateTime.setTime(hours_p, minutes_p, seconds_p, timeFormat_p, amPmFlag_p)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Send data to device
    if(!this->_sendData()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

//     ///////////////    RAM DATA HANDLING FUNCTIONS     ///////////////     //

bool_t Ds1307::getRamData(uint8_t position_p, uint8_t *buffer_p, uint8_t size_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::getRamData(uint8_t, uint8_t *, uint8_t)", Debug::CodeIndex::DS1307_MODULE);

    // CHECK FOR ERROR - invalid pointer
    if(!isPointerValid(buffer_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - wrong number of bytes to receive
    if(size_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(size_p > constDs1307RamSize) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - position invalid
    if(position_p > (constDs1307RamSize - 1)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - memory overlap
    if((position_p + size_p) > constDs1307RamSize) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Read RAM data
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    position_p += (uint8_t)(Register::RAM_START);
    if(!this->_busHandler->readReg(position_p, buffer_p, size_p)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::setRamData(uint8_t position_p, uint8_t *buffer_p, uint8_t size_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::setRamData(uint8_t, uint8_t *, uint8_t)", Debug::CodeIndex::DS1307_MODULE);

    // CHECK FOR ERROR - invalid pointer
    if(!isPointerValid(buffer_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - wrong number of bytes to receive
    if(size_p == 0) {
        // Returns error
        this->_lastError = Error::ARGUMENT_CANNOT_BE_ZERO;
        debugMessage(Error::ARGUMENT_CANNOT_BE_ZERO, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(size_p > constDs1307RamSize) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - position invalid
    if(position_p > (constDs1307RamSize - 1)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_VALUE_INVALID;
        debugMessage(Error::ARGUMENT_VALUE_INVALID, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    // CHECK FOR ERROR - memory overlap
    if((position_p + size_p) > constDs1307RamSize) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_LARGE;
        debugMessage(Error::BUFFER_SIZE_TOO_LARGE, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Write RAM data
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    position_p += (uint8_t)(Register::RAM_START);
    if(!this->_busHandler->writeReg(position_p, buffer_p, size_p)) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

// =============================================================================
// Class private methods
// =============================================================================

void Ds1307::_clearData(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::_clearData(void)", Debug::CodeIndex::DS1307_MODULE);

    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    this->_busHandler                   = nullptr;
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    this->_countingHalted               = false;
    this->_initialized                  = false;
    this->_squareWave                   = SquareWave::OFF_LOW;
    this->_dateTime.setDate(
            2000,
            DateTime::Month::JANUARY,
            1
    );
    this->_dateTime.setTime(
            0,
            0,
            0
    );

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return;
}

bool_t Ds1307::_isInitialized(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::_isInitialized(void)", Debug::CodeIndex::DS1307_MODULE);

    // CHECK FOR ERROR - peripheral not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::_getData(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::_getData(void)", Debug::CodeIndex::DS1307_MODULE);

    // Local variables
    uint8_t auxBuffer[7];
    uint8_t auxSeconds;
    uint8_t auxMinutes;
    uint8_t auxHours;
    uint16_t auxYear;
    uint8_t auxMonth;
    uint8_t auxMonthDay;
    DateTime::TimeFormat auxTimeFormat;
    DateTime::AmPmFlag auxAmPmFlag;

    // Reads data from device
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)(Register::SECONDS), auxBuffer, 7)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Decodes the information
    this->_countingHalted = isBitSet(auxBuffer[0], 7);
    auxBuffer[0] &= 0x7F;
    auxSeconds = ((auxBuffer[0] >> 4) * 10) + (auxBuffer[0] & 0x0F);
    auxMinutes = ((auxBuffer[1] >> 4) * 10) + (auxBuffer[1] & 0x0F);
    if(isBitSet(auxBuffer[2], 6)) {  // 12 hour-mode
        auxHours = (((auxBuffer[2] & 0x10) >> 4) * 10) + (auxBuffer[2] & 0x0F);
        auxTimeFormat = DateTime::TimeFormat::FORMAT_12_HOURS;
        auxAmPmFlag = (isBitSet(auxBuffer[2], 5)) ? DateTime::AmPmFlag::PM : DateTime::AmPmFlag::AM;
    } else {                        // 24 hour-mode
        auxHours = (((auxBuffer[2] & 0x30) >> 4) * 10) + (auxBuffer[2] & 0x0F);
        auxTimeFormat = DateTime::TimeFormat::FORMAT_24_HOURS;
        auxAmPmFlag = DateTime::AmPmFlag::AM;
    }
    auxMonthDay = ((auxBuffer[4] >> 4) * 10) + (auxBuffer[4] & 0x0F);
    auxMonth = ((auxBuffer[5] >> 4) * 10) + (auxBuffer[5] & 0x0F);
    auxYear = ((auxBuffer[6] >> 4) * 10) + (auxBuffer[6] & 0x0F);
    auxYear += 2000;

    // Update data members
    if(!this->_dateTime.setTime(auxHours, auxMinutes, auxSeconds, auxTimeFormat, auxAmPmFlag)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_dateTime.setDate(auxYear, (DateTime::Month)auxMonth, auxMonthDay)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::_sendData(void)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::_sendData(void)", Debug::CodeIndex::DS1307_MODULE);

    // Local variables
    uint8_t auxBuffer[7];
    uint8_t auxSeconds;
    uint8_t auxMinutes;
    uint8_t auxHours;
    DateTime::WeekDay auxWeekDay;
    uint8_t auxMonthDay;
    DateTime::Month auxMonth;
    uint16_t auxYear;
    DateTime::TimeFormat auxTimeFormat;
    DateTime::AmPmFlag auxAmPmFlag;

    // Gets the data from class members
    if(!this->_dateTime.getTimeFormat(&auxTimeFormat)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_dateTime.getTime(&auxHours, &auxMinutes, &auxSeconds, auxTimeFormat, &auxAmPmFlag)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_dateTime.getDate(&auxYear, &auxMonth, &auxMonthDay, &auxWeekDay)) {
        // Returns error
        this->_lastError = this->_dateTime.getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    if(auxYear > 1999) {
        auxYear -= 2000;
    }

    // Encode the information
    auxBuffer[0] = ((auxSeconds / 10) << 4) | (auxSeconds % 10);
    auxBuffer[0] |= this->_countingHalted << 7;
    auxBuffer[1] = ((auxMinutes / 10) << 4) | (auxMinutes % 10);
    auxBuffer[2] = ((auxHours / 10) << 4) | (auxHours % 10);
    if(auxTimeFormat == DateTime::TimeFormat::FORMAT_12_HOURS) {
        auxBuffer[2] |= 0x40;
        auxBuffer[2] |= ((auxAmPmFlag == DateTime::AmPmFlag::PM) ? (1 << 5) : 0);
    }
    auxBuffer[3] = (uint8_t)(auxWeekDay);
    auxBuffer[4] = ((auxMonthDay / 10) << 4) | (auxMonthDay % 10);
    auxBuffer[5] = (((uint8_t)(auxMonth) / 10) << 4) | ((uint8_t)(auxMonth) % 10);
    auxBuffer[6] = ((auxYear / 10) << 4) | (auxYear % 10);

    // Writes data at device
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_busHandler->writeReg((uint8_t)(Register::SECONDS), auxBuffer, 7)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

bool_t Ds1307::_setCounting(bool counting_p)
{
    // Mark passage for debugging purpose
    debugMark("Ds1307::_setCounting(bool)", Debug::CodeIndex::DS1307_MODULE);

    // Local variables
    uint8_t auxBuffer;
    bool isCounting;

    // Read register data from device
    if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    if(!this->_busHandler->readReg((uint8_t)(Register::SECONDS), &auxBuffer, 1)) {
        // Returns error
        this->_lastError = this->_busHandler->getLastError();
        debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
        return false;
    }
    isCounting = isBitClr(auxBuffer, 7);

    // Update buffer
    if(isCounting != counting_p) {
        if(counting_p) {
            clrBit(auxBuffer, 7);
        } else {
            setBit(auxBuffer, 7);
        }
        // Writes data at device
        if(!this->_busHandler->setDevice(constDs1307DeviceAddress)) {
            // Returns error
            this->_lastError = this->_busHandler->getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
            return false;
        }
        if(!this->_busHandler->writeReg((uint8_t)(Register::SECONDS), &auxBuffer, 1)) {
            // Returns error
            this->_lastError = this->_busHandler->getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::DS1307_MODULE);
            return false;
        }
    }

    // Update data members
    this->_countingHalted = !counting_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::DS1307_MODULE);
    return true;
}

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
