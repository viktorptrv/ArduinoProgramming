#include <Wire.h>

#define COMPASS_ADDR 0x1E

bool haveHMC5883L = false;

bool detectCompassModule(void);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("GY-271 TEST");
  Wire.begin();

  // Lower I2C Clock
  //TWBR = 78;
  //TWSR |= _BV (TWPS0); // Change prescaler
}

void loop() {
  // put your main code here, to run repeatedly:
  bool detect = detectCompassModule();
  if (!haveHMC5883L){
    if (detect){
      haveHMC5883L = true;
      Serial.println("We have HMC5883L, moving on");

      // put the HMC5883 IC into the correct operating mode;
      Wire.beginTransmission(COMPASS_ADDR);
      Wire.write(0x02); // Select mode register
      Wire.write(0x00); // cont measurement mode
      Wire.endTransmission();
    }
    else{
      Serial.println("No HMC5883L Detected!");
      delay(2000);
    }
  }
  else{
    if (!detect){
      haveHMC5883L = false;
      Serial.println("Lost connection to HMC");
      delay(2000);
    }
  }

  int x, y, z;
  Wire.beginTransmission(COMPASS_ADDR);
  Wire.write(0x03);
  Wire.endTransmission();
  Wire.requestFrom(COMPASS_ADDR, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.println(z);
  delay(250);
}

bool detectCompassModule(void){
  Wire.beginTransmission(COMPASS_ADDR);
  Wire.write(10);
  Wire.endTransmission();
  Wire.requestFrom(COMPASS_ADDR, 3);
  if (3 == Wire.available()){
    char a = Wire.read();
    char b = Wire.read();
    char c = Wire.read();
    
    if (a == 'H' && b == '4' && c == '3')
      return true;
  }

  return false;
}
