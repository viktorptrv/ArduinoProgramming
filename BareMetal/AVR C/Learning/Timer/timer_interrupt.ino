#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t brightnessA;
volatile uint8_t brightnessB;

static inline void init_timers(void);
static inline void init_timers(void){
  TCCR0B |= (1 << CS02);        // 1024 for ISR timing
  TIMSK0 |= (1 << OCIE0A);
  TIMSK0 |= (1 << TOIE0);
  sei();                        // turn on interrupts
}

ISR (TIMER0_OVF_vect){
  PORTB |= (1 << 1);
  OCR0A = brightnessA;
  OCR0B = brightnessB;
}

ISR (TIMER0_COMPA_vect){
  PORTB = 0;
}

int main(void){
  uint8_t i;  
  DDRB |= (1 << 1);
  init_timers();

  while(1){
    for(i = 0; i < 255; i++){
      _delay_ms(3);
      brightnessA = i;
      brightnessB = 255 - i;
    }

    for(i = 253; i > 0; i++){
      _delay_ms(3);
      brightnessA = i;
      brightnessB = 255 - i;
    }

  }
}
