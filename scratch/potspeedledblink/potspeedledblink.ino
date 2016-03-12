int potPin = 2;
int ledPin = 13;
int val = 0;

void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  val = analogRead(potPin);
  Serial.println(val);
  if (val < 25){
    val = 25;
  }
  
  digitalWrite(ledPin, HIGH);
  delay(val);
  digitalWrite(ledPin, LOW);
  delay(val);
}
