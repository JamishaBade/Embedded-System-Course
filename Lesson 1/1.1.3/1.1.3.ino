// 4-bit Fish Counter

// LED pins for binary display
int ledPins[4] = {2, 3, 4, 5};

// Push button pins
int increment_button = 6;   // Increment button
int reset_button = 7;       // Reset button

// Built-in LED (overflow indicator)
int overflowLED = 13;

// Counter variable
int counter = 0;

// For button debounce (track last states)
int lastIncState = HIGH;
int lastResetState = HIGH;

void setup() {
  // Set LEDs as output
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(overflowLED, OUTPUT);

  // Set buttons as input with pull-up resistors
  pinMode(increment_button, INPUT_PULLUP);
  pinMode(reset_button, INPUT_PULLUP);
}

void loop() {
  // Read button states (LOW = pressed, because of INPUT_PULLUP)
  int incState = digitalRead(increment_button);
  int resetState = digitalRead(reset_button);

  // is reset button pressed?
  if (resetState == LOW && lastResetState == HIGH) {
    counter = 0;
  }

  // is increment button pressed?
  if (incState == LOW && lastIncState == HIGH) {
    counter++;
  }

  // Handle overflow (>15 for 4-bit)
  if (counter > 15) {
    // Lock into overflow state
    counter = 16;  
    // Turn OFF 4 LEDs
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    // Turn ON built-in overflow LED
    digitalWrite(overflowLED, HIGH);
  } else {
    // Display binary value on 4 LEDs
    for (int i = 0; i < 4; i++) {
      int bitVal = (counter >> i) & 1;  // extract i-th bit
      digitalWrite(ledPins[i], bitVal);
    }
    // Overflow LED OFF
    digitalWrite(overflowLED, LOW);
  }

  // Save last button states
  lastIncState = incState;
  lastResetState = resetState;

  delay(50); // debounce delay
}
