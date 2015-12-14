/* A simple test sketch that demonstrates the
  usage of the "pulseImmediate" method and how
  can turn on an LED for ten minutes without
  the use if delay().
  Works great with MightyCore!
*/

#include "Timer.h"

int ledPin = 0;                   // LED is attached to digital pin 0
int tenSeconds = 10 * 1000;       // 10000 ms
long tenMinutes = 10 * 60 * 1000; // 600000 ms

Timer t; // Object of the timer class


void setup()
{ 
  pinMode(ledPin, OUTPUT); // Define ledPin as an output
  
  t.pulseImmediate(ledPin, tenMinutes, HIGH);    // (pin, pause, toggle to) - this method will turn on the LED for ten seconds, and the turn it off forever
  //t.pulseImmediate(ledPin, tenSeconds, HIGH);  // (pin, pause, toggle to) - this method will turn on the LED for ten minutes, and the turn it off forever
  //t.pulse(ledPin, tenSeconds, HIGH);           // (pin, pause, start condition) - the LED will be low for ten seconds, then turn on for ten seconds and then stay low forever
}

void loop()
{
  t.update(); // Updates the timers
  // Run your code here
}

