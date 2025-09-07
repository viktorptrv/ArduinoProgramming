#define G 9
#define F 8
#define A 7
#define B 6
#define DP 5
#define C 4
#define D 3
#define E 2

int leds[] = {A, B, C, D, E, F, G, DP};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 8; i++){
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 8; i++){
    digitalWrite(leds[i], HIGH);
    delay(500);
    digitalWrite(leds[i], LOW);
  }
}
