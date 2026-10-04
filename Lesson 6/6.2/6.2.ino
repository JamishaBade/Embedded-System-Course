// Simple vending machine finite state machine.
//
// Buttons are wired from pin to ground and use INPUT_PULLUP.
//   2 - add quarter
//   3 - change product
//   4 - vend
//   5 - return credit

const uint8_t COIN_BUTTON = 2;
const uint8_t SELECT_BUTTON = 3;
const uint8_t VEND_BUTTON = 4;
const uint8_t RETURN_BUTTON = 5;

const uint8_t READY_LED = 10;
const uint8_t DISPENSE_LED = 11;
const uint8_t ERROR_LED = 12;

const uint32_t DEBOUNCE_MS = 40;

enum MachineState {
  STATE_AWAIT_PAYMENT,
  STATE_READY_TO_VEND,
  STATE_DISPENSE,
  STATE_RETURN_CREDIT,
  STATE_ERROR
};

struct Product {
  const char *name;
  uint8_t costInQuarters;
  uint8_t stock;
};

Product products[] = {
  { "CHIPS", 4, 3 },
  { "CANDY", 3, 4 },
  { "DRINK", 5, 2 }
};

MachineState state = STATE_AWAIT_PAYMENT;
uint8_t selectedProduct = 0;
uint8_t quarterCount = 0;
uint32_t stateStartedAt = 0;

uint8_t buttonPins[] = { COIN_BUTTON, SELECT_BUTTON, VEND_BUTTON, RETURN_BUTTON };
bool stableState[] = { HIGH, HIGH, HIGH, HIGH };
bool lastReading[] = { HIGH, HIGH, HIGH, HIGH };
uint32_t lastChangedAt[] = { 0, 0, 0, 0 };

void setup() {
  Serial.begin(9600);

  for (uint8_t i = 0; i < sizeof(buttonPins); i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(READY_LED, OUTPUT);
  pinMode(DISPENSE_LED, OUTPUT);
  pinMode(ERROR_LED, OUTPUT);

  printStatus();
}

void loop() {
  if (buttonPressed(COIN_BUTTON)) {
    quarterCount++;
    printStatus();
  }

  if (buttonPressed(SELECT_BUTTON)) {
    selectedProduct = (selectedProduct + 1) % productCount();
    printStatus();
  }

  if (buttonPressed(RETURN_BUTTON)) {
    state = STATE_RETURN_CREDIT;
    stateStartedAt = millis();
  }

  runStateMachine();
  updateIndicators();
}

void runStateMachine() {
  Product &product = products[selectedProduct];

  switch (state) {
    case STATE_AWAIT_PAYMENT:
      if (quarterCount >= product.costInQuarters) {
        state = STATE_READY_TO_VEND;
        printStatus();
      }
      break;

    case STATE_READY_TO_VEND:
      if (quarterCount < product.costInQuarters) {
        state = STATE_AWAIT_PAYMENT;
      } else if (buttonPressed(VEND_BUTTON)) {
        if (product.stock == 0) {
          state = STATE_ERROR;
        } else {
          state = STATE_DISPENSE;
          stateStartedAt = millis();
          product.stock--;
          quarterCount -= product.costInQuarters;
        }
        printStatus();
      }
      break;

    case STATE_DISPENSE:
      if (millis() - stateStartedAt >= 1200) {
        state = quarterCount > 0 ? STATE_RETURN_CREDIT : STATE_AWAIT_PAYMENT;
        printStatus();
      }
      break;

    case STATE_RETURN_CREDIT:
      quarterCount = 0;
      if (millis() - stateStartedAt >= 600) {
        state = STATE_AWAIT_PAYMENT;
        printStatus();
      }
      break;

    case STATE_ERROR:
      if (buttonPressed(SELECT_BUTTON) || buttonPressed(RETURN_BUTTON)) {
        state = STATE_AWAIT_PAYMENT;
        printStatus();
      }
      break;
  }
}

bool buttonPressed(uint8_t pin) {
  uint8_t index = buttonIndex(pin);
  bool reading = digitalRead(pin);

  if (reading != lastReading[index]) {
    lastChangedAt[index] = millis();
    lastReading[index] = reading;
  }

  if ((millis() - lastChangedAt[index]) > DEBOUNCE_MS && reading != stableState[index]) {
    stableState[index] = reading;
    return stableState[index] == LOW;
  }

  return false;
}

uint8_t buttonIndex(uint8_t pin) {
  for (uint8_t i = 0; i < sizeof(buttonPins); i++) {
    if (buttonPins[i] == pin) {
      return i;
    }
  }
  return 0;
}

uint8_t productCount() {
  return sizeof(products) / sizeof(products[0]);
}

void updateIndicators() {
  digitalWrite(READY_LED, state == STATE_READY_TO_VEND);
  digitalWrite(DISPENSE_LED, state == STATE_DISPENSE || state == STATE_RETURN_CREDIT);
  digitalWrite(ERROR_LED, state == STATE_ERROR);
}

void printStatus() {
  Product &product = products[selectedProduct];

  Serial.print("Product: ");
  Serial.print(product.name);
  Serial.print(" | cost: ");
  Serial.print(product.costInQuarters);
  Serial.print(" quarters | stock: ");
  Serial.print(product.stock);
  Serial.print(" | credit: ");
  Serial.println(quarterCount);
}
