//Pot middle pin connected to Analog 2
//Outside pins to 5V and Gnd.
//LED to pin 13.

int potPin = 2;
int ledPin = 13;
long val = 0;
long matchval = 0;
int precision = 3;
long closeness = 0;

void setup() {
  pinMode(ledPin,OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  
  matchval = random(0,1024);
}

void loop(){
  val = analogRead(potPin);
  //Serial.println(matchval);
  //Serial.println(val);


  closeness = matchval - val;
  Serial.println(closeness);
  if (closeness < 0){
    closeness = closeness * -1;
  }
  if ( closeness < precision ) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(10);
}
