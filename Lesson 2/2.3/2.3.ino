// RGB LED Serial Controller
int ledR = 9;
int ledG = 10;
int ledB = 11;

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

    // Convert the hex string to a number
    long color = strtol(input.c_str(), NULL, 16);
    if (color == 0 && !input.equals("000000")) {
      Serial.println("ERROR: Invalid hex code!");
      return;
    }

    // Split into red, green, blue
    //this is the main concept 
    int b = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int r = color & 0xFF;

    // Set the LED colors
    analogWrite(ledR, r);
    analogWrite(ledG, g);
    analogWrite(ledB, b);

    Serial.println(" LED updated ");
  }
}
