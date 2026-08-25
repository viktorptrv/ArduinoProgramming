#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Declarations
#define MAX_COUNTS 4999 
#define MAX_SERVO  625                     // Max servou duty cycle  for max right
#define MIN_SERVO  125                     // min servo duty cycle for full left
#define STEP_SERVO 5
#define ADC_PRESCALER ((1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0))

static inline void init_io(void);
static inline void init_timer(void);
static inline void init_adc(void);
static inline void turn_on_servo(void);
static inline void turn_off_servo(void);
static inline uint16_t get_anal_inp(uint8_t port);
static inline void move_servo(uint16_t step);

// Functions
static inline void init_io(void){
  DDRB |= (1 << PB1) | (1 << PB0);         // Pin 9 to control servo with PWM, Pin 8 - Status led
}

static inline void init_timer(void){
  TCCR1A |= (1 << COM1A1);               // Set OC1A foor FAST PWM
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << CS11) | (1 << CS10);    // Set prescaler to 64 -> 0.04us
  TCCR1B |= (1 << WGM12) | (1 << WGM13);  // turn on Fast PWM
  ICR1 = MAX_COUNTS;                       // 5000 * 0.04us = 20us which is servos pwm period, we canuse ICR1 also for timing.         
}

static inline void init_adc(void){
  ADMUX |= (1 << REFS0);                  // Voltage reference selection for ADC
  ADCSRA |= (1 << ADEN) ;   // Turn on ADC and set prescaler
}

static inline void turn_on_servo(void){
  DDRB |= (1 << PB1);
  PORTB |= (1 << PB0);                     // Turn on LED
}

static inline void turn_off_servo(void){
  DDRB &= ~(1 << PB1);
  PORTB &= ~(1 << PB0);                    // Turn off LED
}

static inline uint16_t get_anal_inp(uint8_t port){  // port can be either 0 or 1
  uint16_t port_result;
  if (port > 0)
    ADMUX |= (1 << MUX0);
  ADCSRA |= (1 << ADSC);                    // start conversion
  loop_until_bit_is_clear(ADCSRA, ADSC);
  port_result = ADC;  
  Serial.print("ADC Result =  ");
  Serial.println(port_result);
  //port_result = (port_result >> 7);         // get only the first 3 bits
  if (port_result < MIN_SERVO){
    port_result = MIN_SERVO;
  }
  if (port_result > MAX_SERVO){
    port_result = MAX_SERVO;
  }
  if (port > 0)
    ADMUX &=~(1 << MUX0);
  return port_result;
}

static inline void move_servo(uint16_t step){
  turn_on_servo();
  OCR1A = step;
  _delay_ms(1500);
  turn_off_servo();
}

int main(void){
  uint16_t servo_step;  
  // Init Ports
  init_io();

  // Init Timers
  init_timer();

  // Init ADC
  init_adc();

  Serial.begin(9600);

  while(1){ 
    servo_step = get_anal_inp(0);
    Serial.print("Servo Step 0 = ");
    Serial.println(servo_step);
    _delay_ms(500);
    move_servo(servo_step);
    servo_step = get_anal_inp(1);
    Serial.print("Servo Step 1 = ");
    Serial.println(servo_step);
    _delay_ms(500);
    move_servo(servo_step);
  }
}
