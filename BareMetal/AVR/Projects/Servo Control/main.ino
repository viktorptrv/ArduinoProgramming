#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define PULSE_MIN 1000
#define PULSE_MAX 2000
#define PULSE_MID 1500

void init_timer1_servo(void);
void init_timer1_servo(void){
  // We have to setup TIMER1 to give a pulse every 20ms
  // We are going to use FASTPWM mode, counter max in ICR1
  TCCR1A |= (1 << WGM11);                   // Set Fast PWM
  TCCR1B |= (1 << WGM12) | (1 << WGM13);    // Set CTC
  TCCR1B |= (1 << CS10)                     // Set no prescalling (we count in microseconds)
  ICR1 = 20000;                             // Sets direct output on PB1
  TCCR1A |= (1 << COM1A1);                  // Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode)
  DDRB |= (1 << PB1);
}

int main(void){
  // Inits
  uint16_t servoPulseLength;
  OCR1A = PULSE_MID;
  init_timer1_servo();
}
