#include <Wire.h>

#define MPU_ADDR 0x70

uint16_t gyro_output[3];
uint16_t acc_output[3];

uint16_t gyro_offset[3];
uint16_t acc_offset[3];

uint16_t gyro_temp_value[3][1000];
uint16_t acc_temp_value[3][1000];

uint16_t gyro_x, gyro_y, gyro_z;
uint16_t accel_x, accel_y, accel_z, temperature;



void setup() {
  // put your setup code here, to run once:
  Wire.begin(MPU_ADDR);                    // Set address of I2C MPU
  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  Serial.begin(9600);
  setup_gyro();
  setup_acc();
}

void loop() {
  // put your main code here, to run repeatedly:
  read_data();
  delay(100);
}

void read_data(void){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accel_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accel_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accel_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
}

void calibrate_offsets(void){
  long long int sum_gyro_x, sum_gyro_y, sum_gyro_z;
  long long int sum_accel_x, sum_accel_y, sum_accel_z;

  for(int i = 0; i < 1000; i++){
    sum_gyro_x += gyro_temp_value[0][i];
  }
  gyro_offset[0] = sum_gyro_x / 1000;

  for(int i = 0; i < 1000; i++){
    sum_gyro_y += gyro_temp_value[1][i];
  }
  gyro_offset[1] = sum_gyro_y / 1000;

  for(int i = 0; i < 1000; i++){
    sum_gyro_z += gyro_temp_value[2][i];
  }
  gyro_offset[2] = sum_gyro_z / 1000;

  for (int i = 0; i < 1000; i++){
    sum_accel_x += acc_temp_value[0][i];
  }
  acc_offset[0] = sum_accel_x / 1000;

  for (int i = 0; i < 1000; i++){
    sum_accel_y += acc_temp_value[1][i];
  }
  acc_offset[1] = sum_accel_y / 1000;

  for (int i = 0; i < 1000; i++){
    sum_accel_z += acc_temp_value[2][i];
  }
  acc_offset[2] = sum_accel_z / 1000;
}

void setup_gyro(void){
  // setup gyro full scale range to 250 degrees per second
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1B);
  Wire.write(0x00);     // LSB is 131 
  Wire.endTransmission();

  // Setup gyro digital low pass filtr
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1A);
  Wire.write(0x03);
  Wire.endTransmission();
}

void setup_acc(void){
  // setup accelerometer full scale range
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x1C);
  Wire.write(0x01);
  Wire.endTransmission();
}
