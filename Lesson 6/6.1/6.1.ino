// Non-blocking blink example.
// Two LEDs toggle at independent rates using millis() instead of delay().

const uint8_t LED_FAST = 2;
const uint8_t LED_SLOW = 3;

const uint32_t FAST_INTERVAL_MS = 389;
const uint32_t SLOW_INTERVAL_MS = 991;

uint32_t previousFast = 0;
uint32_t previousSlow = 0;

void setup() {
  pinMode(LED_FAST, OUTPUT);
  pinMode(LED_SLOW, OUTPUT);
  previousFast = millis();
  previousSlow = millis();
}

void loop() {
  toggleWhenDue(LED_FAST, FAST_INTERVAL_MS, previousFast);
  toggleWhenDue(LED_SLOW, SLOW_INTERVAL_MS, previousSlow);
}

void toggleWhenDue(uint8_t pin, uint32_t intervalMs, uint32_t &previousTime) {
  uint32_t now = millis();

  if (now - previousTime >= intervalMs) {
    digitalWrite(pin, !digitalRead(pin));
    previousTime = now;
  }
}
