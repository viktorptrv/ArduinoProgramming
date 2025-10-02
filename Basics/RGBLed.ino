const byte RED = 11;
const byte BLUE = 10;
const byte GREEN = 9;

void setup(){
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop(){
  for(int i = 0; i<255; i+=10){
    analogWrite(RED, i);
    analogWrite(BLUE, i);
    analogWrite(GREEN, i);
    delay(100);
  }
}
