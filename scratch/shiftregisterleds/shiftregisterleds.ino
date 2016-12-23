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
    
    void writeRegister(byte value) {
      latchLow();
      shiftOut(dataPin, clockPin, MSBFIRST, value);
      latchHigh();
      registerData = value;
    }
};


// Shift register to Display mapping: XGFEDCBA
int digitValues = 10;
byte numberValues[] = { B00111111, B00000110, B01011011, B01001111, B01100110, B01101101, B01111101, B00000111, B01111111, B01101111};

// Setup the transistor pins for display multiplexing.  This should be converted to a shift register at some point.
int digits = 4;
int digitPins[] = {1, 2, 3, 4};

// Initialize the Seven Segment display shift register.
shiftRegister srSevenSegment(8, 12, 11);

// Used to store the current value of the timer.
long timerNumber = 0;
// Microsecond delay for seven segment multiplexing.
int delayAmt = 4000;
// Value to start countdown from
int countdownFrom = 60;
// Initialize value to compare current time against (resets when number loops).
unsigned long startTime = 1;
// Stores current time (in milliseconds) the arduino has been online.
unsigned long currentTime;
int score = 0;

void setup() {
  // Setup shift register pins
  srSevenSegment.setupPins();
  
  // Setup transistor pins
  for (int currentDigit = 1; currentDigit <= digits; currentDigit++) {
    pinMode(currentDigit, OUTPUT);
    digitalWrite(currentDigit, LOW);
  }
  
  randomSeed(analogRead(0));
  
};


void loop() {
  // Update the timer display.
  //updateTimer();
  updateScore();
  
};

void updateScore(){
  int thousands, hundreds, tens, ones;
  
  // Split out number digits for display.
  thousands = score / 1000;
  hundreds = score % 1000 / 100;
  tens = score % 100 / 10;
  ones = score % 10; 

  displayNumber(1, thousands);
  delayMicroseconds (delayAmt);
  displayNumber(2, hundreds);
  delayMicroseconds (delayAmt);
  displayNumber(3, tens);
  delayMicroseconds (delayAmt);
  displayNumber(4, ones);
  delayMicroseconds (delayAmt);
};

void updateTimer(){
  int thousands, hundreds, tens, ones;
  
  // Get the current time for this loop
  currentTime = millis();
  
  // Check if countdown timer has reached zero.  If so, restart.
  if ((currentTime - startTime) / 1000 > countdownFrom) {
    startTime = currentTime;
  }
  
  // Calculate number for display.
  timerNumber = countdownFrom - (currentTime - startTime) / 1000;
  
  // Split out number digits for display.
  thousands = timerNumber / 1000;
  hundreds = timerNumber % 1000 / 100;
  tens = timerNumber % 100 / 10;
  ones = timerNumber % 10;

  displayNumber(1, thousands);
  delayMicroseconds (delayAmt);
  displayNumber(2, hundreds);
  delayMicroseconds (delayAmt);
  displayNumber(3, tens);
  delayMicroseconds (delayAmt);
  displayNumber(4, ones);
  delayMicroseconds (delayAmt);
};



// Enable single digit on four-digit seven segment display.
void pickDigit(int x)
{
  for (int digitPin = 1; digitPin <= digits; digitPin++) {
    digitalWrite(digitPin, LOW);
  }
  digitalWrite(x, HIGH);
  
};

// Push given number to given digit on four-digit seven segment display.
void displayNumber(int digit, int number)
{
  pickDigit(digit);
  srSevenSegment.writeRegister(numberValues[number]);
};

boolean Randomizer(){
  if ( (random(0,9) % 2) == 0) {
    return true;
  } else {
    return false;
  }
}
