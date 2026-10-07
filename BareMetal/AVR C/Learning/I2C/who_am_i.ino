#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>

void initI2C(void);
void initI2C(void){
  TWSR &=~ (1 << TWPS1) | (1 << TWPS0);
  TWBR = 72;
  TWCR = (1 << TWEN);
}

void check_bit(void);
void check_bit(void){
  while (!(TWCR & (1<<TWINT)));
}

void I2C_start(void);
void I2C_start(void){
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1 << TWEN);
  check_bit(); 
  //TWCR &=~ (1 << TWSTA);
}

void IC2_send_data(uint8_t data);
void IC2_send_data(uint8_t data){
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  check_bit();
}

int I2C_check_status(uint8_t status_code);
int I2C_check_status(uint8_t status_code){
  if ((TWSR & 0xF8) != status_code){
    return 0;
  }
  else{
    return 1;
  }
}

void I2C_stop(void);
void I2C_stop(void){
  TWCR = (1<<TWINT) | (1<<TWEN)| (1<<TWSTO); 
}

int main(void){
  uint8_t address = 1;
  uint8_t status;
  Serial.begin(9600);
  initI2C();
  
  _delay_ms(1000);
  while(1){
    // First send start bit
    I2C_start();

    // Check if start bit was successful
    status = I2C_check_status(TW_START);
    if(status == 1){
      Serial.println("Successfull start");
    }
    else{
      Serial.println("Could not send start");
    }

    // Then send SLA+W
    IC2_send_data(address << 1);

    // Check the status of that data;
    status = I2C_check_status(TW_MT_SLA_ACK);
    if(status == 1){
      Serial.print("Address found!: ");
      //Serial.println(address << 1);
      I2C_stop();
      return 0;
    }

    address++;
    I2C_stop();
    
  }

  return 0;
}
