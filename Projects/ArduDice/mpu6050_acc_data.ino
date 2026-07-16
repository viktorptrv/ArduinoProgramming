#include <Wire.h>

#define MPU_ADDR 0x68
#define ACC_RANGE 8   // depends on how many G's its configured, since this one is +-4G => 8

uint16_t gyro_output[3];
uint16_t acc_output[3];

uint16_t gyro_offset[3];
uint16_t acc_offset[3];

uint16_t gyro_temp_value[3][1000];
uint16_t acc_temp_value[3][1000];

uint16_t gyro_x, gyro_y, gyro_z;
uint16_t accel_x, accel_y, accel_z, temperature;

const double acc_value_change = 0.12207217517;    // ACC_RANGE * 1000 / 65535

char tmp_str[7];

void setup() {
  // put your setup code here, to run once:
  Wire.begin(MPU_ADDR);                    // Set address of I2C MPU
  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  Serial.begin(9600);
  //setup_gyro();
  //setup_acc();
}

void loop() {
  // put your main code here, to run repeatedly:
  read_data();
  Serial.print("Acceleration on X axis -> ");
  Serial.println(calculate_g(accel_x));
  Serial.print("Acceleration on Y axis -> ");
  Serial.println(calculate_g(accel_y));
  Serial.print("Acceleration on Z axis -> ");
  Serial.println(calculate_g(accel_z));
  delay(100);
}

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
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

  /* Just for DEBUG
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accel_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accel_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accel_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();*/
  delay(500);
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

double calculate_g(int sens_value){
  double result = ((double)sens_value * acc_value_change) / 1000;
  Serial.print("Into Calculate_g, value of sensor:");
  Serial.println(sens_value);
  Serial.print("Value change: ");
  Serial.println(acc_value_change);
  Serial.print("Result: ");
  Serial.println(result);
  delay(2000);
  return result;
}
