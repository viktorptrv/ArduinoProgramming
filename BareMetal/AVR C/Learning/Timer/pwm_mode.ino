#include <avr/io.h>
#include <util/delay.h>

static inline void init_timers(void);
static inline void init_timers(void){
  TCCR1A |= (1 << WGM10);     // Setting up PWM FAST PWM mode
  TCCR1B |= (1 << WGM12);     // Setting up PWM FAST PWM mode
  TCCR1B |= (1 << CS12);      // Setting up FREQUENCY 16MHZ / 256
  TCCR1A |= (1 << COM1A1);    // Compare output mode for channel A
  OCR1A = 0;
}

int main(void){
  int num, state;
  DDRB |= (1 << 1);
  init_timers();
  while(1){
    if (num == 0){
      state = 1;
    }
    if (num == 255){
      state = -1;
    }

    num += state;
    OCR1A = num;
    _delay_us(200);
  }

  return 0;
}
