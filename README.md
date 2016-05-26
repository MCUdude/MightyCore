#MightyCore
An Arduino core for large, breadboard friendly AVRs, all running [Optiboot 6](https://github.com/Optiboot/optiboot). Major libraries such as SD, Servo, SPI and Wire are modified to work with this core. Still, a large amount of third-party libraries often works without any modifications. 
<br/> <br/>
This core requires at least Arduino IDE v1.6, where v1.6.5+ is recommended. 
<br/>
An Arduino forum post for this particular core are located [here](http://forum.arduino.cc/index.php?topic=379427.0). 
<br/> <br/>
If you're into "pure" AVR programming, I'm happy to tell you that all relevant keywords are being highlighted by the IDE through a separate keywords file. Make sure to test the [example files](https://github.com/MCUdude/MightyCore/tree/master/avr/libraries/AVR_examples/examples) (File > Examples > AVR C code examples).
<br/> <br/>
If you're looking for a great development board for these DIP-40 microcontrollers, I got you covered! I've used the Arduino UNO for years,
but felt like some functionality was missing on the board. When designing this board I made sure all missing functionality was added. [The board can be bought on my Tindie store](https://www.tindie.com/products/MCUdude/dip-40-arduino-compatible-development-board).
Read more in the hardware section below.

#Table of contents
* [Supported microcontrollers](#supported-microcontrollers)
* [Supported clock frequencies](#supported-clock-frequencies)
* [BOD option](#bod-option)
* [Pinout](#pinout)
* [Programmers](#programmers)
* [Write to own flash](#write-to-own-flash)
* [How to install](#how-to-install)
	- [Boards Manager Installation](#boards-manager-installation)
	- [Manual Installation](#manual-installation)
	- [PlatformIO](#platformio)
* [Library porting](#library-porting)	
* [Hardware](#hardware)	
* [Minimal setup](#minimal-setup)


##Supported microcontrollers
* ATmega1284*
* ATmega644*
* ATmega324*
* ATmega164*
* ATmega32*
* ATmega16*
* ATmega8535*

(* all variants - P, PA, A. Select the correct version in the 'Variant' menu)


##Supported clock frequencies
* 20 MHz external oscillator
* 16 MHz external oscillator (default)
* 8 MHz external oscillator
* 8 MHz internal oscillator
* 1 MHz internal oscillator 
 
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external oscillator is recommended.

##BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. For microcontrollers with an extended fuse (ATmega164/324/644/1284) there is a separate BOD option. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader".

##Pinout
This core got two different pinout option. The default one is named "Standard", and is based on the original AVR pinout. The other one is named "Bobuino" and is basically an Arduino UNO pinout setting. This pinout version is great for using with shields or code that's written for the Arduino UNO, as the pin functions stays the same (MOSI on D11, MISO on D12, SCK on D13). Please have a look at the (`pins_arduino.h`) files for more info. Pick your favorite!</br> </br>
<b>Click to enlarge:</b> 
</br> </br>
<img src="http://i.imgur.com/hZGMRwH.png" width="375"> <img src="http://i.imgur.com/9cpfTGl.png" width="430">
</br> </br>
<img src="http://i.imgur.com/PF1HWho.png" width="375"> <img src="http://i.imgur.com/fHC5LQK.png" width="430">

##Programmers
MightyCore adds its own copies of all the standard programmers to the "Programmer" menu. You must select the MightyCore copy of the programmer you are using for "Upload Using Programmer" to work with ATmega1284, ATmega324A, or ATmega164A.

##Write to own flash
A while ago [@majekw](https://github.com/majekw) announced that he'd [successfully modified the Optiboot bootloader](http://forum.arduino.cc/index.php?topic=332191.0) to let the running program permanently store content in the flash memory.
The flash memory is much faster than the EEPROM, and can handle about 10 000 write cycles. <br/>
With help from [@sunnyque](https://github.com/MCUdude/MightyCore/issues/24) this feature is working perfectly with the MightyCore! To enable this feature the bootloader needs to be replaced by the new one. Simply hit "Burn Bootloader", and it's done! <br/>
Please check out the [Optiboot flasher example](https://github.com/MCUdude/MightyCore/tree/master/avr/libraries/Optiboot_flasher/examples/Read_and_write/Read_and_write.ino) for more info about how this feature works, and how you can try it on your own MightyCore compatible microcontroller.


##How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json`
* Open the **Tools > Board > Boards Manager...** menu item.
* Wait for the platform indexes to finish downloading.
* Scroll down until you see the **MightyCore** entry and click on it.
  * **Note**: If you are using Arduino IDE 1.6.6 then you may need to close **Boards Manager** and then reopen it before the **MightyCore** entry will appear.
* Click **Install**.
* After installation is complete close the **Boards Manager** window.

####Manual Installation
Click on the "Download ZIP" button. Exctract the ZIP file, and move the extracted folder to the location "**~/Documents/Arduino/hardware**". Create the "hardware" folder if it doesn't exist.
Open Arduino IDE, and a new category in the boards menu called "MightyCore" will show up.

####PlatformIO
[PlatformIO](http://platformio.org) is an open source ecosystem for IoT development. It got a built-in library manager and is Arduino compatible. It support most operating systems; Windows, Mac OSX, Linux 32 and 64-bit; ARM and X86.

* [What is PlatformIO?](http://docs.platformio.org/en/latest/what-is-platformio.html)
* [PlatformIO IDE](http://platformio.org/#!/platformio-ide)
* Getting started with [PlatformIO IDE](http://docs.platformio.org/en/latest/ide/atom.html#quick-start) or [PlatformIO command line interface](http://docs.platformio.org/en/latest/quickstart.html)
* [Advanced functionality](http://docs.platformio.org/en/latest/platforms/atmelavr.html) 
* [MightyCore compatible microcontrollers](http://docs.platformio.org/en/latest/platforms/atmelavr.html#mcudude)
* [Integration with other IDE](http://docs.platformio.org/en/latest/ide.html) -
  Atom, CLion, Eclipse, Emacs, NetBeans, Qt Creator, Sublime Text, VIM and Visual Studio
* [Project Examples](http://docs.platformio.org/en/latest/platforms/atmelavr.html#examples)

##Library porting
Some users have reported issues when trying to use some 3rd party libraries with the ATmega8535, ATmega16 or ATmega32.
A simple guide to port a library can be found <b>[here](https://github.com/MCUdude/MightyCore/blob/master/Library_porting.md)</b>.

##Hardware
I've designed a development board for this particular core. I've added all the functionality I missed with the original Arduino boards, and added the original AVR pinout. 
Not all supported microcontrollers have the same pin functions, and differences are highlighted. The boards measures 8.0 * 10.0 cm (3.15 * 3.94 in)<br/>
The development board got some additional unique features:
* A voltage select jumper to run the microcontroller at 5V or 3.3V
* All pins are located at the same side of the board, making it easy to hook it up to a breadboard
* Possible to add both male and female header for the IO pins (and solder a row of male headers under the board for breadboarding)
* A JTAG header for programming and debugging
* A high voltage parallel programming header for programming and fixing bad fuse settings (pin compatible with the AVR Dragon)
* A potmeter for using as a voltage reference (e.g adjusting the LCD contrast)
* LOTS of 5V, 3.3V and GND points broken out, both male and female
* Socketed crystal, perfect for experimenting with different clock frequencies
* A Reset enable header to enable/disable auto-reset when uploading new code or opening the serial monitor
* PWM pins are clearly marked, and a lookup table can be found on the under side of the board (three '~'s - all microcontrollers, two '~'s - 164; 324; 644; 1284, one '~' - 1284)
* IO peripherals can be found on the underside of the board. No need to search in the datasheet anymore!
* Mini USB instead of the large USB Type-B plug
* The USB to serial chip is broken out on the underside of the board in a standard "FTDI pinout" for using the board as a USB to serial adapter, or for using an external programmer instead
* The rest of the hand shake pins (CTS, DTR, RI, DCD) in the USB to serial adapter are broken out for other applications, such as bit banging

####[The development board can be bought on my Tindie store.](https://www.tindie.com/products/MCUdude/dip-40-arduino-compatible-development-board/) This includes a pre programmed ATmega32. <br/>
<br/>
Click the images for full resolution <br/>
![Development board front](http://i.imgur.com/zovyQUy.jpg)
<br/>
![Development board back](http://i.imgur.com/cWmPBWh.jpg)
<br/>
![Semi assembled board](http://i.imgur.com/CEDMgzg.jpg)

##Minimal setup
Here is a simple schematic showing a minimal setup using an external crystal. Skip the crystal and the two capacitors if you're using the internal oscillator. <br/>
<img src="http://i.imgur.com/DG9AiKe.png" width="750">

