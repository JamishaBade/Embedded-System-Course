#include "twi.h"

#include <avr/interrupt.h>
#include <avr/io.h>

int main(void)
{
    DDRB |= (1 << DDB5);

    sei();

    if (twi_init(100000) != TWI_SUCCESS) {
        while (1) {
            PORTB ^= (1 << PORTB5);
        }
    }

    uint8_t who_am_i_register = 0x75;
    uint8_t who_am_i_value = 0;

    twi_message_t messages[] = {
        {
            .address = TWI_WRITE_ADDRESS(0x68),
            .buffer = &who_am_i_register,
            .size = 1
        },
        {
            .address = TWI_READ_ADDRESS(0x68),
            .buffer = &who_am_i_value,
            .size = 1
        }
    };

    if (twi_enqueue(messages, 2) == TWI_SUCCESS) {
        while (!twi_idle()) {
        }
    }

    if (twi_status() == TWI_SUCCESS && who_am_i_value == 0x68) {
        PORTB |= (1 << PORTB5);
    }

    while (1) {
    }
}
