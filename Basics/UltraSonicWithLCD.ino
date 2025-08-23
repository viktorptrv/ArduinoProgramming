#include <LiquidCrystal.h>
#define trigPin 8
#define echoPin 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("Object Distance:" );
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long int duration, distance;
  lcd.setCursor(0, 1);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
  lcd.print(distance);
  lcd.print(" cm.");
  delay(1000);
  lcd.clear();
}
