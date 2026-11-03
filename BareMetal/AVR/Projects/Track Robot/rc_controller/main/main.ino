// Control transmitter to robot
#include "main_funcs.h"

int main(void){
  Serial.begin(9600);
  bt_Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursos(0,0);
  init_pins();
  init_clock();
  init_interrupts();

  while(1){

  }
}