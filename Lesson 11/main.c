#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/atomic.h>

#define TIMER0_PRESCALER 64UL
#define TIMER0_OVERFLOW_US ((TIMER0_PRESCALER * 256UL * 1000000UL) / F_CPU)

static volatile uint32_t milliseconds = 0;
static volatile uint16_t microsecond_remainder = 0;

ISR(TIMER0_OVF_vect)
{
    microsecond_remainder += TIMER0_OVERFLOW_US;

    while (microsecond_remainder >= 1000) {
        milliseconds++;
        microsecond_remainder -= 1000;
    }
}

static uint32_t millis_avr(void)
{
    uint32_t copy = 0;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        copy = milliseconds;
    }

    return copy;
}

int main(void)
{
    DDRB |= (1 << DDB5);

    TCCR0A = 0;
    TCCR0B = (1 << CS01) | (1 << CS00);
    TCNT0 = 0;
    TIMSK0 = (1 << TOIE0);

    sei();

    uint32_t previous = millis_avr();

    while (1) {
        uint32_t now = millis_avr();

        if (now - previous >= 500) {
            PORTB ^= (1 << PORTB5);
            previous = now;
        }
    }
}
