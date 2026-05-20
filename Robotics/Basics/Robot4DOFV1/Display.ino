#include <Arduino.h>
#include <U8g2lib.h>
#include <string.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define MENU_ITEMS 3
char *menu_strings[MENU_ITEMS] = { "X = ", "Y = ", "Z = "};
int menu_current = 0;

U8G2_SSD1309_128X64_NONAME2_F_4W_SW_SPI u8g2(
  U8G2_R0,
  /* clock=*/ 13,
  /* data=*/ 11,
  /* cs=*/ 10,
  /* dc=*/ 9,
  /* reset=*/ 8
);

volatile bool sendPos = false;
volatile bool manualPos = false;
byte send_butt = 2;
byte mode_butt = 3;
byte NegativeZ = 4;
byte PositiveZ = 5;
byte NegativeY = 6;
byte PositiveY = 7;
byte NegativeX = 8;
byte PositiveX = 9;
int PosX = 0; int PosY = 0; int PosZ = 0;
int pos[] = {PosX, PosY, PosZ};
char posBuffer[4];

byte allButtons[8] = {send_butt, mode_butt, NegativeZ,
                     PositiveZ, NegativeY, PositiveY,
                     NegativeX, PositiveX};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++){
    pinMode(allButtons[i], INPUT_PULLUP);
  }

  attachInterrupt(digitalPinToInterrupt(send_butt), send_command, FALLING);
  attachInterrupt(digitalPinToInterrupt(mode_butt), change_mod, FALLING);
  Serial.begin(9600);
  Serial.println("Arduino is starting");
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(NegativeZ) == LOW){
    if (PosZ > 0){
      PosZ--;
      Serial.print("Negative Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(NegativeY) == LOW){
    if (PosY > 0){
      PosY--;
      Serial.print("Negative Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(NegativeX) == LOW){
    if (PosX > 0){
      PosX--;
      Serial.print("Negative X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }
  if (digitalRead(PositiveZ) == LOW){
    if (PosZ < 180){
      PosZ++;
      Serial.print("Positive Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(PositiveY) == LOW){
    if (PosY < 180){
      PosY++;
      Serial.print("Positive Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(PositiveX) == LOW){
    if (PosX < 180){
      PosX++;
      Serial.print("Positive X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }

  if (sendPos == true || manualPos == true){
    send_position_to_robot();
    delay(200);
  }

  u8g2.clearBuffer();

  draw_menu();

  u8g2.sendBuffer();

  update_menu();
}

void draw_menu()
{
  uint8_t i;
  int h;
  int d;
  int w;

  u8g2.setFont(u8g2_font_6x13_tr);
  u8g2.setFontPosTop();

  h = u8g2.getAscent() - u8g2.getDescent();
  w = u8g2.getDisplayWidth();

  for (i = 0; i < MENU_ITEMS; i++)
  {
    d = (w - u8g2.getStrWidth(menu_strings[i])) / 2;

    if (i == menu_current)
    {
      // Highlight selected item
      u8g2.drawBox(0, i * h, w, h);

      // Inverted text
      u8g2.setDrawColor(0);
      u8g2.drawStr(d, i * h, menu_strings[i]);
      clear_pos_buffer();
      create_char_buffer(pos[i]);
      u8g2.drawStr(d + 30, i* h, posBuffer);

      // Restore normal drawing
      u8g2.setDrawColor(1);
    }
    else
    {
      u8g2.drawStr(d, i * h, menu_strings[i]);
    }
  }
}

void clear_pos_buffer(void){
  for(int i = 0; i < 4; i++){
    posBuffer[i] = '\0';
  }
}

void create_char_buffer(int num){
  snprintf(posBuffer, sizeof(posBuffer), "%d", num);
}

void update_menu(void)
{

}

void send_command(void){
  sendPos = !sendPos; // flip bool value
}

void change_mod(void){
  //manualPos = !manualPos; // flip bool value
  menu_current++;
  if (menu_current >= 3){
    menu_current = 0;
  }
}

void send_position_to_robot(void){
  Serial.println("Robot Pos Function called");
  sendPos = !sendPos;
}
