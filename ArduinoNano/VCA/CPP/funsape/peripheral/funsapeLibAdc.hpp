//!
//! \file           funsapeLibAdc.hpp
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
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_ADC_HPP
#define __FUNSAPE_LIB_ADC_HPP                   2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_ADC_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_ADC_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#if defined(_FUNSAPE_PLATFORM_AVR)

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Peripherals
//! \brief          Microcontroller peripherals.
//! \{
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Peripherals/Adc"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \addtogroup     Adc
//! \brief          Analog to Digital Converter (ADC) controller module.
//! \{
//!

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

//!
//! \brief          ADC conversion complete callback function.
//! \details        This function is called when the ADC interrupt is treated.
//!                     It is a weak function that can be overwritten by user
//!                     code.
//!
void adcConversionCompleteCallback(void);

// =============================================================================
// Adc Class
// =============================================================================

//!
//! \brief          Adc class.
//! \details        This class manages the Analog to Digital Converter (ADC)
//!                     peripheral.
//! \warning        An instance of this class is already defined as a global
//!                     object. Therefore, there is not necessary, neither
//!                     recommended to create another object of this class.
//!
class Adc
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     //////////////////     ADC Clock Source    ///////////////////     //
    //!
    //! \brief      Clock source enumeration.
    //! \details    Clock prescaler options associated with ADC.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class Prescaler : uint8_t {
        DISABLED                        = 0,    //!< Disables clock, Adc is off.
        PRESCALER_2                     = 1,    //!< Adc clock frequency will be CPU clock divided by 2.
        PRESCALER_4                     = 2,    //!< Adc clock frequency will be CPU clock divided by 4.
        PRESCALER_8                     = 3,    //!< Adc clock frequency will be CPU clock divided by 8.
        PRESCALER_16                    = 4,    //!< Adc clock frequency will be CPU clock divided by 16.
        PRESCALER_32                    = 5,    //!< Adc clock frequency will be CPU clock divided by 32.
        PRESCALER_64                    = 6,    //!< Adc clock frequency will be CPU clock divided by 64.
        PRESCALER_128                   = 7     //!< Adc clock frequency will be CPU clock divided by 128.
    };

    //     //////////////     ADC Full Scale Reference    ///////////////     //
    //!
    //! \brief      Reference enumeration.
    //! \details    Full scale reference source.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class Reference : uint8_t {
        EXTERNAL                        = 0,    //!< Adc full scale reference is the voltage at the AVREF pin.
        POWER_SUPPLY                    = 1,    //!< Adc full scale reference is the voltage of the analog power supply.
        // RESERVED                     = 2,
        INTERNAL                        = 3     //!< Adc full scale reference is the internal 1.1 V bandgap generator.
    };

    //     ///////////////     ADC Channel Selection     ////////////////     //
    //!
    //! \brief      Channel enumeration.
    //! \details    Channel source selection.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class Channel : uint8_t {
        CHANNEL_0                       = 0,    //!< Select the ADC channel 0.
        CHANNEL_1                       = 1,    //!< Select the ADC channel 1.
        CHANNEL_2                       = 2,    //!< Select the ADC channel 2.
        CHANNEL_3                       = 3,    //!< Select the ADC channel 3.
        CHANNEL_4                       = 4,    //!< Select the ADC channel 4.
        CHANNEL_5                       = 5,    //!< Select the ADC channel 5.
        CHANNEL_6                       = 6,    //!< Select the ADC channel 6 (not available on the DIP package).
        CHANNEL_7                       = 7,    //!< Select the ADC channel 7 (not available on the DIP package).
        TEMPERATURE                     = 8,    //!< Select the internal temperature sensor.
        // RESERVED                     = 9,
        // RESERVED                     = 10,
        // RESERVED                     = 11,
        // RESERVED                     = 12,
        // RESERVED                     = 13,
        BAND_GAP                        = 14,   //!< Select the internal bandgap generator.
        GND                             = 15    //!< Select the GND.
    };

    //     /////////////////     ADC Operation Mode    //////////////////     //
    //!
    //! \brief      Mode enumeration.
    //! \details    Operation mode associated with the ADC.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class Mode {
        AUTO_CONTINUOUS                 = 0,    //!< ADC in automatic mode, triggered automatically at the end of the conversion.
        AUTO_ANALOG_COMP                = 1,    //!< ADC in automatic mode, triggered by Analog Comparator.
        AUTO_INT0                       = 2,    //!< ADC in automatic mode, triggered by External Interrupt INT0.
        AUTO_TIMER0_COMPA               = 3,    //!< ADC in automatic mode, triggered by Timer0 Compare A Match.
        AUTO_TIMER0_OVERFLOW            = 4,    //!< ADC in automatic mode, triggered by Timer0 Counter Overflow.
        AUTO_TIMER1_COMPB               = 5,    //!< ADC in automatic mode, triggered by Timer1 Compare B Match.
        AUTO_TIMER1_OVERFLOW            = 6,    //!< ADC in automatic mode, triggered by Timer1 Counter Overflow.
        AUTO_TIMER1_CAPTURE             = 7,    //!< ADC in automatic mode, triggered by Timer1 Input Capture Match.
        SINGLE_CONVERSION               = 15    //!< ADC in sigle mode, triggered by software.
    };

    //     //////////////     ADC Result Presentation     ///////////////     //
    //!
    //! \brief      Data adjust enumeration.
    //! \details    Presentation mode of the ADC result.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class DataAdjust : cbool_t {
        RIGHT                           = 0,    //!< Adjust right. Significant bits are ADC[9...0].
        LEFT                            = 1     //!< Adjust left. Significant bits are ADC[15...6].
    };

    //     ///////////////////     Digital Input     ////////////////////     //
    //!
    //! \brief      Digital input enumeration.
    //! \details    Digital inputs to be enabled/disabled. The values can be
    //!                 'ORed' (|) to select multiple inputs.
    //! \warning    The value associate with the symbolic names may change
    //!                 between builds and might not reflect the register/bits
    //!                 real values. In order to ensure compatibility between
    //!                 builds, always refer to the SYMBOLIC NAME, instead its
    //!                 VALUE.
    //!
    enum class DigitalInput : uint8_t {
        INPUT_0                         = (1 << 0),     //!< Digital input 0.
        INPUT_1                         = (1 << 1),     //!< Digital input 1.
        INPUT_2                         = (1 << 2),     //!< Digital input 2.
        INPUT_3                         = (1 << 3),     //!< Digital input 3.
        INPUT_4                         = (1 << 4),     //!< Digital input 4.
        INPUT_5                         = (1 << 5),     //!< Digital input 5.
        INPUT_6                         = (1 << 6),     //!< Digital input 6.
        INPUT_7                         = (1 << 7)      //!< Digital input 7.
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Adc class constructor.
    //! \details    Creates an Adc object. The object is loaded with the
    //!                 default register values (Channel::CHANNEL_0,
    //!                 DataAdjust::RIGHT, Mode::SINGLE_CONVERSION,
    //!                 Prescaler::DISABLED and Reference::EXTERNAL)). The
    //!                 object still must be initialized before use.
    //! \see        init(Mode mode_p, Reference reference_p, Prescaler prescaler_p).
    //!
    Adc(
            void
    );

    //!
    //! \brief      Adc class destructor.
    //! \details    Destroys an Adc object.
    //!
    ~Adc(
            void
    );

    // -------------------------------------------------------------------------
    // Methods -----------------------------------------------------------------
public:
    //     ///////////////////     CONFIGURATION     ////////////////////     //

    //!
    //! \brief          Initializes the ADC module.
    //! \details        Initializes the ADC module, according to provided
    //!                     operation mode, reference source and clock
    //!                     prescaler.
    //! \param          mode_p          Operation mode.
    //! \param          reference_p     Reference source.
    //! \param          prescaler_p      Clock prescaler value.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t init(
            const Mode mode_p,
            const Reference reference_p,
            const Prescaler prescaler_p
    );

    //!
    //! \brief      Sets data adjust result.
    //! \details    Sets data adjust result.
    //! \param      dataAdjust_p        Data adjust option.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setDataAdjust(
            DataAdjust dataAdjust_p
    );

    //!
    //! \brief      Sets operation mode.
    //! \details    Sets operation mode.
    //! \param      mode_p              Operation mode.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setMode(
            Mode mode_p
    );

    //!
    //! \brief      Sets clock prescaler.
    //! \details    Sets clock prescaler.
    //! \param      prescale_p          Clock prescaler.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setPrescaler(
            Prescaler prescale_p
    );

    //!
    //! \brief      Sets reference source.
    //! \details    Sets reference source.
    //! \param      reference_p         Reference source.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setReference(
            Reference reference_p
    );

    //     //////////////////     CHANNEL CONTROL     ///////////////////     //

    //!
    //! \brief      Disables digital inputs.
    //! \details    Disables digital inputs to save power.
    //! \param      flagInputs_p        Input flags mask to de disabled.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t disableDigitalInput(
            DigitalInput flagInputs_p
    );

    //!
    //! \brief      Enables digital inputs.
    //! \details    Enables digital inputs.
    //! \param      flagInputs_p        Input flags mask to de enabled.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t enableDigitalInput(
            DigitalInput flagInputs_p
    );

    //!
    //! \brief      Sets channel.
    //! \details    Sets the channel to be converted.
    //! \param      channel_p           Channel to be converted.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t setChannel(
            Channel channel_p
    );

    //     /////////////////     INTERRUPT CONTROL     //////////////////     //
    //!
    //! \brief      Activates interrupt.
    //! \details    Activates interrupt. If an interrupt request is pending, an
    //!                 interrupt will be triggered when activated. In most
    //!                 applications, it is recommended to ignore an old
    //!                 interrupt request prior to activate the interrupt. This
    //!                 can be done by calling \ref clearInterruptRequest()
    //!                 function imediatelly before activating the interrupt.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t activateInterrupt(
            void
    );

    //!
    //! \brief      Clears interrupt flag.
    //! \details    Clears the interrupt flag, dismissing any pending interrupt
    //!                 request.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    bool_t clearInterruptRequest(
            void
    );

    //!
    //! \brief      Deactivates interrupt.
    //! \details    Deactivates interrupt. This function does not clears any
    //!                 pending interrupt request.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t deactivateInterrupt(
            void
    );

    //     /////////////     MASTER CONTROL AND STATUS     //////////////     //
    //!
    //! \brief      Turns ADC module on.
    //! \details    Turns ADC module on.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t enable(
            void
    );

    //!
    //! \brief      Turns ADC module off.
    //! \details    Turns ADC module off.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t disable(
            void
    );

    //!
    //! \brief      Returns last error.
    //! \details    Returns the status of the last operation.
    //! \return     Error               Code of the last error.
    //!
    Error getLastError(
            void
    );

    //!
    //! \brief      Checks if ADC module is busy.
    //! \details    Checks if ADC module is busy.
    //! \retval     true                The module is busy.
    //! \retval     false               The module is not busy.
    //!
    bool_t inlined isBusy(void) {
        return isBitSet(ADCSRA, ADSC);
    }

    //!
    //! \brief      Triggers a new conversion.
    //! \details    Triggers a new conversion.
    //! \retval     true                Success.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t startConversion(
            void
    );

    //!
    //! \brief      Waits the end of current conversion.
    //! \details    This function continually pools for the ADC conversion
    //!                 status. The system will be halted while the conversion
    //!                 is in process.
    //! \retval     true                Converion has ended.
    //! \retval     false               Retrieve the error using the \ref
    //!                                     getLastError() function.
    //!
    bool_t waitUntilConversionFinish(
            void
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
private:
    bool_t          _isEnabled          : 1;
    bool_t          _isInitialized      : 1;
    bool_t          _isInterruptEnabled : 1;
    Error           _lastError;
    Prescaler       _prescaler;
    Reference       _reference;
    Channel         _channel;
    Mode            _mode;
    DataAdjust      _dataAdjust         : 1;
}; // class Adc

