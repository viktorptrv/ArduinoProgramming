Dancing servos:
- Using a PCA9685 16-Channel Servo Driver to control simultaneously 16 servos and make the illusion of them dancing.
- Also a RGB Led module is used to synchronize with them (WS2818B 8 LEDS)

 Whole idea is basic - connect all of the servos to the PCA9685 servo driver and use I2C to control them. For this Reason the library By Adafruit (#include <Adafruit_PWMServoDriver.h>)
 has been used with combination of wire library.

 RGB Leds are being controlled by FastLED.h library.

 PCA9685 needs 5V (coming from the arduino) to power the microcontroller and 5V (coming from external power supply) to actually power the servos. You need an external power supply
 for the LEDS too, because every RGB LED consumes 60mA when its at full brightness.

<img width="960" height="1280" alt="photo_2026-05-02_14-14-31" src="https://github.com/user-attachments/assets/06bf3c53-fb5b-43af-a180-fe69d5a545bc" />
<img width="1280" height="960" alt="photo_2026-05-02_14-14-23" src="https://github.com/user-attachments/assets/b1e361a3-129c-40ad-87ff-5599b8bbc71a" />
<img width="960" height="1280" alt="photo_2026-05-02_14-14-26" src="https://github.com/user-attachments/assets/5f892933-29a5-46b2-bd24-5e8a37932469" />
