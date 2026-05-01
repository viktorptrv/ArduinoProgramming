Just a simple serial communication using the clock to synchronize the sending and receiving of bits.
Main idea: 
  We use two pins one labeled DATA and one labeled CLOCK. Through the data pin we send the bits (0 - LOW signal, 1 HIGH signal) and 
  we use the clock to synchronize the transceiver and the receiver. 
  - Transceiver - read one bit from the whole byte (starting from the left most digit) and configure the output accordingly. if the left most digit bit is 0
  digital output will be set to 0, and vice versa for bit with value of 1. Then you start the clock pulse which will take just 1 millisecond. 
  after that increment the value with 1.
  - Receiver - first wait till the clock pulse comes, for that reason input are PULLUP to stop floating inputs. When the pulse comes, read the data
  from the data pin and add it to the byte. Then wait for the clock pulse to stop. Increment for the rest of the 7 bits.
