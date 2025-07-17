
#include "funsapeLibSound.hpp"

#if defined(_FUNSAPE_PLATFORM_AVR)

bool_t playNotes(Note *notes_p)
{
    uint8_t i = 0;

    while(notes_p[i] != Note::END) {
        timer1.setCounterValue(0);
        timer1.setClockSource(notesPrescaler[(uint8_t)notes_p[i]]);
        timer1.setCompareAValue(notesOcrValue[(uint8_t)notes_p[i]]);
        i++;
        delayMs(125);
    }
    timer1.setCounterValue(0);
    timer1.setClockSource(Timer1::ClockSource::DISABLED);
    clrBit(PORTB, PB1);

    return true;
}

#endif // defined(_FUNSAPE_PLATFORM_AVR)
