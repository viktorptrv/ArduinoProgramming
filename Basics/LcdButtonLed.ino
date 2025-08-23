#include <LiquidCrystal.h>

const int gnd = A0;
const int vcc = A4;
const int z = A1;
const int y = A2;
const int x = A2;
const int LED = 8;
const int Button = 9;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 pinMode(x, INPUT);
 pinMode(y, INPUT);
 pinMode(z, INPUT);
 pinMode(LED, OUTPUT);
 pinMode(Button, INPUT);
 // Setting A0 as a gnd:
 pinMode(gnd, LOW);
 // Setting A4 as a vcc;
 pinMode(vcc, HIGH);
 lcd.begin(16, 2);
 lcd.print("Flashing Mode: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  int y, x, z;
  int mode = 0;
  mode = digitalRead(Button);
  Serial.print("Mode:");
  Serial.print(mode);
  y = analogRead(y);
  x = analogRead(x);
  z = analogRead(z);
  lcd.setCursor(0, 1);
  if (mode == 0){
    lcd.print("-> Single     ");
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
  }
  else{
    lcd.print("-> Continuous");
    digitalWrite(LED, HIGH);
    delay(5000);
    digitalWrite(LED, LOW);
  }
  delay(2000);
  /*Serial.println("X = ");
  Serial.print(x);
  Serial.println("Y = ");
  Serial.print(y);
  Serial.println("Z = ");
  Serial.print(z);*/
}
