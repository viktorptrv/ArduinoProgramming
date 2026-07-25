#include <avr/io.h>
#include <util/delay.h>

#define PORTB_ADDR *((volatile byte*)0x25)

int main(void){
  DDRB |= (1<<5);

  while(1){
    PORTB_ADDR |= (1<<5);
    _delay_ms(1000);
    PORTB_ADDR &= 0;
    _delay_ms(1000); 
  }

  return 0;
}
