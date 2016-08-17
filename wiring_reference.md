#Wiring reference
To extend this core's functionality a bit futher, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isnt active. These functions is used as "regular" Arduino functions, and there's no need to include an external library.

##Content
* [portMode](#portmode())()
* [portRead](#portread())()
* [portWrite](#portwrite())()
* [enableSleep](#enablesleep())()
* [disableSleep](#disablesleep())()
* [sleepMode](#sleepmode())()
* [startSleep](#startsleep())()
* [sleep](#sleep())()	
* [enablePower](#enablepower())()	
* [disablepower](#disablepower())()

##portMode()
The <b>portMode()</b> method sets a specified digital I/O port as INPUT or OUTPUT. A digital I/O port is a group of 8 pins. By writing 0 to a port it will set individually each of the 8 pins to 0 (LOW). Possible values range from 0 to 255. It possible to read or write a value of a digital I/O port by using the <b>[portRead()](#portread)</b> and <b>[portWrite()](#portwrite)</b> methods.

###Syntax
``` cpp
portMode(portNumber, value)
```
<br/>

####Parameters
`portNumber` - <i>byte/uint8_t</i> <br/>
`value` - <i>byte/uint8_t</i>

| PortNumber  | Physical port |
|-------------|---------------|
| 0           | PORTA         |
| 1           | PORTB         |
| 2           | PORTC         |
| 3           | PORTD         |
<br/>

####Returns
`none`
<br/>
<br/>
###Example
``` c++
byte portNumber = 1; // Use port B
byte val = 0;

void setup() {
  portMode(portNumber, OUTPUT);
}

void loop() {
  portWrite(portNumber, val);
  val = val + 1;
  if (val > 255) 
    val = 0;
}
```
<br/>

##portRead()
The <b>portRead()</b> method reads the value of the digital input port specified.
<br/>

###Syntax
``` c++
portRead(portNumber)
```
<br/>

####Parameters
`portNumber` - <i>byte/uint8_t</i> <br/>

| PortNumber  | Physical port |
|-------------|---------------|
| 0           | PORTA         |
| 1           | PORTB         |
| 2           | PORTC         |
| 3           | PORTD         |
<br/>

####Returns
`byte/uint8_t`
<br/>
<br/>

###Example
``` c++
byte inport = 1;
byte val = 0;

void setup() {
  portMode(inport, INPUT); 
  Serial.begin(9600);
}

void loop() {
  val = portRead(inport);
  Serial.print(val);
}
```

##portWrite()

##enableSleep()

##disableSleep()

##sleepMode()

##startSleep()

###sleep()

###enablePower()

###disablePower()
