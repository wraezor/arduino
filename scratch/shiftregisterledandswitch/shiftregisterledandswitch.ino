
//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

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
    byte registerData; // Byte currently in register.
    
    shiftRegister(int latch, int clock, int data) {
      latchPin = latch;
      clockPin = clock;
      dataPin = data;
      registerData = 00000000;
      
      writeRegister(registerData);
    }

    void setupPins() {
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }
    
    void writeRegister(int value) {
      latchLow();
      shiftOut(dataPin, clockPin, MSBFIRST, value);
      latchHigh();
      registerData = value;
    }
};


shiftRegister srSwitchRead(8, 12, 11);
shiftRegister srLEDOutput(7, 6, 5);
int switchReadPin = 4;

void setup() {
  srSwitchRead.setupPins();
  srLEDOutput.setupPins();


  pinMode(4, INPUT);
  Serial.begin(9600);
}

void loop() {

  byte registerLEDByte = 00000000;
  
  // Loop through each register on the chip
  for (byte bit = 10000000; bit > 0; bit >>= 1) {
    // Record the current value to display on the LEDs.
    registerLEDByte <<= 1;
    registerLEDByte |= checkRegisterPin(bit);
  }

  srLEDOutput.writeRegister(registerLEDByte);
  Serial.print("LED Register: ");
  Serial.println(srLEDOutput.registerData, BIN);
  delay (1000);
}

boolean checkRegisterPin(int registerPin) {
  srSwitchRead.writeRegister(registerPin);
  
  //Do I need any delay?
  return digitalRead(switchReadPin);
}
