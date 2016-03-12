// Arduino Switch Pins / BB / Resistor to 5V / Switch / Gnd
// Postive side of Switch pins are pulled up using 10K resistors

// Pins 2-3 are the lights you have to match.
// Pins 4-5 are the lights you can manipulate with the switch.


int inLEDPins[] = {2, 3};
int outLEDPins[] = {4, 5};
int switchPins[] = {6, 7};
int ledsOn[] = {false, false};
int switchesOn[] = {false, false};
int totalItems = 2;
int totalMatches = 0;

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
    totalMatches++;   
    Serial.print("Match: ");
    Serial.println(totalMatches); 
    lightLEDs();
  }
//  Serial.print("In: ");
//  Serial.print(ledsOn[0]);
//  Serial.println(ledsOn[1]);
//  Serial.print("Out: ");
//  Serial.print(switchesOn[0]);
//  Serial.println(switchesOn[1]);

  delay(100);  
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
