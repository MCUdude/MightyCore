Arduino Timer Library
Readme file for version 2.1  
https://github.com/JChristensen/Timer/tree/v2.1

This library was originally developed by Dr. Simon Monk to avoid problems that arise when you start trying to do much inside the loop() function.  It can change pin values or run a callback function.  See Dr. Monk's original page http://www.doctormonk.com/2012/01/arduino-timer-library.html.

The library does not interfere with the built-in timers, it just uses millis() in a basic type of scheduler to decide when something needs doing.


EXAMPLES

The Arduino delay() function is both a blessing and a curse.  It's great for showing beginners how to make an LED flash.  But as soon as you get more complex and start slowing down your loop() function you will run into problems.

A classic example is turning a relay on for 10 minutes.  The delay() way looks like this:


int pin = 13;

void setup()
{
    pinMode(13, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(10 * 60 * 1000);
    digitalWrite(pin, LOW);
}

void loop()
{
}


The disadvantage of the delay() approach is that nothing else can go on while the delay() is happening.  You cannot update a display, or check for key presses for example.

The Timer library version looks like this:


#include "Timer.h"

Timer t;
int pin = 13;

void setup()
{
    pinMode(pin, OUTPUT);
    t.pulse(pin, 10 * 60 * 1000, HIGH); // 10 minutes  
}

void loop()
{
    t.update();
}


The pulse() method takes arguments of a pin to change, the period to change it for and its initial state.

The call to t.update() takes a matter of microseconds to run, and when the appropriate period of time has passed, it will change the state of the pin.

Let's look at another example that uses two timer events.  One to flash an LED and another that reads analog input 0 and displays its value on the Serial Monitor.


#include "Timer.h"

Timer t;
int pin = 13;

void setup()
{
    Serial.begin(9600);
    pinMode(pin, OUTPUT);
    t.oscillate(pin, 100, LOW);
    t.every(1000, takeReading, (void*)0);
}

void loop()
{
    t.update();
}

void takeReading(void *context)
{
    Serial.println(analogRead(0));
}


The first thing to notice is that we are using a callback function called takeReading().  We connect it to the Timer using the every() method, which in this case, will call the function every second.

We have also attached another event to the timer using the method oscillate(). This will cause the LED to toggle state every 100 milliseconds.

Each of the events has an integer ID associated with it, so that you can stop an event, as we do in the example below, which will write to the serial monitor every 2 seconds, flash the LED and after 5 seconds, stop the LED flashing fast, and flash it 5 times slowly.


#include "Timer.h"

Timer t;
int ledEvent;

void setup()
{
    Serial.begin(9600);
    int tickEvent = t.every(2000, doSomething, (void*)0);
    Serial.print("2 second tick started id=");
    Serial.println(tickEvent);

    pinMode(13, OUTPUT);
    ledEvent = t.oscillate(13, 50, HIGH);
    Serial.print("LED event started id=");
    Serial.println(ledEvent);

    int afterEvent = t.after(10000, doAfter, (void*)0);
    Serial.print("After event started id=");
    Serial.println(afterEvent); 
}

void loop()
{
    t.update();
}

void doSomething(void *context)
{
    Serial.print("2 second tick: millis()=");
    Serial.println(millis());
}

void doAfter(void *context)
{
    Serial.println("stop the led event");
    t.stop(ledEvent);
    t.oscillate(13, 500, HIGH, 5);
}


You can attach up to 10 events to a timer.

Note that the callback functions have a "context" parameter.  The context value is specified when the event is created and it will be sent to callback function when the timer fires. The context is a void pointer, so it can be cast to any other data type.  Its use is optional, if you don't need it, just code (void*)0 as in the above examples, but be sure that the callback function definitions have it in their argument list, i.e. (void *context).



REFERENCE


every();
Description:
	Runs the callback function every period milliseconds. Optionally stops after repeatCount times.
Syntax:
	t.every(period, callback, context);  
	t.every(period, callback, repeatCount, context);
Parameters:
	period: How often to run the callback function, in milliseconds (unsigned long) 
	callback: The name of the callback function which is called when the timer event fires (function pointer)* 
	repeatCount: The number of times to run the callback function (int, optional)
	context: Context value to be passed to the callback function (void pointer)
Returns:
	The ID of the Timer event (int8_t or char)


after();
Description:
	Run the callback function once, after period milliseconds.
Syntax:
	t.after(period, callback, context);
Parameters:
	period: How long to wait before running the callback function, in milliseconds (unsigned long) 
	callback: The name of the callback function which is called when the timer event fires (function pointer)
	context: Context value to be passed to the callback function (void pointer) 
Returns:
	The ID of the Timer event (int8_t or char)


oscillate();
Description:
	Toggle the state of the digital output pin every period milliseconds. The pin's starting value is specified by startingValue, which should be HIGH or LOW. Optionally stops after repeatCount times.
Syntax:
	t.oscillate(pin, period, startingValue);  
	t.oscillate(pin, period, startingValue, repeatCount);
Parameters:
	pin: The number of the pin to oscillate (uint8_t or byte) 
	period: How often to toggle the pin, in milliseconds (unsigned long)
	startingValue: HIGH or LOW, the state at which the pin will start (uint8_t or byte)
	repeatCount: Optional number of toggles to stop after (int)
Returns:
	The ID of the Timer event (int8_t or char)


pulse();
Description:
	Generates a pulse of !startingValue, occuring period after the call to this method and lasting for period. The pin will be left in !startingValue state.
Syntax:
	t.pulse(pin, period, startingValue);
Parameters:
	pin: The number of the pin to pulse (uint8_t or byte)
	period: The pulse period in milliseconds (unsigned long)
	startingValue: HIGH or LOW, the state at which the pin will start (uint8_t or byte)
Returns:
	The ID of the Timer event (int8_t or char)


pulseImmediate();
Description:
	Generates a pulse of startingValue, which begins immediately and lasts for period. The pin will be left in the !startingValue state.
Syntax:
	t.pulseImmediate(pin, period, pulseValue);
Parameters:
	pin: The number of the pin to pulse (uint8_t or byte)
	period: The pulse period in milliseconds (unsigned long)
	startingValue: HIGH or LOW, the state at which the pulse will start (uint8_t or byte)
Returns:
	The ID of the Timer event (int8_t or char)


stop();
Description:
	Stops the given timer event.
Syntax:
t.stop(timerID);
Parameters:
	timerID: The number of the timer event to be stopped, as returned previously by one of the other functions, e.g. every(), after(), oscillate(), etc.
Returns:
	If a valid timerID is given, returns TIMER_NOT_AN_EVENT to indicate that the timer was successfully stopped.  By default, the library supports up to 10 events per timer; the valid range is therefore 0-9.  If a value outside this range is given, that same value is returned.


update();
Description:
	Must be called from loop().  This will service all the events associated with the timer.
Syntax:
	t.update();
Parameters:
	None.
Returns:
	None.



REVISION HISTORY

#1.0 by Simon Monk
- Library as downloaded 02Feb2012 22:55 UTC from http://srmonk.blogspot.com/2012/01/arduino-timer-library.html

#1.1 by Jack Christensen
Changed data types of variables and functions:
- event types and indexes changed from int to int8_t.
- periods and durations changed from long to unsigned long.
- update() and stop() functions typed as void, since they return nothing.
- pin numbers and pin values changed from int to uint8_t, this agrees with digitalWrite().
- added return values to Timer::pulse() and Timer::oscillate(uint8_t, unsigned long, uint8_t).
- changed test in Event::update() to use subtraction to avoid rollover issues.
- Updated keywords.txt file to include all functions.

#1.2 by Damian Philipp
- Added a range check to Timer::stop() to avoid memory corruption.
- Added constants to <Timer.h>: 
  - NO_TIMER_AVAILABLE: Signals that while an event was to be queued, no free timer could be found.
  - TIMER_NOT_AN_EVENT: Can be used to flag a variable that *might* contain a timer ID as *not* containing a timer ID
- Replaced a bunch of magic numbers in Timer.cpp with the above constants
- Added several comments
- Added Timer::pulseImmediate(). pulseImmediate sets the pin to the specified value for the given duration. After the duration, the pin is set to !value.
   
#1.3 by Jack Christensen
- Added "blink2" example illustrating flashing two LEDs at different rates.
- 19Oct2013: This is the last v1.x release. It will continue to be available on GitHub as a branch named v1.3. Future development will continue with Sandy Walsh's v2.0 which can pass context (timer ID, etc.) to the callback functions.
   
#2.0 by Sandy Walsh
- Added a "context" parameter to callbacks. You can pass in the context when the event is created and it will be sent back to callback when called. If you don't have any context data you want to pass in (let's say you're using separate callbacks for each timer), you can just pass in 0 and ignore it in the callback.
   
#2.1 by ThoMo
- Changed the stop() method to return TIMER_NOT_AN_EVENT when it is given a valid timer event ID.  Given an invalid (out of bounds) ID, it simply returns the same ID that it was given.
- Converted the ReadMe file to Markdown, added examples, reference, etc. from Dr. Monk's site. *[jc]*.
- Minor cosmetic editing, tabs to spaces *[jc]*.
