//!
//! \file           funsapeLibAdc.cpp
//! \brief          Analog-to-Digital Converter peripheral control for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-05-08
//! \version        24.05
//! \copyright      license
//! \details        Analog-to-Digital Converter peripheral module control for
//!                     the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibAdc.hpp"
#if !defined(__FUNSAPE_LIB_ADC_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_ADC_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// File exclusive - Constants
// =============================================================================

#define DEBUG_ADC                       0x0FFF

cuint8_t constChannelOffset             = MUX0;     //!< Channel bit position offset
cuint8_t constChannelMask               = 0x0F;     //!< Channel bit mask
cuint8_t constReferenceOffset           = REFS0;    //!< Reference source bit position offset
cuint8_t constReferenceMask             = 0x03;     //!< Reference source bit mask
cuint8_t constPrescalerOffset           = ADPS0;    //!< Clock prescaler bit position offset
cuint8_t constPrescalerMask             = 0x07;     //!< Clock prescaler bit mask
cuint8_t constTriggerSourceOffset       = ADTS0;    //!< Conversion trigger bit position offset
cuint8_t constTriggerSourceMask         = 0x07;     //!< Conversion trigger bit mask

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

Adc adc;

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

Adc::Adc()
{
    // Mark passage for debugging purpose
    debugMark("Adc::Adc(void)", DEBUG_ADC);

    // Reset data members
    this->_channel                      = Channel::CHANNEL_0;
    this->_dataAdjust                   = DataAdjust::RIGHT;
    this->_isEnabled                    = false;
    this->_isInitialized                = false;
    this->_isInterruptEnabled           = false;
    this->_mode                         = Mode::SINGLE_CONVERSION;
    this->_prescaler                    = Prescaler::DISABLED;
    this->_reference                    = Reference::EXTERNAL;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return;
}

Adc::~Adc()
{
    // Returns successfully
    debugMessage(Error::NONE, DEBUG_ADC);
    return;
}

// =============================================================================
// Class public methods
// =============================================================================

