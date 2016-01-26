/********************************************************* 
 This sketch demonstrates the use of a watchdog timer.
 The watchdog timer causes a processor reset to occur if
 it is allowed to time out. When the sketch are running
 inside the second while loop, the watch dog timer is
 consistently resat to prevent a timeout. When PB0 are 
 pulled high, it breaks put of the while loop and causes 
 the watch dog timer to reset the processor.
 ********************************************************/ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>


uint16_t counter;

int main(void)
{
  DDRB |= 0x01; 		 // Set PB0 as output, ignore the rest
  //DDRB |= _BV(PB0);	 // Alternative method
  //DDRB |= (1 << PB0); // Alternative method

  DDRB &= ~0x02; 		 // Set PB1 as input, ignore the rest
  //DDRB &= _BV(PB1);	 // Alternative method
  //DDRB &= ~(1 << PB1);// Alternative method
  
  PORTB |= 0x02; // Enable pullup on PB1

  
  while((PINB & _BV(PB1)) == 1) // Wait for PB1 to be pulled down
  {
    PORTB ^= 0x01; //Toggle PB0 while waiting
    _delay_ms(100);
  }


  wdt_enable(WDTO_1S); // Enable WDT with 1 second timeout

  while((PINB & _BV(PB1)) == 0) // Wait for PB1 to be pulled high
  {
    wdt_reset(); //Reset WDT while PD0 are pulled low
    
    counter++;

    if(counter >= 50000)
    {
      PORTB ^= 0x01; // Toggle PB0 every 50000th time
      counter = 0;
    }
  }

  
  while(1); // The watchdog will reset the microcontroller after 1 second
}

