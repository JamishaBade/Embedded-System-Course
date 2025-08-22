// 4 bit binary counting problem

// LED pins for binary display
int ledPins[4] = {2, 3, 4, 5};

// this is push buttons
int increment_button = 6;   // Increment button
int reset_button = 7;       // Reset button

// built in led is pin 13
int overflowLED = 13;
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

  // if counter is greater than 15, it is overflowing 
  if (counter > 15) {
    //counter++;
    counter = 16;  
    // turn off leds
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    // turn on the inbuilt led to indicate overflow
    digitalWrite(overflowLED, HIGH);
  } else {
   
    for (int i = 0; i < 4; i++) {
      int bitVal = (counter >> i) & 1;  //takes ith place and turns it ON or OFF accordingly
      digitalWrite(ledPins[i], bitVal);
    }
    // Overflow LED OFF
    digitalWrite(overflowLED, LOW);
  }


  lastIncState = incState;
  lastResetState = resetState;

  delay(50); 
}
