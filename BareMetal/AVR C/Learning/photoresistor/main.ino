#include <avr/io.h>
#include <util/delay.h>

byte ledPort;

static inline void initPort(void){
  DDRD |= (1<<2) | (1<<3) | (1<<4);
}

static inline void initADC0(void){
  ADMUX |= (1 << REFS0);
  ADCSRA  |= (1<< ADEN) | (1 << ADPS0) | (1 << ADPS1);
}

int main(void){
  // init
  uint8_t ledValue;
  uint16_t adcValue;
  uint8_t i;

  initPort();
  initADC0();

  Serial.begin(9600);

  // event Loop;
  while(1){
    ADCSRA |= (1 << ADSC); // start adc conversion
    loop_until_bit_is_clear(ADCSRA, ADSC);
    adcValue = ADC;
    ledValue = (adcValue >> 7);

    Serial.print("AdCVAlue:");
    Serial.println(ledValue);

    PORTD = 0;
    for(i = 0; i <= ledValue; i++){
      PORTD |= (1<<i+2);
    }
    _delay_ms(50);
  }

  return 0;
}
