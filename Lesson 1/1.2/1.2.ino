const int ledPin = LED_BUILTIN;
const int buttonPin = 2;

int brightnessLevel = 0;         // 0 = off, 1-10 = brightness
const int maxLevel = 10;

bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Using internal pull-up
}

void loop() {
  // --- Button handling with debounce ---
  bool reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) { // Button pressed (active LOW)
      brightnessLevel++;
      if (brightnessLevel > maxLevel) brightnessLevel = 0;
    }
  }
  lastButtonState = reading;

  // The LED isn’t actually dimming; it just spends less time turned on in each fast cycle, so your eyes perceive it as dimmer.
  int onTime = brightnessLevel * 100;  // in microseconds (10% per level)
  int offTime = 1000 - onTime;         // total period = 1000 µs → 1 kHz

  digitalWrite(ledPin, HIGH);
  delayMicroseconds(onTime);
  digitalWrite(ledPin, LOW);
  delayMicroseconds(offTime);
}
