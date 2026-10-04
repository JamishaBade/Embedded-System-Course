#ifndef DIGITAL_H
#define DIGITAL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DIGITAL_INPUT,
    DIGITAL_OUTPUT,
    DIGITAL_INPUT_PULLUP
} digital_mode_t;

bool digital_pin_mode(uint8_t pin, digital_mode_t mode);
bool digital_write(uint8_t pin, bool high);
bool digital_read(uint8_t pin, bool *pin_state);

#endif
