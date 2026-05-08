#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#include <Servo.h>

#define TFT_DC  9
#define TFT_CS 10
#define TFT_RS 8
#define ServoPIN 6

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RS);
Servo servo;

int display_width;
int display_height;

void setup() {
  Serial.begin(9600);
  Serial.println("GC9A01A Test!");
  servo.attach(ServoPIN);
  servo.write(90);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  tft.begin();

  display_width  = tft.width();  
  display_height = tft.height();

  Serial.print("W: "); Serial.println(display_width);
  Serial.print("H: "); Serial.println(display_height);
  Serial.println(F("Done!"));

  tft.setRotation(0);
  //tft.setTextSize(2);
   
}

void loop(void) {
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextSize(5);
  tft.setTextColor(GC9A01A_PURPLE);
  
  int sens1 = analogRead(A3);
  int sens2 = analogRead(A4);
  int sens3 = analogRead(A5); 
  Serial.print("Sens A3 - >");
  Serial.println(sens1);
  Serial.print("Sens A4 - >");
  Serial.println(sens2);
  Serial.print("Sens A5 - >");
  Serial.println(sens3);

  if (sens1 < 575){
    servo.write(0);
    tft.drawCircle(display_width / 2, (display_width / 2 - 50),  10, GC9A01A_PURPLE);
  }
  if (sens2 < 575){
    servo.write(90);
    tft.drawCircle(display_width / 2, display_width / 2,  10, GC9A01A_PURPLE);
  }
  if (sens3 < 575){
    servo.write(180);
    tft.drawCircle(display_width / 2, (display_width / 2 + 50),  10, GC9A01A_PURPLE);
  }

  delay(500);
}
