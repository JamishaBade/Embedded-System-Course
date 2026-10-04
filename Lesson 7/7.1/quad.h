#pragma once

#include <Arduino.h>

void encoder_setup(uint8_t clkPin = 2, uint8_t dtPin = 3);
long encoder_steps(void);
void encoder_reset(void);
