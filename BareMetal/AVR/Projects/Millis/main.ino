#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define CPU_MHZ     16000000
#define prescaler   1024

const volatile float time_passed = 0.00000104448;
signed long long int volatile millis_pas = 0;

static inline void init_timer(void){
  TCCR0A |= (1 << WGM01);                // Enable CTC mode
  TCCR0B |= (1 << CS02) | (1 << CS00);  // Setting prescaler to 1024
  TIMSK0 |= (1 << OCIE0A);              // Enabling timer Interrupt
  OCR0A = 255;                // 15625
  sei();
}

ISR(TIMER0_COMPA_vect){
  millis_pas += 16384;
}

double get_time(void){
  char cSREG;
  double return_value;
  cSREG = SREG;
  cli();
  return_value = millis_pas;
  SREG = cSREG;
  return_value = (return_value * 1.0) / (1000000.0);
  Serial.print("Current millis:");
  Serial.println(return_value);
  return return_value;
}

int main(void){
  double current = 0;
  double now = 0;
  init_timer();
  Serial.begin(9600);
  while(1){
    if ((get_time()-current) > 10){
      Serial.println("timed:");
      Serial.print(get_time());
    }
  }
}
