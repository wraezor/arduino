// Display pins are numbered counter-clockwise bottom left to top left

int dgt1Pin = 1; // Pin 12 (w/330 resistor)
int dgt2Pin = 2; // Pin 9 (w/330 resistor)
int dgt3Pin = 3; // Pin 8 (w/330 resistor)
int dgt4Pin = 4; // Pin 6 (w/330 resistor)

int segA = 5; // Pin 11
int segB = 6; // Pin 7
int segC = 7; // Pin 4
int segD = 8; // Pin 2
int segE = 9; // Pin 1
int segF = 10; // Pin 10
int segG = 11; // Pin 5

long number = 0;
int digit = 0;
int delayAmt = 3;
int countdownFrom = 1000;
unsigned long startTime = 1;
unsigned long currentTime;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(dgt1Pin, OUTPUT);
  pinMode(dgt2Pin, OUTPUT);
  pinMode(dgt3Pin, OUTPUT);
  pinMode(dgt4Pin, OUTPUT);
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  Serial.begin(9600); 
  
  // Set starting number.
  startTime = 1;
}

// the loop routine runs over and over again forever:
void loop() {
  count();
}



void count(){
  int thousands, hundreds, tens, ones;
  
  // Get the current time for this loop
  currentTime = millis();
  
  // Check if countdown timer has reached zero.  If so, restart.
  if ((currentTime - startTime) / 1000 > countdownFrom){
    startTime = currentTime;
  }
  
  // Calculate number for display.
  number = countdownFrom - (currentTime - startTime) / 1000;
  
  // Split out number digits for display.
  thousands = number / 1000;
  hundreds = number % 1000 / 100;
  tens = number % 100 / 10;
  ones = number % 10;

//  Serial.print("currentTime:");
//  Serial.println(currentTime);
//  Serial.print("startTime:");
//  Serial.println(startTime);
//  Serial.print("millis:");
//  Serial.println(millis());
//  Serial.print("Number:");
//  Serial.println(number);
//  Serial.print("Ones:");
//  Serial.println(ones);
//  Serial.print("Tens:");
//  Serial.println(tens);
//  Serial.print("Hundreds:");
//  Serial.println(hundreds);
//  Serial.print("Thousands:");
//  Serial.println(thousands);

  displayNumber(1, thousands);
  delay (delayAmt);
  displayNumber(2, hundreds);
  delay (delayAmt);
  displayNumber(3, tens);
  delay (delayAmt);
  displayNumber(4, ones);
  delay (delayAmt);

}


  

void pickDigit(int x)
{
  digitalWrite(dgt1Pin, HIGH);
  digitalWrite(dgt2Pin, HIGH);
  digitalWrite(dgt3Pin, HIGH);
  digitalWrite(dgt4Pin, HIGH);
  
  switch(x)
  {
    case 1: digitalWrite(dgt1Pin, LOW); break;
    case 2: digitalWrite(dgt2Pin, LOW); break;
    case 3: digitalWrite(dgt3Pin, LOW); break;
    case 4: digitalWrite(dgt4Pin, LOW); break;
  }
}

void displayNumber(int digit, int number)
{
  pickDigit(digit);
  switch(number)
  {
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    default: zero(); break;
  }
}

void blank(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void zero(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
}

void one(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void two(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}

void three(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
}

void four(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}

void five(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}

void six(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}

void seven(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
}

void eight(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}

void nine(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
}
