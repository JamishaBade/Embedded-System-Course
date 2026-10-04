#ifndef TWI_H
#define TWI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    TWI_SUCCESS,
    TWI_BUSY,
    TWI_DISABLED,
    TWI_INVALID_PARAMETER,
    TWI_INIT_FAILURE,
    TWI_NACK_FAILURE,
    TWI_BUS_ERROR
} twi_status_t;

typedef struct {
    uint8_t address;
    uint8_t *buffer;
    size_t size;
} twi_message_t;

twi_status_t twi_init(uint32_t scl_hz);
twi_status_t twi_enqueue(twi_message_t *messages, size_t count);
twi_status_t twi_status(void);
bool twi_idle(void);

#define TWI_WRITE_ADDRESS(address) ((uint8_t)((address) << 1))
#define TWI_READ_ADDRESS(address)  ((uint8_t)(((address) << 1) | 1))

#endif
