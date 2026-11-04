#include "main_funcs.h"

double timer = 0;
int8_t volatile aFlag = 0;
int8_t volatile bFlag = 0;
int8_t volatile encPos = 0;
int8_t volatile enc_spd = 0;           // speed
int8_t volatile old_enc_spd = 0;
int8_t volatile enc_stp = 0;           // step
int8_t volatile old_enc_stp = 0;
int8_t volatile reading = 0;

int8_t inline received_from_robot(void){
  return bt_Serial.read();
}

uint8_t send_to_robot(int8_t val){
  return bt_Serial.write(val);
}

void init_pins(void){
  // all buttons must be configured as pull up input
  DDRB &=~ ((1 << BTN_MID) | (1 << BTN_RHT) | (1 << BTN_LFT));
  PORTB |= (1 << BTN_MID) | (1 << BTN_RHT) | (1 << BTN_LFT);

  DDRL &=~ ((1 << BTN_DWN) | (1 << BTN_UP));
  PORTL |= ((1 << BTN_DWN) | (1 << BTN_UP));

  DDRE &=~ ((1 << BTN_SPD) | (1 << BTN_STEP));
  PORTE |= ((1 << BTN_SPD) | (1 << BTN_STEP));

  DDRD &=~ ((1 << ENC_S1) | (1 << ENC_S2));  
  PORTD |= ((1 << ENC_S1) | (1 << ENC_S2)); 
}

void init_interrupts(void){
  uint8_t oldSREG = SREG;   // get the avr status register
  cli();
  EICRA |= (1 << ISC21) | (1 << ISC31) | (1 << ISC20) | (1 << ISC30);
  EICRB |= (1 << ISC41) | (1 << ISC51) | (1 << ISC40) | (1 << ISC50);
  EIMSK |= (1 << INT2) | (1 << INT3) 
        | (1 << INT4) | (1 << INT5);
  TIMSK3 |= (1 << OCIE3A); // When this bit is written to one, and the I-flag in the Status Register is set (interrupts globally enabled), the
                          //Timer/Countern Output Compare A Match interrupt is enabled.
  sei();
  SREG = oldSREG;
}

// START of interrupt service routines:
ISR (TIMER3_COMPA){
  timer += TIMER_INCREMENT;
}

ISR(INT2_vect){
  //int_a = 1;
  reading = PIND & 0b00000011;
  if (reading == ENC_PINS_HIGH && aFlag){
    encPos--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == ENC_PINA_READ)
    bFlag = 1;
}

ISR(INT3_vect){
  reading = PIND & 0b00000011;
  if (reading == ENC_PINS_HIGH && bFlag){
    encPos++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == ENC_PINB_READ)
    aFlag = 1;
}

ISR(INT4_vect){
  
}

ISR(INT5_vect){
  
}

// END OF interrupt service routines

// timer should have interrupt enabled
void init_clock(void){
  // make sure power reduction bit on timer 3 is disabled
  PRR1 &=~ (1 << PRTIM3);
  TCCR3B |= (1 << CS30) | (1 << CS31) | (1 << WGM32);     // set prescaler to 64
  TCCR3A &=~ ((1 << COM3A1) | (1 << COM3A0) | (1 << WGM30)); // make sure its disconnected from the ports
  OCR3A = 25;
}

void switch_enc_mode(void){
  enc_mode = ~enc_mode;             // change between speed and step
  lcd.clear();
  lcd.setCursor(1,0);
  if (enc_mode == 1)
    lcd.print("SPEED MODE");
  else if (enc_mode == 0)
    lcd.print("STEP MODE");
  _delay_ms(50);
}

void turn_on_led(Btn* btn){
  // make sure output is turned on;
  *btn->ddr_addr |= (1 << btn->btn);

  // turn on led
  *btn->port_addr |= (1 << btn->btn);
}

void turn_off_led(Btn* btn){
  //just turn off the output
  *btn->ddr_addr &=~ (1 << btn->btn);
}

int8_t bt_listening(void){
  return (bt_Serial.isListening()) ? 1 : 0;
}

int8_t bt_overflow(void){
  return (bt_Serial.overflow()) ? 1 : 0;
}