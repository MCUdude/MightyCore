/* ARDUINO TIMER LIBRARY 
   https://github.com/JChristensen/Timer/tree/v2.1
    
   A simple sketch that demonstrates the
   "every" method. This method let you run code
   every second, every millisecond or any other
   specified delay. It's like multitasking!
   Works great with MightyCore!
*/

#include "Timer.h"

int ledPin = 0;     // LED is attached to digital pin 0
int pause1 = 100;   // 100 ms
int pause2 = 1000;  // 1000 ms

Timer t; // Object of the timer class


void setup() {
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Define ledPin as an output

/* run the "toggle" method every 100 ms and
   pass the value '0' to the "toggle" method  */
  t.every(pause1, toggle, (void*)0); // (pause, method, pass value)

/* run the "takeReading" method every 1000 ms and
   pass the value '1' to the "takeReading" method  */
  t.every(pause2, takeReading, (void*)1); // (pause, method)
}

void loop()
{
  t.update(); // Updates the timer
}

void takeReading(void* context)
{
  int val = (int)context; //convert the passed value to an integer
  Serial.print("Value passed to the takeReading method: ");
  Serial.println(val);
  Serial.print("AnalogRead value: ");
  Serial.println(analogRead(0));
}

void toggle(void* context) {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the ledPin
}
