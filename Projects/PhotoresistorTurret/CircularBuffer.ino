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

byte buffer_full[3]    = {0, 0, 0};
byte display_value[3]  = {0, 0, 0};

int display_width;
int display_height;

int sens1Buffer[8];
int sens2Buffer[8];
int sens3Buffer[8];
int buff_idx[3] = {0, 0, 0};

int add_to_buffer(int number, int buffer[], int sensBufferIdx);
int average_buffer(int buffer_num, int buffer[]);

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
  tft.setRotation(0);
}

void loop(void) {
  int res_sens1, res_sens2, res_sens3;
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextSize(5);
  tft.setTextColor(GC9A01A_PURPLE);

  // --- Sensor 1 ---
  int sens1 = analogRead(A3);
  res_sens1 = add_to_buffer(sens1, sens1Buffer, 0);
  if (res_sens1 & 2 || buffer_full[0] & 1) {
    sens1 = average_buffer(0, sens1Buffer);
    Serial.print("Average sens 1 -> ");
    Serial.println(sens1);
  }

  // --- Sensor 2 ---
  int sens2 = analogRead(A4);
  res_sens2 = add_to_buffer(sens2, sens2Buffer, 1);
  if (res_sens2 & 2) {
    sens2 = average_buffer(1, sens2Buffer);
    Serial.print("Average sens 2 -> ");
    Serial.println(sens2);
  }

  // --- Sensor 3 --- (fixed: was using res_sens2)
  int sens3 = analogRead(A5);
  res_sens3 = add_to_buffer(sens3, sens3Buffer, 2);
  if (res_sens3 & 2) {
    sens3 = average_buffer(2, sens3Buffer);
    Serial.print("Average sens 3 -> ");
    Serial.println(sens3);
  }

  // --- Servo / Display logic ---
  if (display_value[0] & 1) {
    if (sens2 < 575) {
      servo.write(0);
      tft.drawCircle(display_width / 2, (display_width / 2 - 50), 10, GC9A01A_PURPLE);
    }
    display_value[0] &= ~1;  // clear flag after acting
  }

  if (display_value[1] & 1) {
    if (sens2 < 510) {
      servo.write(90);
      tft.drawCircle(display_width / 2, display_width / 2, 10, GC9A01A_PURPLE);
    }
    display_value[1] &= ~1;
  }

  if (display_value[2] & 1) {
    if (sens3 < 575) {
      servo.write(180);
      tft.drawCircle(display_width / 2, (display_width / 2 + 50), 10, GC9A01A_PURPLE);
    }
    display_value[2] &= ~1;
  }

  delay(1000);
}

// Fixed: write the value first, THEN check for wrap; sum all 8 elements
int add_to_buffer(int number, int buffer[], int sensBufferIdx) {
  buffer[buff_idx[sensBufferIdx]] = number;
  buff_idx[sensBufferIdx] += 1;

  if (buff_idx[sensBufferIdx] >= 8) {
    buff_idx[sensBufferIdx] = 0;
    buffer_full[sensBufferIdx] = 1;
    return 0x0002;  // buffer just completed, signal to average
  }
  return 0x0001;
}

// Fixed: sum all 8 elements and divide by 8
int average_buffer(int buffer_num, int buffer[]) {
  int res = 0;
  for (int i = 0; i < 8; i++) {
    res += buffer[i];
  }
  display_value[buffer_num] |= 1;
  return (res / 8);
}
