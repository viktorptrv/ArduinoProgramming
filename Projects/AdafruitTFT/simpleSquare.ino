#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

#define TFT_DC  9
#define TFT_CS 10
#define TFT_RS 8

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RS);

int display_width;
int display_height;

void setup() {
  Serial.begin(9600);
  Serial.println("GC9A01A Test!");

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  tft.begin();

  display_width  = tft.width();  
  display_height = tft.height();

  Serial.print("W: "); Serial.println(display_width);
  Serial.print("H: "); Serial.println(display_height);
  Serial.println(F("Done!"));

  tft.setRotation(0);
  tft.fillScreen(GC9A01A_BLACK);
  //tft.setTextSize(2);
   
}

void loop(void) {
  tft.setTextSize(5);
  tft.setTextColor(GC9A01A_PURPLE);
  tft.setCursor(display_width / 2 - 60, display_height / 2 - 8);
  tft.print("Hello world!"); // use print(), not write()
  for(int i = 0; i < 5; i++){
    tft.fillRect(display_width / 2 - 60, display_height / 2 - 8, display_width, display_height, GC9A01A_BLACK);
    yield();
    tft.drawRect(display_width / 2 - 60, display_height / 2 - 8, 50*(i+1), 20*(i+1), GC9A01A_PURPLE);
    delay(1000);
  }
}
