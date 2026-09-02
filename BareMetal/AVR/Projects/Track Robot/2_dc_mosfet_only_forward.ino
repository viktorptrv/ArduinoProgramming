#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define SPEED_STEP_DELAY 2

static inline void initTimer0(void){
  TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << COM0B1) | (1 << COM0A1);
  TCCR0B |= (1 << CS02);
}

int main(void){
  uint8_t updateSpeed;

  initTimer0();
  OCR0B = 0;
  OCR0A = 0;

  DDRD |= (1 << PD5);
  DDRD |= (1 << PD6);

  while(1){
    updateSpeed = 255;  // currently motor is ran at 245hz

    if (OCR0B < updateSpeed && OCR0A < updateSpeed){
      while (OCR0B < updateSpeed && OCR0A < updateSpeed){
        OCR0B++;
        OCR0A++;
        _delay_ms(SPEED_STEP_DELAY);
      }
    }
    else{
      updateSpeed = 0;
      while (OCR0B > updateSpeed && OCR0A > updateSpeed){
        OCR0B--;
        OCR0A--;
        _delay_ms(SPEED_STEP_DELAY);
      }
    }
  }

}
