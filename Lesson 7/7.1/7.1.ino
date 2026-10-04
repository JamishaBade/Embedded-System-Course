#include "quad.h"

const uint8_t CLK_PIN = 2;
const uint8_t DT_PIN = 3;
const uint8_t LED_PIN = LED_BUILTIN;

long lastPosition = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  encoder_setup(CLK_PIN, DT_PIN);
  Serial.println("Quadrature encoder ready. Send r to reset.");
}

void loop() {
  long position = encoder_steps();

  if (position != lastPosition) {
    Serial.print("position=");
    Serial.println(position);
    digitalWrite(LED_PIN, position & 1);
    lastPosition = position;
  }

  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'r' || command == 'R') {
      encoder_reset();
      lastPosition = 0;
      Serial.println("position reset");
    }
  }
}
