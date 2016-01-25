/**************************************************
 This simple sketch shows the power and simplicity
 by manipulating the ports on the AVR. The code
 reads all the pins on port B and output the state
 on port A.
**************************************************/

#include <avr/io.h>


int main(void)
{
  DDRA = 0xFF; // Set all pins on port A as output
  DDRB = 0x00; // Set all pins on port B as input
  
  while(1)
  {
    PORTA = PINB; // Read the state of port B and write the state to port A
  }
  
  return 0;
}  
