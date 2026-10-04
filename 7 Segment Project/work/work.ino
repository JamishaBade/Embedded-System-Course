// Four-digit 7-segment display marquee.
//
// Segment pins are active HIGH.
// Digit pins are active LOW.

const char MESSAGE[] = " EMBEDDED SYSTEMS ";
const uint8_t WINDOW_SIZE = 4;
const uint16_t SCROLL_DELAY_MS = 350;
const uint16_t DIGIT_REFRESH_US = 1800;

enum Segment {
  SEG_A,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  SEG_G,
  SEG_DP,
  SEG_COUNT
};

const uint8_t SEGMENT_PINS[SEG_COUNT] = {
  8, 4, 5, 7, 9, 6, 2, 3
};

const uint8_t DIGIT_PINS[WINDOW_SIZE] = {
  10, 11, 12, 13
};

uint8_t windowStart = 0;
uint32_t lastScroll = 0;

void setup() {
  for (uint8_t i = 0; i < SEG_COUNT; i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }

  for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
    pinMode(DIGIT_PINS[i], OUTPUT);
    digitalWrite(DIGIT_PINS[i], HIGH);
  }
}

void loop() {
  if (millis() - lastScroll >= SCROLL_DELAY_MS) {
    windowStart = (windowStart + 1) % messageLength();
    lastScroll = millis();
  }

  refreshDisplay();
}

void refreshDisplay() {
  for (uint8_t digit = 0; digit < WINDOW_SIZE; digit++) {
    blankDigits();

    char c = MESSAGE[(windowStart + digit) % messageLength()];
    writeSegments(glyph(c));

    digitalWrite(DIGIT_PINS[digit], LOW);
    delayMicroseconds(DIGIT_REFRESH_US);
    digitalWrite(DIGIT_PINS[digit], HIGH);
  }
}

void blankDigits() {
  for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
    digitalWrite(DIGIT_PINS[i], HIGH);
  }
}

void writeSegments(uint8_t mask) {
  for (uint8_t segment = 0; segment < SEG_COUNT; segment++) {
    digitalWrite(SEGMENT_PINS[segment], (mask & (1 << segment)) != 0);
  }
}

uint8_t messageLength() {
  return sizeof(MESSAGE) - 1;
}

uint8_t glyph(char c) {
  switch (c) {
    case '0': return 0b00111111;
    case '1': return 0b00000110;
    case '2': return 0b01011011;
    case '3': return 0b01001111;
    case '4': return 0b01100110;
    case '5': return 0b01101101;
    case '6': return 0b01111101;
    case '7': return 0b00000111;
    case '8': return 0b01111111;
    case '9': return 0b01101111;
    case 'A': return 0b01110111;
    case 'B': return 0b01111100;
    case 'C': return 0b00111001;
    case 'D': return 0b01011110;
    case 'E': return 0b01111001;
    case 'F': return 0b01110001;
    case 'H': return 0b01110110;
    case 'I': return 0b00000110;
    case 'L': return 0b00111000;
    case 'M': return 0b00110111;
    case 'N': return 0b01010100;
    case 'O': return 0b00111111;
    case 'P': return 0b01110011;
    case 'R': return 0b01010000;
    case 'S': return 0b01101101;
    case 'T': return 0b01111000;
    case 'Y': return 0b01101110;
    case ' ': return 0b00000000;
    default: return 0b00000000;
  }
}
