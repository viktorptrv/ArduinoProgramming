// RECEIVER
#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const int ledPin = 7;
const int rxPin = 8;

RH_ASK driver(2000, rxPin, 11, 10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("Transmitter started");
}


void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)){
    int i;
    digitalWrite(ledPin, true);
    Serial.println("got:");
    for(i = 0; i < buflen; i++){
      Serial.println(buf[i], HEX);
      Serial.println(" (");
      Serial.println(char(buf[i]));
      Serial.println(") ");
    }
  }

  Serial.println("");
  delay(100);
  digitalWrite(ledPin, false);
}



// TRANSMITTER
#include <RadioHead.h>
#include <RH_ASK.h>
#include <SPI.h>

const int ledPin = 7;
const int txPin = 8;

RH_ASK driver(2000, 7, txPin, 10);

void setup(){
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.println("Transmitter started");
}

void loop(){
  const char*msg = "hello";
  Serial.println("t");
  digitalWrite(ledPin, HIGH);
  driver.send((uint8_t*)msg, strlen(msg));
  driver.waitPacketSent();
  digitalWrite(ledPin, LOW);
  Serial.println("x");
  delay(500);
}
