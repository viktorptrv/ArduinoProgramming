#include <LiquidCrystal.h>

const int gnd = A0;
const int vcc = A4;
const int z = A1;
const int y = A2;
const int x = A2;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 pinMode(x, INPUT);
 pinMode(y, INPUT);
 pinMode(z, INPUT);
 // Setting A0 as a gnd:
 pinMode(gnd, LOW);
 // Setting A4 as a vcc;
 pinMode(vcc, HIGH);
 lcd.begin(16, 2);
 lcd.print("Accelometer: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  int y, x, z;
  y = analogRead(y);
  x = analogRead(x);
  z = analogRead(z);
  lcd.setCursor(0, 1);
  lcd.print("X=");
  lcd.print(x);
  lcd.print(",Y=");
  lcd.print(y);
  lcd.print(",Z=");
  lcd.print(z);
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);
  delay(1000);
}
