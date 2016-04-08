
//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 8; //Pin 12 on 595
//Pin connected to SH_CP of 74HC595
int clockPin = 12; // Pin 11 on 595
////Pin connected to DS of 74HC595
int dataPin = 11;  // Pin 14 on 595
int potPin = 2;

// Pin, Current Value
int potData[5][2] = {
  { 1, 0 },
  { 2, 0 },
  { 3, 0 },
  { 4, 0 },
  { 5, 0 }
};

// Match value, State
int ledStates[5][2] = {
  { 0, 0 },
  { 0, 0 },
  { 0, 0 },
  { 0, 0 },
  { 0, 0 }
};


void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  //pot1matchval = random(0,1024);
  
}

void loop() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  //for (int numberToDisplay = 0; numberToDisplay < 32; numberToDisplay++) {

    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
  // digitalWrite(latchPin, LOW);
    // shift out the bits:
  // shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay >> 8);  
  // shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
    //take the latch pin high so the LEDs will light up:
  // digitalWrite(latchPin, HIGH);
    // pause before next value:
  // Serial.println(numberToDisplay);
 //  delay(100);
   
  //}
  
//  delay(10000);
  int LEDValue;
  setSourceLEDs();
  //Serial.print(ledStates[0][1]);
  //Serial.print(ledStates[1][1]);
  //Serial.print(ledStates[2][1]);
  //Serial.print(ledStates[3][1]);
  //Serial.println(ledStates[4][1]);

//  for (int LED = 0; LED < 5; LED++) {
//    Serial.print(ledStates[LED][0]);
//    Serial.print(" ");
//  }
//  Serial.println(" ");

  getPOTValues();

  for (int Pot = 0; Pot < 5; Pot++) {
    Serial.print(potData[Pot][1]);
    Serial.print(" ");
  }
  Serial.println(" ");


//  Serial.println(potValues[1]);
  
  delay(50);
  
}

void getPOTValues() {
  for (int Pot = 0; Pot < 5; Pot++) {
    potData[Pot][1] = analogRead(potData[Pot][0]);
  }
}

void setSourceLEDs() {
  int lightsInt;
  lightsInt = random(0,32);

  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, 0);
  shiftOut(dataPin, clockPin, MSBFIRST, lightsInt);
  digitalWrite(latchPin, HIGH);

  // Loop through each light.
  for (int LED = 0; LED < 5; LED++) {
    // Track the status of each LED
    int LEDState = lightsInt >> LED;
    if ( ( LEDState % 2) == 0) {
      ledStates[LED][1] = false;
    } else {
      ledStates[LED][1] = true;
    }
    // Assign the random value the Pots have to match.
    ledStates[LED][0] = random(0, 1024);
  }
}
