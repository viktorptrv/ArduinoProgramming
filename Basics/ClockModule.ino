#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();
  if (!rtc.isrunning()){
    Serial.println("RTC is NOT Running!");
    rtc.adjust(DateTime(2025, 9,9,21,28,00));
  }
}

void loop(){
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.println();
}