//     ///////////////////     CONFIGURATION     ////////////////////     //
bool_t Adc::init(Mode mode_p, Reference reference_p, Prescaler prescaler_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::init(Mode, Reference, Prescaler)", DEBUG_ADC);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;
    uint8_t auxAdmux = ADMUX;

    // Configure mode
    clrMaskOffset(auxAdcsrB, constTriggerSourceMask, constTriggerSourceOffset);
    if(mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        setMaskOffset(auxAdcsrB, (uint8_t)mode_p, constTriggerSourceOffset);
    }
    // Configure reference
    clrMaskOffset(auxAdmux, constReferenceMask, constReferenceOffset);
    setMaskOffset(auxAdmux, (uint8_t)reference_p, constReferenceOffset);
    // Configure prescaler
    clrMaskOffset(auxAdcsrA, constPrescalerMask, constPrescalerOffset);
    setMaskOffset(auxAdcsrA, (uint8_t)prescaler_p, constPrescalerOffset);

    // Update registers
    ADMUX = auxAdmux;
    ADCSRA = auxAdcsrA;
    ADCSRB = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;
    this->_reference        = reference_p;
    this->_prescaler        = prescaler_p;
    this->_isInitialized    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::setDataAdjust(DataAdjust data_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::setDataAdjust(DataAdjust)", DEBUG_ADC);

    // Configure Data Adjustment
    if(data_p == DataAdjust::RIGHT) {
        clrBit(ADMUX, ADLAR);
    } else {
        setBit(ADMUX, ADLAR);
    }

    // Update class members
    this->_dataAdjust       = data_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::setMode(Mode mode_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::setMode(Mode)", DEBUG_ADC);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;
    uint8_t auxAdcsrB = ADCSRB;

    // Configure mode
    clrMaskOffset(auxAdcsrB, constTriggerSourceMask, constTriggerSourceOffset);
    if(mode_p == Mode::SINGLE_CONVERSION) {
        clrBit(auxAdcsrA, ADATE);
    } else {
        setBit(auxAdcsrA, ADATE);
        setMaskOffset(auxAdcsrB, (uint8_t)mode_p, constTriggerSourceOffset);
    }

    // Update registers
    ADCSRA = auxAdcsrA;
    ADCSRB = auxAdcsrB;

    // Update class members
    this->_mode             = mode_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::setPrescaler(Prescaler prescale_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::setPrescaler(Prescaler)", DEBUG_ADC);

    // Local variables
    uint8_t auxAdcsrA = ADCSRA;

    // Configure prescaler
    clrMaskOffset(auxAdcsrA, constPrescalerMask, constPrescalerOffset);
    setMaskOffset(auxAdcsrA, (uint8_t)prescale_p, constPrescalerOffset);

    // Update registers
    ADCSRA = auxAdcsrA;

    // Update class members
    this->_prescaler        = prescale_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::setReference(Reference reference_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::setReference(Reference)", DEBUG_ADC);

    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure reference
    clrMaskOffset(auxAdmux, constReferenceMask, constReferenceOffset);
    setMaskOffset(auxAdmux, (uint8_t)reference_p, constReferenceOffset);

    // Update registers
    ADMUX = auxAdmux;

    // Update class members
    this->_reference        = reference_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

//     //////////////////     CHANNEL CONTROL     ///////////////////     //
bool_t Adc::disableDigitalInput(DigitalInput flagInputs_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::disableDigitalInput(DigitalInput)", DEBUG_ADC);

    // TODO: Implement function
    this->_lastError = Error::NOT_IMPLEMENTED;
    debugMessage(Error::NOT_IMPLEMENTED, DEBUG_ADC);
    return false;
}

bool_t Adc::enableDigitalInput(DigitalInput flagInputs_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::enableDigitalInput(DigitalInput)", DEBUG_ADC);

    // TODO: Implement function
    this->_lastError = Error::NOT_IMPLEMENTED;
    debugMessage(Error::NOT_IMPLEMENTED, DEBUG_ADC);
    return false;
}

bool_t Adc::setChannel(Channel channel_p)
{
    // Mark passage for debugging purpose
    debugMark("Adc::setChannel(Channel)", DEBUG_ADC);

    // Local variables
    uint8_t auxAdmux = ADMUX;

    // Configure reference
    clrMaskOffset(auxAdmux, constChannelMask, constChannelOffset);
    setMaskOffset(auxAdmux, (uint8_t)channel_p, constChannelOffset);

    // Update registers
    ADMUX = auxAdmux;

    // Update class members
    this->_channel          = channel_p;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

//     /////////////////     INTERRUPT CONTROL     //////////////////     //
bool_t Adc::activateInterrupt(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::activateInterrupt(void)", DEBUG_ADC);

    // Configure Interrupt
    setBit(ADCSRA, ADIE);

    // Update class members
    this->_isInterruptEnabled           = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::clearInterruptRequest(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::clearInterruptRequest(void)", DEBUG_ADC);

    // Configure Interrupt
    setBit(ADCSRA, ADIF);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::deactivateInterrupt(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::deactivateInterrupt(void)", DEBUG_ADC);

    // Configure Interrupt
    clrBit(ADCSRA, ADIE);

    // Update class members
    this->_isInterruptEnabled           = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

//     /////////////     MASTER CONTROL AND STATUS     //////////////     //
bool_t Adc::enable(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::enable(void)", DEBUG_ADC);

    // Enables ADC
    setBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::disable(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::disable(void)", DEBUG_ADC);

    // Disables ADC
    clrBit(ADCSRA, ADEN);

    // Update class members
    this->_isEnabled                    = false;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

Error Adc::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t Adc::startConversion(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::startConversion(void)", DEBUG_ADC);

    // Starts conversion
    setBit(ADCSRA, ADSC);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
}

bool_t Adc::waitUntilConversionFinish(void)
{
    // Mark passage for debugging purpose
    debugMark("Adc::waitUntilConversionFinish(void)", DEBUG_ADC);

    waitUntilBitIsClear(ADCSRA, ADSC);

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, DEBUG_ADC);
    return true;
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

weakened void adcConversionCompleteCallback(void)
{
    return;
}

// =============================================================================
// Interruption handlers
// =============================================================================

//!
//! \brief          ADC interrupt service routine
//! \details        ADC interrupt service routine.
//!
ISR(ADC_vect)
{
    adcConversionCompleteCallback();
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)

// =============================================================================
// END OF FILE
// =============================================================================
