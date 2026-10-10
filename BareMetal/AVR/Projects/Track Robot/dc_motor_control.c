#include <avr/io.h>
#include <util/delay.h>

#define LED         PD3
#define MC_IN1      PD4
#define MC_IN2      PD5
#define MC_IN3      PD6
#define MC_IN4      PD7 
#define MC_SPD_IN1  PB1
#define MC_SPD_IN2  PB2
#define MAX_ON      10666
#define MIN_ON      3300
#define TICK_SEC    0.0000000625

#define MOVE_FWD  ((1 << MC_IN2) | (1 << MC_IN4)) // Must be set to high and MOVE_BCK TO LOW
#define MOVE_BCK  ((1 << MC_IN1) | (1 << MC_IN3)) // Must be set to HIGH and MOVE_FWD to low

void init_pwm(void);
void init_ports(void);
void set_speed(uint16_t speed);
void current_duty_cycle(uint16_t speed);

void init_pwm(void){
  TCCR1B |= (1 << CS10);                   // Setting Prescaler to 256
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1); // Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM 
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  ICR1 = 10666;                            // This is the top value
}

void init_ports(void){
  DDRD |= (1 << LED) | (1 << MC_IN1) | (1 << MC_IN2) | (1 << MC_IN3) | (1 << MC_IN4);
  PORTD |= (1 << LED); 
  DDRB |= (1 << MC_SPD_IN1) | (1 << MC_SPD_IN2);
}

void set_speed(uint16_t speed){
  OCR1A = speed;
  OCR1B = speed;
}

void current_duty_cycle(uint16_t speed){
  float current_hz = 1 / (speed * TICK_SEC);
  Serial.print("Frequency = ");
  Serial.println(current_hz);
}

int main(void){
  Serial.begin(115200);
  init_ports();
  init_pwm();
  uint16_t current_speed = MIN_ON;
  while(1){
    set_speed(current_speed);
    Serial.print("Current Speed = ");
    Serial.println(current_speed);
    current_duty_cycle(current_speed);
    PORTD |= (1 << MC_IN2) | (1 << MC_IN4) | (1 << LED);
    _delay_ms(1000);
    PORTD &=~ ((1 << MC_IN2) | (1 << MC_IN4) | (1 << LED));
    _delay_ms(1000);
    current_speed += 100;
    if (current_speed > MAX_ON)
      current_speed = MIN_ON;

  }
}
