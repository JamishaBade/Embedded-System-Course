#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define SHIFT_DATA  PORTD4
#define SHIFT_LATCH PORTD5
#define SHIFT_CLOCK PORTD6

static const uint8_t DIGIT_MASKS[16] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
    0x77,
    0x7C,
    0x39,
    0x5E,
    0x79,
    0x71
};

static void pulse(uint8_t pin)
{
    PORTD |= (1 << pin);
    PORTD &= ~(1 << pin);
}

static void shift_write(uint8_t value)
{
    for (int8_t bit = 7; bit >= 0; bit--) {
        if (value & (1 << bit)) {
            PORTD |= (1 << SHIFT_DATA);
        } else {
            PORTD &= ~(1 << SHIFT_DATA);
        }

        pulse(SHIFT_CLOCK);
    }

    pulse(SHIFT_LATCH);
}

int main(void)
{
    DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6);

    uint8_t count = 0;

    while (1) {
        shift_write(DIGIT_MASKS[count & 0x0F]);
        count++;
        _delay_ms(500);
    }
}
