#include <avr/io.h>
#include <util/delay.h>

static inline void  setup_pin(void);
static inline void  setup_timer(void);
static inline void  play_note(uint8_t note, uint8_t duration);

static inline void  setup_timer(void){
  TCCR0A |= (1 << WGM01);               // Setup CTC Mode of operation
  TCCR0A |= (1 << COM0A0);              // setup compare output
  TCCR0B |= (1 << CS02) | (1 << CS00);  // Setup prescaler
}

static inline void  play_note(uint8_t note, uint8_t duration){
  Serial.println("Playing note");
  OCR0A = note;                         // Setup value for compare register

  DDRD |= (1 << 1);
  PORTD |= (1 << 1);
  while(duration){
    _delay_ms(1);
    duration--;
  }

  PORTD = 0;
  DDRD &= ~(1 << 1);
}

int main(void){
  Serial.begin(9600);
  setup_timer();
  
  while(1){
    play_note(4, 200);
    _delay_ms(200);
    play_note(2, 200);
    _delay_ms(200);
    play_note(3, 200);
    _delay_ms(200);
    play_note(4, 200);
    _delay_ms(200);
    play_note(5, 200);
    _delay_ms(200);
    play_note(6, 200);
    _delay_ms(200);
  }
}
