const int dataPin = 5;
const int clockPin = 6;

byte x = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin, INPUT_PULLUP); // pull up stops floating inputs
  pinMode(clockPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 8; i++){
    // wait for clock to go high
    while(digitalRead(clockPin) == LOW){};
    // read the data pin
    x = x << 1;                 //shift all the bits left one place
    x += digitalRead(dataPin);  // add the new bit
    // wait for the clock to go low to be ready for the next bit
    while(digitalRead(clockPin) == HIGH){};
  }
  Serial.println(x);
}
