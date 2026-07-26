#include <avr/io.h>
#include <util/delay.h>


int setBitON(byte *addr, int bit);
int setBitOFF(byte *addr, int *bit);

volatile byte* _PORTB = 0x25;
volatile byte* _DDRB = 0x24;

int main(void){
int iRes = 0;
  iRes = setBitON(_DDRB, (1<<5));
  while(1){
    iRes = setBitON(_PORTB, (1<<5));
    _delay_ms(1000);
    iRes = setBitOFF(_PORTB, NULL);
    _delay_ms(1000); 
  }

  return 0;
}

int setBitON(byte *addr, int bit){
  if (addr == NULL){
    return 0;
  }
  *addr |= bit;
  return 1;
}

int setBitOFF(byte *addr, int *bit){
  if (addr == NULL){
    return 0;
  }
  if (bit == NULL){
   *addr &= 0;
  }
  else{
    *addr &= ~(*bit);
  }
  return 1;
}
