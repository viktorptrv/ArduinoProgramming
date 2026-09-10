#include <avr/io.h>
#include <util/delay.h>

#define SCK           PB5
#define MISO          PB4
#define MOSI          PB3
#define SS            PB2 
#define SLAVESELECT   DDRB &=~ (1 << SS)
#define SLAVEDESELECT DDRB |= (1 << SS)

static inline void init_SPI(void){
  DDRB |= (1 << SS) | (1 << MOSI) | (1 << SCK);
  PORTB |= (1 << SS) | (1 << SCK);    // pull the slave pin high
  PORTN |= (1 << MISO);

  SPCR |= (1 << MSTR) | (1 <<SPR0);
  SPCR |= (1 << SPE);
}

int main(void){

}
