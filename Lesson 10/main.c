#include "digital.h"

#include <stdbool.h>
#include <stdint.h>
#include <util/delay.h>

enum {
    COIN_PIN = 2,
    SELECT_PIN = 3,
    VEND_PIN = 4,
    RETURN_PIN = 5,
    READY_LED = 9,
    DISPENSE_LED = 10,
    ERROR_LED = 11
};

typedef enum {
    AWAIT_PAYMENT,
    READY,
    DISPENSE,
    RETURN_CREDIT,
    OUT_OF_STOCK
} machine_state_t;

typedef struct {
    uint8_t cost;
    uint8_t stock;
} product_t;

static product_t products[] = {
    {4, 3},
    {3, 4},
    {5, 2}
};

static bool button_pressed(uint8_t pin)
{
    bool first = true;
    bool second = true;

    digital_read(pin, &first);
    _delay_ms(20);
    digital_read(pin, &second);

    return first && !second;
}

int main(void)
{
    machine_state_t state = AWAIT_PAYMENT;
    uint8_t selected = 0;
    uint8_t credit = 0;

    digital_pin_mode(COIN_PIN, DIGITAL_INPUT_PULLUP);
    digital_pin_mode(SELECT_PIN, DIGITAL_INPUT_PULLUP);
    digital_pin_mode(VEND_PIN, DIGITAL_INPUT_PULLUP);
    digital_pin_mode(RETURN_PIN, DIGITAL_INPUT_PULLUP);
    digital_pin_mode(READY_LED, DIGITAL_OUTPUT);
    digital_pin_mode(DISPENSE_LED, DIGITAL_OUTPUT);
    digital_pin_mode(ERROR_LED, DIGITAL_OUTPUT);

    while (1) {
        if (button_pressed(COIN_PIN)) {
            credit++;
        }

        if (button_pressed(SELECT_PIN)) {
            selected = (selected + 1) % (sizeof(products) / sizeof(products[0]));
            state = AWAIT_PAYMENT;
        }

        if (button_pressed(RETURN_PIN)) {
            state = RETURN_CREDIT;
        }

        switch (state) {
            case AWAIT_PAYMENT:
                if (credit >= products[selected].cost) {
                    state = READY;
                }
                break;

            case READY:
                if (button_pressed(VEND_PIN)) {
                    if (products[selected].stock == 0) {
                        state = OUT_OF_STOCK;
                    } else {
                        credit -= products[selected].cost;
                        products[selected].stock--;
                        state = DISPENSE;
                    }
                }
                break;

            case DISPENSE:
                digital_write(DISPENSE_LED, true);
                _delay_ms(600);
                digital_write(DISPENSE_LED, false);
                state = credit > 0 ? RETURN_CREDIT : AWAIT_PAYMENT;
                break;

            case RETURN_CREDIT:
                credit = 0;
                state = AWAIT_PAYMENT;
                break;

            case OUT_OF_STOCK:
                if (button_pressed(SELECT_PIN) || button_pressed(RETURN_PIN)) {
                    state = AWAIT_PAYMENT;
                }
                break;
        }

        digital_write(READY_LED, state == READY);
        digital_write(ERROR_LED, state == OUT_OF_STOCK);
    }
}
