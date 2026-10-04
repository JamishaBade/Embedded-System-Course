const int potPin = A0;           // Potentiometer connected to A0
const int ledPins[4] = {2, 3, 4, 5}; // LEDs

int thresholds[4] = {200, 400, 600, 800}; // Volume thresholds
int hysteresis = 20;                        // Hysteresis buffer (state depends on prev state)
//Hysteresis is used to avoid flickering of the LEDs when the potentiometer is near a threshold.
int currentLevel = 0;                        // Currently lit LEDs

void setup() {
  for(int i=0; i<4; i++){
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  int potValue = analogRead(potPin);
  
  // Determine level with hysteresis
  int newLevel = currentLevel;
  // helps to make the transition smoother
  if(currentLevel < 4 && potValue > thresholds[currentLevel] + hysteresis){
    newLevel++;
  } 
  else if(currentLevel > 0 && potValue < thresholds[currentLevel-1] - hysteresis){
    newLevel--;
  }
  
  currentLevel = newLevel;

  // Update LEDs
  for(int i=0; i<4; i++){
    if(i < currentLevel) digitalWrite(ledPins[i], HIGH);
    else digitalWrite(ledPins[i], LOW);
  }
  
  delay(20);
}
