Dancing Servos Project

This project creates the illusion of synchronized “dancing” using 16 servo motors controlled through a PCA9685 16-channel servo driver. An RGB LED module (WS2812B, 8 LEDs) is integrated to match the motion with dynamic lighting effects.

The core concept is straightforward: all servos are connected to the PCA9685 driver, which is controlled via I2C from an Arduino. The system uses the Adafruit PWM Servo Driver library (Adafruit_PWMServoDriver.h) alongside the Wire library for communication.

The RGB LEDs are controlled separately using the FastLED library, allowing precise timing and color synchronization with the servo movements.

The PCA9685 requires 5V from the Arduino for logic, but the servos must be powered by an external 5V supply to avoid overloading the board. The LED module also requires its own external power source, as each RGB LED can draw up to 60mA at full brightness.

Required Components:

3D printer + filament (PLA+ recommended)

8 × M2.5 × 8 mm bolts

16 × SG90 servo motors

Arduino Uno

PCA9685 16-channel servo driver

You can find the github repo here: https://github.com/viktorptrv/ArduinoProgramming/tree/main/Projects/DancingServos

 Tutorials used:
 https://learn.adafruit.com/16-channel-pwm-servo-driver/overview -> Servo driver
 https://howtomechatronics.com/tutorials/arduino/how-to-control-ws2812b-individually-addressable-leds-using-arduino/ -> LEDS

<img width="960" height="1280" alt="photo_2026-05-02_14-14-31" src="https://github.com/user-attachments/assets/06bf3c53-fb5b-43af-a180-fe69d5a545bc" />
<img width="1280" height="960" alt="photo_2026-05-02_14-14-23" src="https://github.com/user-attachments/assets/b1e361a3-129c-40ad-87ff-5599b8bbc71a" />
<img width="960" height="1280" alt="photo_2026-05-02_14-14-26" src="https://github.com/user-attachments/assets/5f892933-29a5-46b2-bd24-5e8a37932469" />
<img width="1615" height="1964" alt="Untitled Sketch 2_bb" src="https://github.com/user-attachments/assets/43d50fe8-ed0e-48e0-b196-d4eb556b4f86" />
