
/* Simple AVR sketch to blink an LED (or similar)
   connected to PB0 (Arduino pin D0)
   Note that the compiled sketch is significally
   smaller that the original Arduino blink sketch.
   A detailed explaination about debugging, port and
   pin definitions can be watched here:
   https://www.youtube.com/watch?v=plJf0r7IcWc
 */


#include <avr/io.h>
#include <util/delay.h>



int main(void)
{       
  /* different ways to define ports: */
  
  DDRB |= 0x01; //Define PB0 as output, ignore the rest
  //XXXXXXXX | 00000001 = XXXXXXX1

  //DDRB = 0x01; //Define PB0 as output, set the rest to input

  //DDRB &= ~0x01; //Define PB0 as input, ignore the rest
  // 00000001 -> 11111110 & XXXXXXXX = XXXXXXX0
  
  
  
  // Infinite loop
  while(1)
  {
    //SetPinHigh(&PORTB, 0); 
    PORTB |= 0x01;      // XXXXXXXX | 00000001 = XXXXXXX1
    _delay_ms(1000);
    
    //SetPinLow(&PORTB, 0);
    PORTB &= ~0x01;      // 00000001 -> 11111110 & XXXXXXXX = XXXXXXX0
    _delay_ms(1000);
  }
    
  return 0;
}


// Method to set a pin HIGH
void SetPinHigh(volatile byte *port, byte pin)
  *port |= (1 << pin); // 0b00000001 where the number '1' are shifted left 'pin' times

// Method to set pin LOW
void SetPinLow(volatile byte *port, byte pin)
{
  *port &= ~(1 << pin); // 0b00000001 where the number '1' are shifted left 'pin' times
}

