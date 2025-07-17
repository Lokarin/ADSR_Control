
#ifndef __FUNSAPE_LIB_SOUND_HPP
#define __FUNSAPE_LIB_SOUND_HPP

#include "../funsapeLibGlobalDefines.hpp"
#include "../peripheral/funsapeLibTimer1.hpp"

#if defined(_FUNSAPE_PLATFORM_AVR)

enum class Note : uint8_t {
    NOTE_C0             = 0,
    NOTE_CS0            = 1,
    NOTE_D0             = 2,
    NOTE_DS0            = 3,
    NOTE_E0             = 4,
    NOTE_F0             = 5,
    NOTE_FS0            = 6,
    NOTE_G0             = 7,
    NOTE_GS0            = 8,
    NOTE_A0             = 9,
    NOTE_AS0            = 10,
    NOTE_B0             = 11,
    NOTE_C1             = 12,
    NOTE_CS1            = 13,
    NOTE_D1             = 14,
    NOTE_DS1            = 15,
    NOTE_E1             = 16,
    NOTE_F1             = 17,
    NOTE_FS1            = 18,
    NOTE_G1             = 19,
    NOTE_GS1            = 20,
    NOTE_A1             = 21,
    NOTE_AS1            = 22,
    NOTE_B1             = 23,
    NOTE_C2             = 24,
    NOTE_CS2            = 25,
    NOTE_D2             = 26,
    NOTE_DS2            = 27,
    NOTE_E2             = 28,
    NOTE_F2             = 29,
    NOTE_FS2            = 30,
    NOTE_G2             = 31,
    NOTE_GS2            = 32,
    NOTE_A2             = 33,
    NOTE_AS2            = 34,
    NOTE_B2             = 35,
    NOTE_C3             = 36,
    NOTE_CS3            = 37,
    NOTE_D3             = 38,
    NOTE_DS3            = 39,
    NOTE_E3             = 40,
    NOTE_F3             = 41,
    NOTE_FS3            = 42,
    NOTE_G3             = 43,
    NOTE_GS3            = 44,
    NOTE_A3             = 45,
    NOTE_AS3            = 46,
    NOTE_B3             = 47,
    NOTE_C4             = 48,
    NOTE_CS4            = 49,
    NOTE_D4             = 50,
    NOTE_DS4            = 51,
    NOTE_E4             = 52,
    NOTE_F4             = 53,
    NOTE_FS4            = 54,
    NOTE_G4             = 55,
    NOTE_GS4            = 56,
    NOTE_A4             = 57,
    NOTE_AS4            = 58,
    NOTE_B4             = 59,
    NOTE_C5             = 60,
    NOTE_CS5            = 61,
    NOTE_D5             = 62,
    NOTE_DS5            = 63,
    NOTE_E5             = 64,
    NOTE_F5             = 65,
    NOTE_FS5            = 66,
    NOTE_G5             = 67,
    NOTE_GS5            = 68,
    NOTE_A5             = 69,
    NOTE_AS5            = 70,
    NOTE_B5             = 71,
    NOTE_C6             = 72,
    NOTE_CS6            = 73,
    NOTE_D6             = 74,
    NOTE_DS6            = 75,
    NOTE_E6             = 76,
    NOTE_F6             = 77,
    NOTE_FS6            = 78,
    NOTE_G6             = 79,
    NOTE_GS6            = 80,
    NOTE_A6             = 81,
    NOTE_AS6            = 82,
    NOTE_B6             = 83,
    NOTE_C7             = 84,
    NOTE_CS7            = 85,
    NOTE_D7             = 86,
    NOTE_DS7            = 87,
    NOTE_E7             = 88,
    NOTE_F7             = 89,
    NOTE_FS7            = 90,
    NOTE_G7             = 91,
    NOTE_GS7            = 92,
    NOTE_A7             = 93,
    NOTE_AS7            = 94,
    NOTE_B7             = 95,
    NOTE_C8             = 96,
    NOTE_CS8            = 97,
    NOTE_D8             = 98,
    NOTE_DS8            = 99,
    NOTE_E8             = 100,
    NOTE_F8             = 101,
    NOTE_FS8            = 102,
    NOTE_G8             = 103,
    NOTE_GS8            = 104,
    NOTE_A8             = 105,
    NOTE_AS8            = 106,
    NOTE_B8             = 107,
    END                 = 108
};

inline bool operator==(const Note note1, const Note note2)
{
    return static_cast<uint8_t>(note1) == static_cast<uint8_t>(note2);
}

inline bool operator!=(const Note note1, const Note note2)
{
    return !(note1 == note2);
}

Timer1::ClockSource notesPrescaler[] = {Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_8, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1, Timer1::ClockSource::PRESCALER_1};

cuint16_t notesOcrValue[] = {61161, 57736, 54495, 51413, 48543, 45808, 43252, 40815, 38520, 36363, 34316, 32393, 30580, 28859, 27240, 25713, 24271, 22909, 21621, 20407, 19263, 18181, 17160, 16196, 15287, 14429, 13619, 12856, 12133, 11452, 10810, 10203, 9630, 9090, 8580, 64792, 61156, 57723, 54484, 51426, 48540, 45815, 43242, 40815, 38525, 36363, 34322, 32396, 30577, 28861, 27241, 25712, 24269, 22907, 21621, 20407, 19262, 18181, 17160, 16197, 15288, 14430, 13620, 12856, 12134, 11453, 10810, 10203, 9630, 9090, 8580, 8098, 7644, 7214, 6809, 6427, 6066, 5726, 5404, 5101, 4815, 4544, 4289, 4049, 3821, 3607, 3404, 3213, 3033, 2862, 2702, 2550, 2407, 2272, 2144, 2024, 1910, 1803, 1702, 1606, 1516, 1431, 1350, 1275, 1203, 1135, 1072, 1011};

bool_t playNotes(Note *notes_p);

#endif // defined(_FUNSAPE_PLATFORM_AVR)

#endif
