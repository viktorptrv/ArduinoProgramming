int ledOne = 12;
int ledTwo = 11;
int Buzz = 10;
int sensorThres = 400;
int smokeIn = A5;

void setup(){
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(smokeIn, INPUT);
  Serial.begin(9600);
}

void loop(){
  int analogSensor = analogRead(smokeIn);
  Serial.print("Pin A0:");
  Serial.println(analogSensor);
  if (analogSensor > sensorThres){
    digitalWrite(ledOne, HIGH);
    digitalWrite(ledTwo, LOW);
    tone(Buzz, 1000, 200);
  }
  else{
    digitalWrite(ledOne, LOW);
    digitalWrite(ledTwo, HIGH);
    tone(Buzz, 1000, 200);
  }
  delay(100);
}
