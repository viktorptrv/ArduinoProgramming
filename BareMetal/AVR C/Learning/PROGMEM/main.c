#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

const char myVeryLongString[] PROGMEM = "\r\nHi there, \
this is an example of a long string.\r\n\
The kind that you wouldn't want to store in RAM.\r\n";
const uint16_t sixteenBits PROGMEM = 12345;

int main(void){
  char oneLetter;
  uint8_t i;
  Serial.begin(9600);

  while(1){
    for(i = 0; i < sizeof(myVeryLongString); i++){
      oneLetter = pgm_read_byte(&(myVeryLongString[i]));
      Serial.print(oneLetter);
      _delay_ms(100);
    }
    _delay_ms(1000);

    Serial.print((uint8_t)(&sixteenBits) >> 8);
    Serial.println((uint8_t)(&sixteenBits));
    Serial.print(pgm_read_word(&sixteenBits));
  }
}
