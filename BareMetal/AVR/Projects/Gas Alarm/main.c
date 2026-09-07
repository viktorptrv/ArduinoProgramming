#include <avr/io.h>
#include <util/delay.h>
#include <math.h>

#define LED_RED     PD5      // Pin D5
#define LED_YELLOW  PD6      // Pin D6
#define LED_GREEN   PD7      // Pin D7
#define MOS         PD4      // Pin D4
#define BUZZ        PB1      // Pin D9
#define RL_VALUE 10.0  // Load resistance in kOhms
#define CALIBRATION_SAMPLES 50

const float CoefA = 658.71;         // Propane Coeff A
const float CoefB = -2.168;         // Propane Coeff B
volatile double roAvg;

static inline void setup_pins(void);
static inline void setup_adc(void);
static inline void setup_timer(void);
static inline void calibrating_mq(void);
static inline int read_analog(void);
static inline float calculateRo(float voltage);
static inline float calculatePPM(float rs);
static inline void turn_all_led(uint8_t times);
static inline void Turn_ON_LED(uint8_t led);
static inline void Turn_OFF_LED(uint8_t led);
static inline float calculateRs(int rawValue);

static inline float calculateRs(int rawValue) {
  float voltage = rawValue * (5.0 / 1023.0);
  return ((5.0 * RL_VALUE) / voltage) - RL_VALUE;
}

static inline int read_analog(void){
  ADCSRA |= (1 << ADSC);
  loop_until_bit_is_clear(ADCSRA, ADSC);
  return ADC;
}

static inline void setup_pins(void){
  DDRD |= (1 << LED_RED) | (1 << LED_YELLOW) | (1 << LED_GREEN) | (1 << MOS);
  DDRB |= (1 << BUZZ);
}

static inline void setup_adc(void){
  ADMUX |= (1 << REFS0);  
  ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);     // Reduce clock to 125k
}

static inline void setup_timer(void){

}

static inline void Turn_ON_LED(uint8_t led){
  PORTD |= (1 << led);
}

static inline void Turn_OFF_LED(uint8_t led){
  PORTD &= ~(1 << led);
}

static inline void turn_all_led(uint8_t times){
  for (uint8_t i = 0; i < times; i++){
    Turn_ON_LED(LED_GREEN);
    Turn_ON_LED(LED_YELLOW);
    Turn_ON_LED(LED_RED);
    _delay_ms(100);
    Turn_OFF_LED(LED_GREEN);
    Turn_OFF_LED(LED_YELLOW);
    Turn_OFF_LED(LED_RED);
    _delay_ms(100);
  }
}

static inline float calculatePPM(float rs){
  Serial.print("calculatePPM rs = ");
  Serial.println(rs, 3);
  Serial.print("roAvg = ");
  Serial.println(roAvg);
  float result = CoefA * pow((rs / roAvg), CoefB);
  Serial.print("calculatePPM result = ");
  Serial.println(result, 3);
  return result;
}

static inline float calculateRo(float voltage){
  Serial.print("calculateRo voltage = ");
  Serial.println(voltage);
  float rs = ((5.0 * RL_VALUE) / voltage) - RL_VALUE;
  Serial.print("calculateRo rs = ");
  Serial.println(rs);
  float ro = rs / 9.83; // Clean air factor for MQ-2
  Serial.print("calculateRo ro = ");
  Serial.println(ro);
  return ro;
}

static inline void calibrating_mq(void){
  double roSum = 0;
  for(int i = 0; i < CALIBRATION_SAMPLES; i++){
    int raw = read_analog();
    Serial.print("raw =");
    Serial.println(raw);
    float voltage = raw * (5.0 / 1023.0);
    Serial.print("voltage =");
    Serial.println(voltage);
    roSum += calculateRo(voltage);
    Serial.print("roSum =");
    Serial.println(roSum);
    _delay_ms(100);
  }
  roAvg = roSum / CALIBRATION_SAMPLES;
 // Serial.print("Calibration complete. Ro = ");
  //Serial.print(roAvg);
  //Serial.println("kOhms");
  Serial.print(roAvg, 5);
  turn_all_led(4);
}

int main(void){
  int raw_adc_result;
  float adc_result;
  init();
  Serial.begin(9600);
  setup_pins();
  setup_adc();
  PORTD |= (1 << MOS);
  setup_timer();
  calibrating_mq();
  

  while(1){
    raw_adc_result = read_analog();
    adc_result = calculateRs(raw_adc_result);
    Serial.print("FLOAT RAW_ADC_RESULT = ");
    Serial.println(raw_adc_result);
    adc_result = calculatePPM(adc_result);
    Serial.print("ADC -> ");
    Serial.println(adc_result);

  }
}
