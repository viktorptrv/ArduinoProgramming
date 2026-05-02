#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FastLED.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define LED_PIN 7
#define NUM_LEDS 8

CRGB leds[NUM_LEDS];

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  FastLED.addLeds<WS2812,LED_PIN, GRB>(leds, NUM_LEDS);
  delay(10);
}


void loop() {
  Serial.println("Starting");
   // Drive each servo one at a time using setPWM()
  for (int servo = 0, led = 0; servo < 16; servo++){
    //if (servo % 2 == 0){
    //  led++;
    //}
    //Serial.println("Turn ON LED");
    //leds[led] = CRGB(0, 0, 255);
    //FastLED.show();
    for(int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
      pwm.setPWM(servo, 0, pulselen);
    }
    Serial.print("Servo - ");
    Serial.println(servo);
  }

  Serial.println("Servo are to max");
  delay(1000);

  for (int servo = 15,  led = 0; servo > -1; servo--){
    /*
    if (servo % 2 == 0){
      led++;
    }
    leds[led] = CRGB(0, 0, 255);
    FastLED.show();
    */
    for(int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--){
      pwm.setPWM(servo, 0, pulselen);
    }

    Serial.print("Servo - ");
    Serial.println(servo);
  }

  Serial.println("Servo are to min");
  delay(1000);

  int pulseLength = map(45, 0, 180, SERVOMIN, SERVOMAX);
  for(int servo = 0, led = 0; servo < 16; servo++){
    pwm.setPWM(servo, 0, pulseLength);
    Serial.print("Servo - ");
    Serial.println(servo);
  }

  delay(1000);

  pulseLength = map(60, 0, 180, SERVOMIN, SERVOMAX);
  for(int servo = 0, led = 0; servo < 16; servo++){
    pwm.setPWM(servo, 0, pulseLength);
    Serial.print("Servo - ");
    Serial.println(servo);
  }

  delay(1000);

  pulseLength = map(90, 0, 180, SERVOMIN, SERVOMAX);
  for(int servo = 0, led = 0; servo < 16; servo++){
    pwm.setPWM(servo, 0, pulseLength);
    Serial.print("Servo - ");
    Serial.println(servo);
  }

  delay(1000);

  pulseLength = map(120, 0, 180, SERVOMIN, SERVOMAX);
  for(int servo = 0, led = 0; servo < 16; servo++){
    pwm.setPWM(servo, 0, pulseLength);
    Serial.print("Servo - ");
    Serial.println(servo);
  }

  for (int i = 0; i < 10; i++){
      for(int servo = 0, led = 0; servo < 16; servo++){
        if (servo % 2 == 0){
          pulseLength = map(60, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servo, 0, pulseLength);
        }
        else{
          pulseLength = map(120, 0, 180, SERVOMIN, SERVOMAX);
          pwm.setPWM(servo, 0, pulseLength);
        }
      }

    delay(1000);

    for(int servo = 0, led = 0; servo < 16; servo++){
      if (servo % 2 == 0){
        pulseLength = map(0, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servo, 0, pulseLength);
      }
      else{
        pulseLength = map(0, 0, 180, SERVOMIN, SERVOMAX);
        pwm.setPWM(servo, 0, pulseLength);
      }
    }

    delay(1000);
  }
  

  Serial.println ("Ending");
  delay(1000);
  
}
