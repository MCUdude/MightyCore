/* ARDUINO TIMER LIBRARY 
   https://github.com/JChristensen/Timer/tree/v2.1
   
   This is a simple test sketch that demonstrates the
   oscillate, pulse and pulseImmediate methods.
   Works great with MightyCore!
*/

#include "Timer.h"

int ledPin = 0;   // LED is attached to digital pin 0
int pause = 1000; // 1000 ms

Timer t; // Object of the timer class


void setup() {

  pinMode(ledPin, OUTPUT); // Define ledPin as an output

  
/* This will oscillate ledPin forever
   with start condition LOW */
  t.oscillate(ledPin, pause, LOW); // (pin, pause, start condition)


/* The LED will blink five times
   with start condition LOW */  
  //t.oscillate(ledPin, pause, LOW, 5); // (pin, pause, start condition, repeat count)


/* This will send a pulse with start condition LOW. 
   The LED will be low for 1000 ms, then high for
   1000 ms and then low forever  */
  //t.pulse(ledPin, pause, LOW); // (pin, pause, start condition) 


/* This method will pulse immediately and not return
   to the start condition (this example will set the 
   LED LOW for 1000 ms, then stay HIGH forever) */
  //t.pulseImmediate(ledPin, pause, LOW); // (pin, pause, toggle to)

}

void loop() 
{
  t.update(); // Updates the timer
}
