class shiftRegister {
  private:
    int latchPin; // Pin 12 (ST_CP of 74HC595)
    int clockPin; // Pin 11 (SH_CP of 74HC595)
    int dataPin;  // Pin 14 (DS of 74HC595)
    
    void latchLow() {
      digitalWrite(latchPin, LOW); 
    }
    
    void latchHigh() {
      digitalWrite(latchPin, HIGH); 
    }
    
  public:
    unsigned int registerData; // Data currently in register.
    int pinCount;
    
    unsigned int bitsOn  = 0b1111111111111111;
    unsigned int bitsOff = 0b0000000000000000;
    
    shiftRegister(int latch, int clock, int data, int pins) {
      latchPin = latch;
      clockPin = clock;
      dataPin = data;
      pinCount = pins;
    }

    void setupPins() {
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
      
      registerData = bitsOff;
      writeRegister(registerData);
    }
    
    unsigned int msbValue() {
      unsigned int value = 0b1;
      value = value << (pinCount - 1);
      return value;
    }

    unsigned int lsbValue() {
      unsigned int value = 0b1;
      return value;
    }
    
    void writeRegister(unsigned int value) {
      int currentPinBlock = pinCount - 8;
      latchLow();
      
      //shift out all blocks except last
      while (currentPinBlock > 0) {
        shiftOut(dataPin, clockPin, MSBFIRST, value >> currentPinBlock);  
        currentPinBlock -= 8;
      } 
      
      // Shift out last block
      shiftOut(dataPin, clockPin, MSBFIRST, value);
      latchHigh();
      registerData = value;
      Serial.println(registerData, BIN);
    }

    void setLEDsOn() {
      registerData = bitsOn;
      writeRegister(registerData);
    }

    void setLEDsOff() {
      registerData = bitsOff;
      writeRegister(registerData);
    }

    void setMSBLEDOn() {
      registerData = bitsOff | msbValue();
      writeRegister(registerData);
    }

    void setLSBLEDOn() {
      registerData = bitsOff | lsbValue();
      writeRegister(registerData);
    }

    void shiftDown(bool nextBit = 0) {
      if (nextBit) {
        registerData = registerData >> 1;
        registerData = registerData | msbValue();
      } else {
        registerData = registerData >> 1;
      }
      writeRegister(registerData);
    }

    void shiftUp(bool nextBit = 0) {
      if (nextBit) {
        registerData = registerData << 1;
        registerData = registerData | lsbValue();
      } else {
        registerData = registerData << 1;
      }
      writeRegister(registerData);
    }

    int getLEDState(int value) {
      bool bitValue;
      value -= 1;  //change from 1-8 to 0-7
      bitValue = bitRead(registerData, value);
      return bitValue;
    }
};


class sevenSegmentDisplay {
  private:
    int latchPin; // Pin 12 (ST_CP of 74HC595)
    int clockPin; // Pin 11 (SH_CP of 74HC595)
    int dataPin;  // Pin 14 (DS of 74HC595)
    
    
  public:
    int onesValue;
    int tensValue;
    int hundredsValue;
    int thousandsValue;
    
    sevenSegmentDisplay(shiftRegister& srOutput) {
      srOutput.setLEDsOn();
    }
}





int ledPins = 16;
shiftRegister srOutput(6, 7, 5, 16);
sevenSegmentDisplay ssdOutput(srOutput);
int speed = 500;


void setup() {
  srLEDOutput.setupPins();
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

void loop() {

  randomLights();
  fillupLights();
  sequentialLights(); 
 
}

void randomLights() {
  unsigned int ledRandState = 0;
  
  for (int x=0 ; x < 100 ; x++) {
    ledRandState = random(1,32768);
    srLEDOutput.writeRegister(ledRandState);
    delay(speed);
  }
}

void sequentialLights() {
  for (int y=0 ; y < 100 ; y++) {  
    srLEDOutput.setLSBLEDOn();
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftUp();
      delay(speed/10);
    }
   
    srLEDOutput.setMSBLEDOn();
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftDown();
      delay(speed/10);
    }
  }
} 

void fillupLights() {
  for (int y=0 ; y < 100 ; y++) {  
    srLEDOutput.setLSBLEDOn();
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftUp(1);
      delay(speed/10);
    }
   
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftUp();
      delay(speed/10);
    }
    
    srLEDOutput.setMSBLEDOn();
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftDown(1);
      delay(speed/10);
    }
    
    for (int x=0 ; x < ledPins ; x++) {
      srLEDOutput.shiftDown();
      delay(speed/10);
    }
  }
}
