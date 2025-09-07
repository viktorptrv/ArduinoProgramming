const byte symbols[]{
  B00000001, 
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000
};

const int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup(){
  for (int i = 0; i < 8; i++){
    pinMode(pins[i], OUTPUT);
  }
}

void loop(){
  for (int i = 0; i < 11; i++){
    for (int pin = 0; pin < 8; pin++)
      digitalWrite(pins[pin], bitRead(symbols[i], pin));
    delay(10000);
  }
}
