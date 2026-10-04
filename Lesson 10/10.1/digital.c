#include "digital.h"

#include <avr/io.h>
#include <stddef.h>

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
    uint8_t bit;
} digital_pin_t;

static bool lookup_pin(uint8_t arduino_pin, digital_pin_t *mapped)
{
    if (mapped == NULL) {
        return false;
    }

    if (arduino_pin <= 7) {
        mapped->ddr = &DDRD;
        mapped->port = &PORTD;
        mapped->pin = &PIND;
        mapped->bit = arduino_pin;
        return true;
    }

    if (arduino_pin <= 13) {
        mapped->ddr = &DDRB;
        mapped->port = &PORTB;
        mapped->pin = &PINB;
        mapped->bit = arduino_pin - 8;
        return true;
    }

    if (arduino_pin <= 19) {
        mapped->ddr = &DDRC;
        mapped->port = &PORTC;
        mapped->pin = &PINC;
        mapped->bit = arduino_pin - 14;
        return true;
    }

    return false;
}

bool digital_pin_mode(uint8_t pin, digital_mode_t mode)
{
    digital_pin_t mapped;

    if (!lookup_pin(pin, &mapped)) {
        return false;
    }

    switch (mode) {
        case DIGITAL_INPUT:
            *mapped.ddr &= ~(1 << mapped.bit);
            *mapped.port &= ~(1 << mapped.bit);
            break;

        case DIGITAL_OUTPUT:
            *mapped.ddr |= (1 << mapped.bit);
            break;

        case DIGITAL_INPUT_PULLUP:
            *mapped.ddr &= ~(1 << mapped.bit);
            *mapped.port |= (1 << mapped.bit);
            break;

        default:
            return false;
    }

    return true;
}

bool digital_write(uint8_t pin, bool high)
{
    digital_pin_t mapped;

    if (!lookup_pin(pin, &mapped)) {
        return false;
    }

    if (high) {
        *mapped.port |= (1 << mapped.bit);
    } else {
        *mapped.port &= ~(1 << mapped.bit);
    }

    return true;
}

bool digital_read(uint8_t pin, bool *pin_state)
{
    digital_pin_t mapped;

    if (pin_state == NULL || !lookup_pin(pin, &mapped)) {
        return false;
    }

    *pin_state = (*mapped.pin & (1 << mapped.bit)) != 0;
    return true;
}
