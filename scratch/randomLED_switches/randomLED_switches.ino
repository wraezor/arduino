int inLEDPins[] = {1, 2};
int outLEDPins[] = {3, 4};
int switchPins[] = {5, 6};
int ledsOn[] = {false, false};
int switchesOn[] = {false, false};
int totalItems = 2;

void setup()
{
  for (int currentLED = 0; currentLED < totalItems; currentLED++) {
    pinMode(inLEDPins[currentLED], OUTPUT);
    pinMode(outLEDPins[currentLED], OUTPUT);
    pinMode(switchPins[currentLED], INPUT);
  }

  randomSeed(analogRead(0));
  
  Serial.begin(9600);
}

void loop()
{
  readSwitches();
  if ( ledsMatch() ) {
    Serial.print("Match!");
    lightLEDs();
  }
  Serial.print(digitalRead(switchPins[0]));
  Serial.println(digitalRead(switchPins[1]));
  Serial.print(ledsOn);
  Serial.println(switchesOn);

  delay(1000);  
}

void readSwitches() {
  boolean switchState;
  for (int currentSwitch = 0; currentSwitch < totalItems; currentSwitch++) {
    switchState = digitalRead(switchPins[currentSwitch]);
    digitalWrite(outLEDPins[currentSwitch], switchState);
    switchesOn[currentSwitch] = switchState;
  }
}

boolean ledsMatch() {
  for (int currentPair = 0; currentPair < totalItems; currentPair++) {
    if ( switchesOn[currentPair] != ledsOn[currentPair] ) {
      return false;
    }
  }
  return true;
}

void lightLEDs(){
  for (int currentLED = 0; currentLED < totalItems; currentLED++) {
    digitalWrite(inLEDPins[currentLED], LOW);
    if (OnOffRandomizer() == true) {
      digitalWrite(inLEDPins[currentLED], HIGH);
      ledsOn[currentLED] = true;
    }
    else {
      digitalWrite(inLEDPins[currentLED], LOW);
      ledsOn[currentLED] = false;
    }
  }
}


boolean OnOffRandomizer(){
  if ( (random(0,9) % 2) == 0) {
    return true;
  } else {
    return false;
  }
}
