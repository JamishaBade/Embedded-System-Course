#include "quad.h"

static volatile long encoderTicks = 0;
static volatile uint8_t previousState = 0;
static uint8_t encoderClkPin = 2;
static uint8_t encoderDtPin = 3;

static const int8_t transitionTable[16] = {
  0, -1, 1, 0,
  1, 0, 0, -1,
  -1, 0, 0, 1,
  0, 1, -1, 0
};

static uint8_t readEncoderState(void) {
  return (digitalRead(encoderClkPin) << 1) | digitalRead(encoderDtPin);
}

static void encoder_isr(void) {
  uint8_t currentState = readEncoderState();
  uint8_t transition = (previousState << 2) | currentState;
  encoderTicks += transitionTable[transition];
  previousState = currentState;
}

void encoder_setup(uint8_t clkPin, uint8_t dtPin) {
  encoderClkPin = clkPin;
  encoderDtPin = dtPin;

  pinMode(encoderClkPin, INPUT_PULLUP);
  pinMode(encoderDtPin, INPUT_PULLUP);

  previousState = readEncoderState();

  attachInterrupt(digitalPinToInterrupt(encoderClkPin), encoder_isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderDtPin), encoder_isr, CHANGE);
}

long encoder_steps(void) {
  noInterrupts();
  long ticks = encoderTicks;
  interrupts();

  return ticks / 4;
}

void encoder_reset(void) {
  noInterrupts();
  encoderTicks = 0;
  previousState = readEncoderState();
  interrupts();
}
