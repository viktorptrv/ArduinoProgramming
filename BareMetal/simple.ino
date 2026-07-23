// Bare metal programming


void setup() {
  // put your setup code here, to run once:
  DDRB = 32;  //B00100000 set PortB Bit 5 as an output
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB |= 32;  // LED on PIN 13, confuguring if its high or low
  delay(2000);
  PORTB &= 0;
  delay(1000);
}
