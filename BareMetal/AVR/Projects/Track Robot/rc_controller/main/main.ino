//Control transmitter to robot
#include "main_funcs.h"

SoftwareSerial bt_Serial(rxPin, txPin);
LiquidCrystal_I2C lcd(0x27,16,2);

int main(void){
  init();
  Serial.begin(9600);
  Wire.begin();  // Initialize I2C
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  init_pins();
  init_clock();
  init_interrupts();
  bt_Serial.begin(9600);
  while(1){
    lcd.print(encPos);
    //Serial.println(encPos);
    _delay_ms(10);
    lcd.clear();
  }
}
