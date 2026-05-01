const int dataPin = 5;
const int clockPin = 6;

byte x = 0;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (x > 100){
    x = 0;
  }

  sendByte(x);
  x++;
  delay(1000);
}

void sendByte(byte b){
  for (int i = 0; i < 8; i++){
    // det the data high or low
    digitalWrite(dataPin, bitRead(b, 7-i));
    delay(1);
    digitalWrite(clockPin, HIGH); // start clock pulse
    delay(1);
    digitalWrite(clockPin, LOW);
    delay(1);
  }
}
