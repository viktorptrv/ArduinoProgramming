#include <avr/io.h>
#include <util/delay.h>

#define OUT1      PB0
#define OUT2      PB2
#define OUT3      PL0
#define OUT4      PL2
#define MAX_ON      10666
#define MIN_ON      3300
#define INTS1        PD1
#define INTS2        PD0
#define PWM_PER_ENC  73   
#define PINS_HIGH   0b00000011

volatile int8_t aFlag = 0;
volatile int8_t bFlag = 0;
volatile int8_t encPos = 0;
volatile int8_t oldEncPos = 0;
volatile int8_t reading = 0;

volatile int8_t int_a = 0;
volatile int8_t int_b = 0;

void init_pins(void);
void init_timer(void);
void init_interrupts(void);
void set_speed(int16_t speed);
int16_t map_enc_speed(int16_t enc_speed);

void init_pins(void){
  DDRB = (1 << OUT1) | (1 << OUT2) | (1 << PB6) | (1 << PB5);
  DDRL = (1 << OUT3) | (1 << OUT4);

  // Make the interrupts pull up input
  DDRD &= ~((1 << INTS1) | (1 << INTS2));   // make sure the outputs are set up as inputs;
  PORTD |= (1 << INTS1) | (1 << INTS2);     // enable pull_up input;
}

void init_timer(void){
  // make sure the power reduction pin is on
  PRR0 &= ~(1 << PRTIM1);

  // Configure the timer
  TCCR1A = (1 << COM1A1) 
          | (1 << COM1B1) 
          | (1 << WGM11); // Fast PWM

  TCCR1B = (1 << CS10)
          | (1 << WGM13) 
          | (1 << WGM12); // Fast PWM

  ICR1 = MAX_ON;                            // This is the top value
  OCR1A = 5000;
  OCR1B = 5000;
}

void init_interrupts(void){
  // disable interrupts
  cli();

  EICRA |= (1 << ISC00) | (1 << ISC01); // Rising edge on INTS0
  EICRA |= (1 << ISC10) | (1 << ISC11); // Rising edge on INTS1
  EIMSK |= (1 << INT1) | (1 << INT0);

  sei();  // Enable interrupts again;
}

ISR(INT0_vect){
  //int_a = 1;
  reading = PIND & 0b00000011;
  if (reading == PINS_HIGH && aFlag){
    encPos--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == 0b00000001)
    bFlag = 1;
}

ISR(INT1_vect){
  //int_b = 1;
  reading = PIND & 0b00000011;
  if (reading == PINS_HIGH && bFlag){
    encPos++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == 0b00000010)
    aFlag = 1;
}

void set_speed(int16_t speed){
  OCR1A = speed;
  OCR1B = speed;
}

int16_t map_enc_speed(int16_t enc_speed){
  int16_t res = PWM_PER_ENC * enc_speed;
  return (res + MIN_ON);
}

int main(void){
  int16_t enc_speed = 0;
  Serial.begin(9600);
  init_pins();
  init_timer();
  init_interrupts();

  while(1){
    PORTB |= (1 << OUT1);
    PORTL |= (1 << OUT3);

    /*
    if (int_a & 1){
      Serial.println("ISR_1");
    }
    if (int_b & 1){
      Serial.println("ISR_2");
    }
    int_a = int_b = 0;
    Serial.print("encPos = ");
    Serial.println(encPos);
    */

   
    if (oldEncPos != encPos){
      if (encPos < 0)
        encPos = 0;
      else if (encPos > 100)
        encPos = 100;
      Serial.print("Encoder pose = ");
      Serial.println(encPos);
      oldEncPos = encPos;
      enc_speed = map_enc_speed(encPos);
      set_speed(enc_speed);
    }
  }

  return 0;
}
