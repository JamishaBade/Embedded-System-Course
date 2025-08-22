// RGB LED with 4 legs (common cathode)

// Potentiometers
int potR = A0;
int potG = A1;
int potB = A2;

// RGB LED pins (PWM)
int ledR = 9;
int ledG = 10;
int ledB = 11;

// Optional dim button
int dimButton = 2;
bool dimPressed = false;
int lastButtonState = HIGH;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(dimButton, INPUT_PULLUP);
}

void loop() {
  // Read potentiometers
  int rVal = map(analogRead(potR), 0, 1023, 0, 255);
  int gVal = map(analogRead(potG), 0, 1023, 0, 255);
  int bVal = map(analogRead(potB), 0, 1023, 0, 255);

  // Read dim button (toggle)
  int buttonState = digitalRead(dimButton);
  if (buttonState == LOW && lastButtonState == HIGH) {
    dimPressed = !dimPressed;
  }
  lastButtonState = buttonState;

  // Apply dim
  if (dimPressed) {
    rVal /= 2;
    gVal /= 2;
    bVal /= 2;
  }

  // Set LED color
  analogWrite(ledR, rVal);
  analogWrite(ledG, gVal);
  analogWrite(ledB, bVal);

  delay(20);
}
