const int ledPin = 12;
int delay_time=50;
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  blinkDot();
}


void blinkDot() {

while(delay_time<500){
  // Serial.print(delay_time);
  // Serial.print("\n");

  digitalWrite(ledPin, HIGH);
  delay(delay_time);
  digitalWrite(ledPin, LOW);
  delay(delay_time);
  delay_time+=50;

}
while(delay_time>0){
  // Serial.print(delay_time);
  // Serial.print("\n");

 digitalWrite(ledPin, HIGH);
  delay(delay_time);
  digitalWrite(ledPin, LOW);
  delay(delay_time);
  delay_time-=50;


}
}


