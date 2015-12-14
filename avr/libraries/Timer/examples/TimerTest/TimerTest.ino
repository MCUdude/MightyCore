/* A simple test sketch that demonstrates the
  oscillate, pulse and pulseImmediate methods.
  Works great with MightyCore!
*/

#include "Timer.h"

int ledPin = 0;   // LED is attached to digital pin 0
int pause = 1000; // 1000 ms

Timer t; // Object of the timer class


void setup() {

  pinMode(ledPin, OUTPUT); // Define ledPin as an output
  /** Uncomment to test different timer methods **/
  //t.oscillate(ledPin, pause, LOW);      // (pin, pause, start condition) - this will run forever
  //t.oscillate(ledPin, pause, LOW, 5);   // (pin, pause, start condition, repeat count) - the LED will blink five times
  //t.pulse(ledPin, pause, LOW);          // (pin, pause, start condition) - this will send one pulse with start condition LOW. The LED will be low for 1000 ms, then high for 1000 ms and then low forever
  //t.pulseImmediate(ledPin, pause, LOW); // (pin, pause, toggle to) - this method will pulse immediately and not return to the start condition (this example will leave the LED high after 1000 ms)

}

void loop() {
 t.update(); // Updates the timers
 // Run your code here

}
