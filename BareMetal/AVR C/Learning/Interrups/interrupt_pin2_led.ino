#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUTTON_PIN 2
#define LED1 4
#define LED2 5
#define LED3 6

bool led3_flag = false;

ISR(INT0_vect){
  led3_flag =!led3_flag;
}

void init_leds(void){
  DDRD |= (1 << LED1) | (1 << LED2) | (1 << LED3);

  // Configuring button pin as pullup 
  PORTD |= (1 << BUTTON_PIN);

  // Turning on the rest because they are configured as outputs;
  PORTD |= (1 << LED1) | (1 << LED2) | (1 << LED3); 
  _delay_ms(100);
  PORTD &= ~((1 << LED1) | (1 << LED2) | (1 << LED3));
  _delay_ms(1000);
}

void init_interrupt(void){
  EIMSK |= (1 << INT0);   // Enable INT0
  EICRA |= (1 << ISC01) | (1 << ISC00);  // Trigger when button changes
  sei();                  // Enable global interrupt bit
}

int main(void){
  init_leds();
  init_interrupt();

  while(1){
    _delay_ms(200);
    PORTD ^= (1 << LED1) | (1 << LED2);
    if (led3_flag == true){
      PORTD |= (1 << LED3);
    }
    else{
      PORTD &= ~(1 << LED3);
    }
  }
}
