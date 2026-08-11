#include <avr/io.h>
#include <util/delay.h>

#define BUZZER 8

void init_port(void);
void init_adc(void);
void turnOn_buzz(int time);

void init_port(void){
  DDRB |= (1 << PB0);
}

void init_adc(void){
  ADMUX  |= (1 << REFS0);     // Setting internal AVCC
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRA |= (1 << ADEN);
}

void turnOn_buzz(int time){
  PORTB |= (1 << PB0);
  _delay_us(time);
  PORTB &= ~(1 << PB0);
  _delay_us(time);
}

int main(void){
uint16_t adc_result;
uint8_t tone_value;

  // init pins
  init_port();
  // init adc
  init_adc();

  Serial.begin(9600);

  while(1){
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    adc_result = ADC;

    Serial.print("AdCVAlue:");
    Serial.println(adc_result);

    long int delay_time = (1023 - adc_result)/4; // invert so bright = fast
    PORTB |= (1 << PB0);
    for(int i = 0; i < delay_time; i++){
      _delay_ms(1);
    }

    PORTB &= ~(1 << PB0);
    for(int i = 0; i < delay_time; i++){
      _delay_ms(1);
    }

  }

  return 0;
}
