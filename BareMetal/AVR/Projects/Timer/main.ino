#include <avr/io.h>
#include <util/delay.h>

void init_port(void);
void init_timer(void);

void init_port(void){
  DDRD |= (1 << 3);
  PORTD |= (1 << 4);
}

void init_timer(void){
  TCCR1B |= (1 << CS11) | (1 << CS10);
}

int main(void){
unsigned char sreg;     // Used to save global interrupt flag
uint8_t button_result;
  Serial.begin(9600);
  init_port();
  init_timer();

  PORTD |= (1 << 3);

  while(1){
    TCNT1 = 0;

    loop_until_bit_is_clear(PIND, (1 << PD4));
    Serial.print("TCNT1: ");
    Serial.println(TCNT1);
    PORTD &= ~(1 << 3); 
    TCNT1 = 0 ;
  }

  return 0;
}
