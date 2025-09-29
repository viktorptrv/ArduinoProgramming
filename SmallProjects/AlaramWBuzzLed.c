const byte Buzz = 3;
const byte LED = 4;
const byte Sens = 8;

void setup(){
  pinMode(Buzz, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(Sens, INPUT);
  Serial.begin(115200);
}

void loop(){
  int readSens, count;
  readSens = digitalRead(Sens);
  if (readSens == 1){
    count = 0;
    while(count < 10){
      digitalWrite(LED, HIGH);
      tone(Buzz, 2000);
      delay(100);
      digitalWrite(LED, LOW);
      noTone(Buzz);
      delay(50);
      count++;
    }
  }
}
