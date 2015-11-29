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

##Pinout
All the microcontrollers in this core use the same basic pinout
Note that there are some differences when it comes to PWM pins and hardware serial. For more information, please look in the datasheet or in the pins_arduino.h file for the specified microcontroller</br>
![MightyCore pinout](http://i.imgur.com/VZHussQ.png "Basic pinout")
