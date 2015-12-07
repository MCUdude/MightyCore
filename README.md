# MightyCore
An Arduino core for large, breadboard friendly AVRs, all running Optiboot 6.1 </br>
Major libraries such as SD, Servo SPI and Wire are modified to work with this core. My experience is that a large amount of third-party libraries works out of the box with no modifications.


##Supported microcontrollers
* ATmega1284*
* ATmega644*
* ATmega324*
* ATmega164*
* ATmega32*
* ATmega16*
* ATmega8535*

(* all variants, such as P, PA, PV and so on)


##Supported clock frequencies
* 20 MHz external oscillator
* 16 MHz external oscillator (default)
* 8 MHz external oscillator
* 8 MHz internal oscillator
* 1 MHz internal oscillator 

##How to install
Click on the "Download ZIP" button. Exctract the Zip file, and move the extracted folder to the location "~/Documents/Arduino/hardware". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu, called "MightyCore" will show up.

##Hardware
I've designed a development board for this particular core. I've added all the functionality I missed with the original Arduino boards, and added the original AVR pinout. 
Not all supported microcontrollers have the same pin functions, and differences are highlighted. The boards measures 8.0*10.0 cm.<br/>
The development board got some additional features not all Arduino compatible boards got:
* A voltage select jumper to run the microcontroller at 5V or 3.3V
* All pins are located at the same side of the board, making it easy to hook it up to a breadboard
* Possible to add both male and female header for the IO pins
* A JTAG header for programming and debugging
* A high voltage parallel programming header for programming and fixing bad fuse settings (pin compatible with the AVR Dragon)
* A potmeter for using as a voltage reference (e.g adjusting the LCD contrast)
* LOTS of 5V, 3.3v and GND points broken out
* Socketed crystal, perfect for experimenting with different clock frequencies
* A Reset enable header to disable auto-reset when uploading new code or opening the serial monitor <br/>

I'm thinking about selling these as bare PCBs and as complete assembled boards including a microcontroller. More info about will be added later!<br/>
Click the images for full resolution :) <br/>
![Development board front](http://i.imgur.com/zovyQUy.jpg)
<br/>
![Development board back](http://i.imgur.com/cWmPBWh.jpg)
<br/>
![Semi assembled board](http://i.imgur.com/CEDMgzg.jpg)

##Pinout
All the microcontrollers in this core use the same basic pinout
Note that there are some differences when it comes to PWM pins and hardware serial. For more information, please look in the datasheet or in the pins_arduino.h file for the specified microcontroller</br>
![MightyCore pinout](http://i.imgur.com/VZHussQ.png "Basic pinout")
