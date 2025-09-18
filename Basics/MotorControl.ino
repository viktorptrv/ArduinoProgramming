int speed = 3;
int direction = 2;

bool directions = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(speed, OUTPUT);
  pinMode(direction, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(direction, directions);
  analogWrite(speed, 50);
  delay(5000);
  directions = LOW;
  analogWrite(speed, 0);
  delay(1000);
  digitalWrite(direction, directions);
  analogWrite(speed, 100);
  directions = HIGH;
  analogWrite(speed, 0);
  delay(1000);
}
