#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define CPU_MHZ     16000000
#define prescaler   1024

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
  return return_value;
}

int main(void){
  double lastDebounceTime;
  uint8_t lastState = 0, button_state;

  DDRB |= (1 << 1);      // For the led
  PORTD |= (1 << 2);    // Making the port pull up
  
  init_timer();
  Serial.begin(9600);
  Serial.print("PORTB VALUE: ");
  Serial.println(PIND);
  _delay_ms(1500);
  while(1){
    if ((PIND & (1 << 2)) != lastState){
      Serial.println("Different than last state");
      lastDebounceTime = get_time();
    }

    if ((get_time() - lastDebounceTime) > 0.1){
      if ((PIND & (1 << 2)) != button_state){
        button_state = (PIND & (1 << 2));
        Serial.print("State of PINB = ");
        Serial.println(button_state);
        if (button_state == 0){
          PORTB |= (1 << 1);
          _delay_ms(500);
          PORTB &=~ (1 << 1);
        }
      }
    }

    lastState = (PIND & (1 << 2));
  }
}
