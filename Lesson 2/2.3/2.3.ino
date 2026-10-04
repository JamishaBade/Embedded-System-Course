// RGB LED Serial Controller
int ledR = 9;
int ledG = 10;
int ledB = 11;

bool isHexDigit(char c) {
  return (c >= '0' && c <= '9') ||
         (c >= 'A' && c <= 'F') ||
         (c >= 'a' && c <= 'f');
}

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  Serial.println(" Enter a 6-digit RGB hex like FF00FF !");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // read input until Enter
    input.trim(); // remove any whitespaces

    // Check if input is the right length
    if (input.length() != 6) {
      Serial.println("ERROR: Must be 6 characters like FF00FF");
      return;
    }

    for (int i = 0; i < 6; i++) {
      if (!isHexDigit(input[i])) {
        Serial.println("ERROR: Invalid hex code!");
        return;
      }
    }

    // Convert the hex string to a number
    long color = strtol(input.c_str(), NULL, 16);

    // Split into red, green, blue
    //this is the main concept 
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;

    // Set the LED colors
    analogWrite(ledR, r);
    analogWrite(ledG, g);
    analogWrite(ledB, b);

    Serial.println(" LED updated ");
  }
}
