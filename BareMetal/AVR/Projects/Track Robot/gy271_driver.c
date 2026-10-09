#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

// Addresses
#define GY_W            0x2C    // SLA+W
#define GY_R            0x2D    // SLA+R
#define QMC_CHIPID      0x00
#define QMC_X_LSB       0x01
#define QMC_X_MSB       0x02
#define QMC_Z_LSB       0x03
#define QMC_Z_MSB       0x04
#define QMC_Y_LSB       0x05
#define QMC_Y_MSB       0x06
#define QMC_STAT        0x09
#define QMC_CTRL_REG1   0x0A
#define QMC_CTRL_REG2   0x0B

// Status checks
#define QMC_STAT_READY  0x01
#define QMC_STAT_OVRFL  0x02  // OVFL bit set high when either axis code output exceeds the range of [-30000,30000] LSB and reset to “0” after this bit is read.

// Modes of operations - by default suspended
#define QMC_NORMAL_MODE 0x01
#define QMC_SINGLE_MODE 0x02
#define QMC_CONT_MODE   0x03

// Output data rates  - by default 10HZ
#define QMC_ODR_50HZ    0x04
#define QMC_ODR_100HZ   0x08
#define QMC_ODR_200HZ   0x0C

// Over Sample Ratio - by default 8
#define QMC_OSR1_OVER4  0x10
#define QMC_OSR1_OVER2  0x20
#define QMC_OSR1_OVER1  0x30

// DOWN Sampling Rage - by default 1
#define QMC_OSR2_DOWN2  0x40
#define QMC_OSR2_DOWN4  0x80
#define QMC_OSR2_DOWN8  0xC0

// I2C Functions
void check_bit(void);
uint8_t check_status(uint8_t bit);
void I2C_init(void);
uint8_t I2C_start(void);
uint8_t I2C_send_data_write(uint8_t data);
uint8_t I2C_send_data_read(uint8_t data);
uint8_t I2C_send_ack(void);
uint8_t I2C_send_nack(void);
uint8_t I2C_stop(void);
void inits(void);

// QMC Functions
uint8_t QMC_read_data(uint8_t address);
uint8_t QMC_write_data(uint8_t address, uint8_t value);
uint8_t QMC_read_XYZ(uint8_t address);

// Additional Functions
void print_msg(char msg);

void print_msg(char msg){
  Serial.println(msg);
  return 0;
}

void check_bit(void){
  while (!(TWCR & (1<<TWINT)));
}

uint8_t check_status(uint8_t bit){
  if ((TWSR & 0xF8) != bit){
    return 0;
  }
  else{
    return 1;
  }
}

void I2C_init(void){
  TWSR &=~ ((1 << TWPS1) | (1 << TWPS0));   // Set prescaler to 1
  TWBR = 72;                                // i2c is set to 100khz
  TWCR = (1 << TWEN);                       // Enable i2c
}

// Can be used as a repeated start too
uint8_t I2C_start(void){  
  uint8_t result;
  TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
  check_bit();
  result = check_status(TW_START);
  if (result == 0){
    Serial.println("Could not send start signal!");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_data_write(uint8_t data){
  uint8_t result;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
  result = check_status(TW_MT_SLA_ACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_ACK");
    Serial.flush();
  }
  result = check_status(TW_MT_SLA_NACK);
  if (result == 0){
    Serial.println("Error sending data -> TW_MT_SLA_NACK");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_data_read(uint8_t data){
  uint8_t result;
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
  result = check_status(TW_MR_ARB_LOST);
  if (result == 0){
    Serial.println("Error receiving data -> TW_MR_ARB_LOST");
    Serial.flush();
  }
  result = check_status(TW_MR_SLA_ACK);
  if (result == 0){
    Serial.println("Error receiving data -> TW_MR_SLA_ACK");
    Serial.flush();
  }
  return result;
}

uint8_t I2C_send_ack(void){
  TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA);
  check_bit();
  return TWDR;
}

uint8_t I2C_send_nack(void){
  TWCR=(1<<TWEN) | (1<<TWINT);	
  check_bit();
  return TWDR;		
}

uint8_t I2C_stop(void){
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  while (TWCR & (1 << TWSTO));
}

void inits(void){
  Serial.begin(9600);
  I2C_init();
  Serial.println("Finished Initialising");
  Serial.flush();
}

// Function reads once and sends nack
// Function is not useful for reading XYZ Registers
uint8_t QMC_read_data(uint8_t address){ 
  uint8_t result;
  I2C_start();
  result = I2C_send_data_write(GY_W);
  if (result != 1){
    Serial.println("Error sending SLA+W!");
    
    return 0;
  }
    
  result = I2C_send_data_write(address);
  if (result != 1){
    Serial.println("Error writing address!");
    return 0;
  }

  I2C_start();

  result = I2C_send_data_read();
  if (result != 1){
    Serial.println("Error sending SLA+R!");
    return 0;
  }
  
  result = I2C_send_nack();

  I2C_stop();

  return result;
}

uint8_t QMC_write_data(uint8_t address, uint8_t value){
  uint8_t result;
  I2C_start();
  result = I2C_send_data_write(GY_W);
  if (result != 1){
    Serial.println("Error sending SLA+W!");
    return 0;
  }
    
  result = I2C_send_data_write(address);
  if (result != 1){
    Serial.println("Error writing address!");
    return 0;
  }

  result = I2C_send_data_write(value);
  if (result != 1){
    Serial.println("Error writing value");
    return 0;
  }
  I2C_stop();
  return result;
}

uint8_t QMC_read_XYZ(uint8_t address){
  uint8_t result;
  I2C_start();
  result = I2C_send_data_write(GY_W);
  if (result != 1){
    Serial.println("Error sending SLA+W!");
    
    return 0;
  }
    
  result = I2C_send_data_write(address);
  if (result != 1){
    Serial.println("Error writing address!");
    return 0;
  }

  I2C_start();

  result = I2C_send_data_read();
  if (result != 1){
    Serial.println("Error sending SLA+R!");
    return 0;
  }
  
  result = I2C_send_nack();

  I2C_stop();
}


int main(void){
  uint8_t x_msb, x_lsb, y_msb, y_lsb, z_msb, z_lsb, gy_status;
  uint8_t i2c_status;
  _delay_ms(1000);
  inits();
  while(1){
   
  }
}
