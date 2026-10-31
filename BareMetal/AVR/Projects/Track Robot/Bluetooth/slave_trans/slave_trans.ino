#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 11;

SoftwareSerial blSerial (rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  blSerial.begin(9600);
}

void loop() {
  int state = 0;
  // put your main code here, to run repeatedly:
  if(blSerial.available() > 0){
    state = blSerial.read();
    Serial.print("Received: ");
    Serial.println(state);
    delay(100);
  }
  if (state == 1){
    Serial.println("Turning on LED1");
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(5, LOW);
    delay(10);
  }
  else if (state == 2){
    Serial.println("Turning on LED2");
    digitalWrite(6, HIGH);
    delay(200);
    digitalWrite(6, LOW);
    delay(10);
  }
  else if (state == 3){
    Serial.println("Turning on LED3");
    digitalWrite(7, HIGH);
    delay(200);
    digitalWrite(7, LOW);
    delay(10);
  }
}
