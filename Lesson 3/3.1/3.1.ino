// Traffic light controller with a pedestrian request button.
//
// Pins:
//   9  - green LED
//   10 - yellow LED
//   11 - red LED
//   2  - pedestrian request button wired to ground

const uint8_t GREEN_PIN = 9;
const uint8_t YELLOW_PIN = 10;
const uint8_t RED_PIN = 11;
const uint8_t BUTTON_PIN = 2;

enum TrafficState {
  STATE_GREEN,
  STATE_YELLOW,
  STATE_RED,
  STATE_WALK
};

struct StateTiming {
  TrafficState state;
  uint32_t durationMs;
};

const StateTiming schedule[] = {
  { STATE_GREEN, 5000 },
  { STATE_YELLOW, 1500 },
  { STATE_RED, 4000 },
  { STATE_WALK, 3000 }
};

TrafficState currentState = STATE_GREEN;
uint32_t lastTransition = 0;
bool walkRequested = false;
bool lastButtonReading = HIGH;
uint32_t lastDebounceTime = 0;
const uint32_t debounceDelayMs = 50;

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastTransition = millis();
}

void loop() {
  readWalkButton();
  updateStateMachine();
  writeLights();
}

void readWalkButton() {
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelayMs && reading == LOW) {
    walkRequested = true;
  }

  lastButtonReading = reading;
}

void updateStateMachine() {
  uint32_t elapsed = millis() - lastTransition;
  uint32_t stateDuration = durationFor(currentState);

  if (elapsed < stateDuration) {
    return;
  }

  if (currentState == STATE_RED && walkRequested) {
    currentState = STATE_WALK;
    walkRequested = false;
  } else if (currentState == STATE_WALK) {
    currentState = STATE_GREEN;
  } else {
    currentState = nextTrafficState(currentState);
  }

  lastTransition = millis();
}

uint32_t durationFor(TrafficState state) {
  for (uint8_t i = 0; i < sizeof(schedule) / sizeof(schedule[0]); i++) {
    if (schedule[i].state == state) {
      return schedule[i].durationMs;
    }
  }
  return 1000;
}

TrafficState nextTrafficState(TrafficState state) {
  switch (state) {
    case STATE_GREEN:
      return STATE_YELLOW;
    case STATE_YELLOW:
      return STATE_RED;
    case STATE_RED:
    case STATE_WALK:
    default:
      return STATE_GREEN;
  }
}

void writeLights() {
  digitalWrite(GREEN_PIN, currentState == STATE_GREEN);
  digitalWrite(YELLOW_PIN, currentState == STATE_YELLOW);
  digitalWrite(RED_PIN, currentState == STATE_RED || currentState == STATE_WALK);
}
