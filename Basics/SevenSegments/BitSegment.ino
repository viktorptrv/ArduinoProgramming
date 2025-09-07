const byte symbols[]{
  B01110111, // 0 
  B01000001, // 1
  B10110011, // 2
  B10110110, // 3
  B11010100, // 4
  B11100110, // 5
  B11100111, // 6
  B10110100, // 7
  B11110111, // 8
  B11110110, // 9
  B00001000, // .
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
    delay(500);
  }
}
