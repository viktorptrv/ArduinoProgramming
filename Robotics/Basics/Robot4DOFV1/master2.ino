#include <Wire.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <string.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#define SLAVE_ADDR 0x8
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
byte NegativeZ = 3;
byte PositiveZ = 4;
byte NegativeY = 5;
byte PositiveY = 6;
byte NegativeX = 7;
byte PositiveX = 12;
int PosX = 0; int PosY = 0; int PosZ = 0;
int* pos[] = {&PosX, &PosY, &PosZ};
char posBuffer[4];

byte allButtons[8] = {send_butt,  NegativeZ,
                     PositiveZ, NegativeY, PositiveY,
                     NegativeX, PositiveX};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 8; i++){
    pinMode(allButtons[i], INPUT_PULLUP);
  }
  Wire.begin();
  attachInterrupt(digitalPinToInterrupt(send_butt), send_position_to_robot, FALLING);
  Serial.begin(9600);
  Serial.println("Arduino is starting");
  u8g2.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(NegativeZ) == LOW){
    if (PosZ > 0){
      PosZ -= 5;
      Serial.print("Negative Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(NegativeY) == LOW){
    if (PosY > 0){
      PosY-= 5;
      Serial.print("Negative Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(NegativeX) == LOW){
    if (PosX > 0){
      PosX-= 5;
      Serial.print("Negative X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }
  if (digitalRead(PositiveZ) == LOW){
    if (PosZ < 180){
      PosZ+=5;
      Serial.print("Positive Z -> ");
      Serial.println(PosZ);
      delay(125);
    }
  }
  if (digitalRead(PositiveY) == LOW){
    if (PosY < 180){
      PosY+=5;
      Serial.print("Positive Y -> ");
      Serial.println(PosY);
      delay(125);
    }
  }
  if (digitalRead(PositiveX) == LOW){
    if (PosX < 180){
      PosX+=5;
      Serial.print("Positive X -> ");
      Serial.println(PosX);
      delay(125);
    }
  }

  if (sendPos == true || manualPos == true){
    send_position_to_robot();
    Serial.println("Send pos");
  }

  u8g2.clearBuffer();

  draw_menu();
  delay(100);

  u8g2.sendBuffer();
  delay(100);
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

     // Highlight selected item
    u8g2.drawBox(0, i * h, w, h);

      // Inverted text
    u8g2.setDrawColor(0);
    u8g2.drawStr(d, i * h, menu_strings[i]);
    clear_pos_buffer();
    create_char_buffer(*pos[i]);
    u8g2.drawStr(d + 30, i* h, posBuffer);
  
      // Restore normal drawing
    u8g2.setDrawColor(1);
    if (sendPos == true){
      d = (w - u8g2.getStrWidth("Moving robot...")) / 2;
      u8g2.drawStr(d, 4 * h, "Moving robot...");
    }
  }

  if (sendPos == true){
    char command[20];
    snprintf(command, 20, "x=%d; y=%d; z=%d", PosX, PosY, PosZ);
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(command);
    Wire.endTransmission();
    sendPos = false;
  }
}

void clear_pos_buffer(void){
  for(int i = 0; i < 4; i++){
    posBuffer[i] = '\0';
  }
}

void create_char_buffer(int num){
  snprintf(posBuffer, sizeof(posBuffer), "%d", num);
  Serial.print("Buffer string: ");
  Serial.println(posBuffer);
}

void send_position_to_robot(void){
  sendPos = true;
}