// =============================================================================
// Inlined class functions
// =============================================================================

//!
//! \cond
//!

//!
//! \brief          Bitwise-or operator overloading
//! \details        Bitwise-or operator overloading for DigitalInput enumeration.
//! \param          a           Param description
//! \param          b           Param description
//! \return         Adc::DigitalInput   DigitalInput flags 'ORed'
//!
Adc::DigitalInput inlined operator|(Adc::DigitalInput a, Adc::DigitalInput b)
{
    return static_cast<Adc::DigitalInput>(static_cast<cuint8_t>(a) | static_cast<cuint8_t>(b));
}

//!
//! \brief          Bitwise-or attribution operator overloading
//! \details        Bitwise-or attribution operator overloading for DigitalInput enumeration.
//! \param          a           Param description
//! \param          b           Param description
//! \return         Adc::DigitalInput&  DigitalInput flags 'ORed'
//!
Adc::DigitalInput inlined &operator|=(Adc::DigitalInput &a, Adc::DigitalInput b)
{
    return a = static_cast<Adc::DigitalInput>(static_cast<uint8_t>(a) | static_cast<cuint8_t>(b));
}

//!
//! \endcond
//!

// =============================================================================
// External global variables
// =============================================================================

//!
//!
//! \brief          Adc peripheral handler object.
//! \details        Adc peripheral handler object.
//! \warning        Use this object to handle the peripheral. DO NOT create
//!                     another instance of the class, since this could lead to
//!                     information mismatch between instances and the
//!                     peripheral registers.
//!
extern Adc adc;

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Peripherals/Adc"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Peripherals"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//!
//! \}
//!

// =============================================================================
// Include guard (END)
// =============================================================================

#endif // defined(_FUNSAPE_PLATFORM_AVR)

#endif  // __FUNSAPE_LIB_ADC_HPP

// =============================================================================
// END OF FILE
// =============================================================================
