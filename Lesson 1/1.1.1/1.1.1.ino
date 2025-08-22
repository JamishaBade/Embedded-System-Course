const int LEDPIN = 12;

void setup() {
  pinMode(LEDPIN, OUTPUT);
}

void loop() {

  blinkDot();
  blinkDot();
  blinkDot();
  delay(500);


  blinkDash();
  blinkDash();
  blinkDash();
  delay(500);


  blinkDot();
  blinkDot();
  blinkDot();

  delay(2000);
}

void blinkDot() {
  digitalWrite(LEDPIN, HIGH);
  delay(100);
  digitalWrite(LEDPIN, LOW);
  delay(100);
}

void blinkDash() {
  digitalWrite(LEDPIN, HIGH);
  delay(1000);
  digitalWrite(LEDPIN, LOW);
  delay(1000);
}
