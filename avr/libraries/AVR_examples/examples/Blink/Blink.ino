/***************************************************
 Simple AVR sketch to blink an LED (or similar)
 connected to PB0 (Arduino pin D0)
 Note that the compiled sketch is significally
 smaller that the original Arduino blink sketch.
 A detailed explaination about debugging, port and
 pin definitions can be watched here:
 https://www.youtube.com/watch?v=plJf0r7IcWc
***************************************************/ 


#include <avr/io.h>
#include <util/delay.h>


int main(void)
{       

  /************************************************ 
   A few different ways to set a pin as output and 
   ignore the rest of the pins. Pick your favorite!
  *************************************************/
  DDRB |= 0x01; 		// XXXXXXXX | 00000001 = XXXXXXX1
  //DDRB |= _BV(PB0);	 // Set PB0 as output, ignore the rest
  //DDRB |= (1 << PB0); // Shift the number '1' left 'PB0' times (PB0 = 1)



  /************************************************ 
   A few different ways to set a pin as input and 
   ignore the rest of the pins.
  *************************************************/
  //DDRB &= ~0x01; //00000001 -> 11111110 & XXXXXXXX = XXXXXXX0
  //DDRB &= ~_BV(PB0); 
  //DDRB &= ~(1 << PB0);
    
  
  // Infinite loop
  while(1)
  {
    /*********************************************** 
     A few different ways to set a pin high and 
     ignore the rest of the pins. 
    ************************************************/
    PORTB |= 0x01;  // XXXXXXXX | 00000001 = XXXXXXX1
    //PORTB |= _BV(PB0);
    //PORTB |= (1 << PB0);
	  //SetPinHigh(&PORTB, 0); 
    _delay_ms(1000);
    
    
    /*********************************************** 
     A few different ways to set a pin low and 
     ignore the rest of the pins.
    ************************************************/
    PORTB &= ~0x01;  // 00000001 -> 11111110 & XXXXXXXX = XXXXXXX0
    //PORTB &= ~_BV(PB0);
    //PORTB &= ~(1 << PB0);
    //SetPinLow(&PORTB, 0);
    _delay_ms(1000);
  }
    
  return 0;
}


// Method to set a pin HIGH
void SetPinHigh(volatile byte *port, byte pin)
{
  *port |= (1 << pin); // The number '1' are shifted left 'pin' times
}

// Method to set pin LOW
void SetPinLow(volatile byte *port, byte pin)
{
  *port &= ~(1 << pin); // The number '1' are shifted left 'pin' times
}
