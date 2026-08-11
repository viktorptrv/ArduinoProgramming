#include <avr/io.h>
#include <util/delay.h>

#define BUZZER 10

void init_port(void);
void init_adc(void);

void init_port(void){

}

void init_adc(void){

}

int main(void){
  // init pins
  init_port();
  // init adc
  init_adc();

  while(1){

  }

  return 0;
}
