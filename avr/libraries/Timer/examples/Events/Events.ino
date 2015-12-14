#include "Timer.h"

int ledPin = 0;     // LED is attached to digital pin 0
int pause1 = 1000;  // 1000 ms
int pause2 = 2000;  // 2000 ms
int pause3 = 10000; // 10000 ms
int pause4 = 500;   // 500 ms

int ledEvent = 0;   // Timer ID
int tickEvent = 0;  // Timer ID
int afterEvent = 0; // Timer ID

Timer t; // Object of the timer class


void setup() {
  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // Define ledPin as an output
  
  tickEvent = t.every(pause1, doSomething, (void*)1); // Run the doSomething method every 1000th millisecond, and store the timer ID to tickEvent. Send the value '1' as an argument to the doSomething method
  Serial.print("1 second tick started. ID = ");
  Serial.println(tickEvent); // Prints the timer ID
  
  ledEvent = t.oscillate(ledPin, pause2, HIGH); // Let ledPin toggle every 2000th millisecond with start condition HIGH and store the timer ID to ledEvent
  Serial.print("LED event started. ID = ");
  Serial.println(ledEvent); // Prints the timer ID
  
  afterEvent = t.after(pause3, doAfter, (void*)10); // Run the doAfter method once after 10000 milliseconds and srore the timer ID to afterEvent. Send the value '10' as an argument to the doAfter method
  Serial.print("After event started. ID = ");
  Serial.println(afterEvent); // Prints the timer ID 
  
}

void loop() {
  t.update();
  
}

void doSomething(void* context) {
  int time = (int)context; // the number '1' was passed to this method, and are stored in 'context'
  Serial.print(time);
  Serial.print(" second tick: millis() = ");
  Serial.println(millis());
}


void doAfter(void* context) {
  int time = (int)context; // the number '10' was passed to this method, and are stored in 'context'
  Serial.print("Stopping the LED event after ");
  Serial.print(time);
  Serial.println(" seconds.");
  t.stop(ledEvent);                     // Stops the ledEvent
  t.oscillate(ledPin, pause4, LOW, 5);  // (pin, pause, start condition, number of oscillations) - oscillates the ledPin 5 times with start condition LOW
}
