#include <avr/io.h>
#include <util/delay.h>

#define OUT1      PB0
#define OUT2      PB2
#define OUT3      PL0
#define OUT4      PL2
#define MAX_ON      10666
#define MIN_ON      3300

void init_pins(void);
void init_timer(void);

void init_pins(void){
  DDRB = (1 << OUT1) | (1 << OUT2) | (1 << PB6) | (1 << PB5);
  DDRL = (1 << OUT3) | (1 << OUT4);
}

void init_timer(void){
  // make sure the power reduction pin is on
  PRR0 &= ~(1 << PRTIM1);

  // Configure the timer
  TCCR1A = (1 << COM1A1) 
          | (1 << COM1B1) 
          | (1 << COM1C1) 
          | (1 << WGM11); // Fast PWM

  TCCR1B = (1 << CS10)
          | (1 << WGM13) 
          | (1 << WGM12); // Fast PWM

  ICR1 = MAX_ON;                            // This is the top value
  OCR1A = 5000;
  OCR1B = 5000;
}

int main(void){
  Serial.begin(9600);
  init_pins();
  init_timer();

  while(1){
    PORTB |= (1 << OUT1);
    PORTL |= (1 << OUT3);
    _delay_ms(1000);
    PORTB = 0;
    PORTL = 0;
    _delay_ms(1000);
    PORTB |= (1 << OUT2);
    PORTL |= (1 << OUT4);
    _delay_ms(1000);
    PORTB = PORTL = 0;
    _delay_ms(1000);
  }

  return 0;
}
