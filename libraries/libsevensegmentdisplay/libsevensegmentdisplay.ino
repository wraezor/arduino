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
      //Serial.println(registerData, BIN);
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
    shiftRegister& _srOutput;
    byte           _numberValue[10] = { 0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111 };
    byte           _digitValue[4]   = { 0b1, 0b10, 0b100, 0b1000 };
    byte           _splitValue[4]   = { 0, 0, 0, 0 };
    unsigned long  _previousUpdateMillis = 0;
    int            _delayMillis = 4;
    int            _activeDigit = 0;
    
    void splitNumber(int value) {
      // Split out number digits for display.
      _splitValue[3] = value / 1000;
      _splitValue[2] = value % 1000 / 100;
      _splitValue[1] = value % 100 / 10;
      _splitValue[0] = value % 10;
    }
    
  public:
    
    sevenSegmentDisplay(shiftRegister& srOutput)
    : _srOutput(srOutput)
    {
      _srOutput.setLEDsOff();
    }
    
    void setupPins(){
      _srOutput.setupPins();
    }
    
    void setNumber(int value, int digit){
      //Serial.print("Digit:" );
      //Serial.print(digit);
      //Serial.print(" / Value : ");
      //Serial.println(value);
      
      unsigned int combinedValue = 0b0;
      splitNumber(value);
      
      combinedValue = combinedValue << 4;
      combinedValue = _digitValue[digit];
      combinedValue = combinedValue << 8;
      combinedValue = combinedValue | _numberValue[_splitValue[digit]];
      _srOutput.writeRegister(combinedValue);
    }
    
    void blank(){
      _srOutput.setLEDsOff();
    }
    
    void updateDisplay(int value){
      unsigned long currentUpdateMillis = millis();
      
      
      //Serial.println(currentUpdateMillis);
      //Serial.println(_previousUpdateMillis);
      
      if (currentUpdateMillis - _previousUpdateMillis > _delayMillis) {
        _previousUpdateMillis = currentUpdateMillis;
        setNumber(value, _activeDigit);
        _activeDigit++;
      }
      if (_activeDigit > 3) {
        _activeDigit = 0;
      }
    }
    
};





int ledPins = 16;
shiftRegister srOutput(6, 7, 5, 16);
sevenSegmentDisplay ssdOutput(srOutput);
int speed = 300;
int seconds;

void setup() {
  ssdOutput.setupPins();
  randomSeed(analogRead(0));
  Serial.begin(9600);

}

void loop() {
  //for ( int x = 0; x <= 9; x ++ ) {
  //  ssdOutput.updateDisplay(x);
  //  delay (speed);
  //}
  
  //ssdOutput.setNumber(8);
  //delay (speed*100);
  

  seconds =  millis()/1000;
  
  ssdOutput.updateDisplay (seconds);
}

