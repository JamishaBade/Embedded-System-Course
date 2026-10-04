#include "twi.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <util/twi.h>

typedef struct {
    volatile bool busy;
    volatile twi_status_t status;
    twi_message_t *messages;
    volatile size_t message_count;
    volatile size_t message_index;
    volatile size_t byte_index;
} twi_context_t;

static twi_context_t context = {
    .busy = false,
    .status = TWI_DISABLED,
    .messages = 0,
    .message_count = 0,
    .message_index = 0,
    .byte_index = 0
};

static void twi_continue(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
}

static void twi_continue_ack(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
}

static void twi_start(void)
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);
}

static void twi_stop(twi_status_t status)
{
    context.status = status;
    context.busy = false;
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE);
}

static void complete_message(void)
{
    context.message_index++;
    context.byte_index = 0;

    if (context.message_index < context.message_count) {
        twi_start();
    } else {
        twi_stop(TWI_SUCCESS);
    }
}

static bool configure_clock(uint32_t scl_hz)
{
    static const uint16_t prescalers[] = {1, 4, 16, 64};

    if (scl_hz == 0) {
        return false;
    }

    for (uint8_t code = 0; code < 4; code++) {
        uint32_t denominator = 2UL * prescalers[code] * scl_hz;

        if (F_CPU <= (16UL * scl_hz)) {
            return false;
        }

        uint32_t twbr = (F_CPU - (16UL * scl_hz)) / denominator;

        if (twbr > 0 && twbr <= 255) {
            TWSR = (TWSR & ~0x03) | code;
            TWBR = (uint8_t)twbr;
            return true;
        }
    }

    return false;
}

twi_status_t twi_init(uint32_t scl_hz)
{
    DDRC &= ~((1 << DDC4) | (1 << DDC5));
    PORTC |= (1 << PORTC4) | (1 << PORTC5);

    if (!configure_clock(scl_hz)) {
        context.status = TWI_INIT_FAILURE;
        return TWI_INIT_FAILURE;
    }

    context.busy = false;
    context.status = TWI_SUCCESS;
    TWCR = (1 << TWEN) | (1 << TWIE) | (1 << TWEA);

    return TWI_SUCCESS;
}

twi_status_t twi_enqueue(twi_message_t *messages, size_t count)
{
    uint8_t sreg = SREG;
    cli();

    if ((TWCR & (1 << TWEN)) == 0) {
        SREG = sreg;
        return TWI_DISABLED;
    }

    if (context.busy) {
        SREG = sreg;
        return TWI_BUSY;
    }

    if (messages == 0 || count == 0) {
        SREG = sreg;
        return TWI_INVALID_PARAMETER;
    }

    context.messages = messages;
    context.message_count = count;
    context.message_index = 0;
    context.byte_index = 0;
    context.status = TWI_BUSY;
    context.busy = true;

    twi_start();

    SREG = sreg;
    return TWI_SUCCESS;
}

twi_status_t twi_status(void)
{
    uint8_t sreg = SREG;
    cli();
    twi_status_t status = context.status;
    SREG = sreg;

    return status;
}

bool twi_idle(void)
{
    uint8_t sreg = SREG;
    cli();
    bool idle = !context.busy;
    SREG = sreg;

    return idle;
}

ISR(TWI_vect)
{
    twi_message_t *message = &context.messages[context.message_index];

    switch (TW_STATUS) {
        case TW_START:
        case TW_REP_START:
            TWDR = message->address;
            twi_continue();
            break;

        case TW_MT_SLA_ACK:
        case TW_MT_DATA_ACK:
            if (context.byte_index < message->size) {
                TWDR = message->buffer[context.byte_index++];
                twi_continue();
            } else {
                complete_message();
            }
            break;

        case TW_MR_SLA_ACK:
            if (message->size > 1) {
                twi_continue_ack();
            } else {
                twi_continue();
            }
            break;

        case TW_MR_DATA_ACK:
            message->buffer[context.byte_index++] = TWDR;
            if ((message->size - context.byte_index) > 1) {
                twi_continue_ack();
            } else {
                twi_continue();
            }
            break;

        case TW_MR_DATA_NACK:
            if (context.byte_index < message->size) {
                message->buffer[context.byte_index++] = TWDR;
            }
            complete_message();
            break;

        case TW_MT_SLA_NACK:
        case TW_MT_DATA_NACK:
        case TW_MR_SLA_NACK:
            twi_stop(TWI_NACK_FAILURE);
            break;

        case TW_BUS_ERROR:
        default:
            twi_stop(TWI_BUS_ERROR);
            break;
    }
}
