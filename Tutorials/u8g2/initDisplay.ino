#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(
  U8G2_R0,
  /* clock=*/ 13,
  /* data=*/ 11,
  /* cs=*/ 10,
  /* dc=*/ 9,
  /* reset=*/ 8
);

void setup(void)
{
  u8g2.begin();
}

void drawScreen(const char* text)
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_tinytim_tf );
  u8g2.drawStr(0, 24, text);

  u8g2.sendBuffer();
}

void loop(void)
{
  drawScreen("Hello World!");
  delay(1000);

  drawScreen("Hello Wor2");
  delay(500);
}
