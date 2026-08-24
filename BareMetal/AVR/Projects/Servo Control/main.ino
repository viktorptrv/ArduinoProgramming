#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_MIN 625
#define PULSE_MAX 125
#define PULSE_MID 350

static inline void init_timer1_servo(void);
static inline void init_timer1_servo(void){
  // We have to setup TIMER1 to give a pulse every 20ms
  // We are going to use FASTPWM mode, counter max in ICR1
  TCCR1A |= (1 << WGM11);                   // Set Fast PWM
  TCCR1B |= (1 << WGM12) | (1 << WGM13);    // Set CTC
  TCCR1B |= (1 << CS11) | (1 << CS10);      // prescaler /16 only — NOT CS10 too
  ICR1 = 4999;                               // 20000 ticks * 1µs = 20ms                         // Sets direct output on PB1
  TCCR1A |= (1 << COM1A1);                  // Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode)
  DDRB |= (1 << PB1);
}

static inline void showOff(void){
  OCR1A = PULSE_MID;
  _delay_ms(1500);
  OCR1A = PULSE_MIN;
  _delay_ms(1500);
  OCR1A = PULSE_MAX;
  _delay_ms(1500);
  OCR1A = PULSE_MID;
  _delay_ms(1500);
}

static inline void moveServo(uint16_t pulse_width);
static inline void moveServo(uint16_t pulse_width){
  OCR1A = pulse_width;
}

int main(void){
  // Inits
  uint16_t servoPulseLength;
  OCR1A = PULSE_MID;
  init_timer1_servo();
  showOff();

  while(1){
    for (uint16_t pos = PULSE_MAX; pos <= PULSE_MIN; pos+= 5){
      moveServo(pos);
      _delay_ms(1500);
    }
  }
}
