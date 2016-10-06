#MightyCore
An Arduino core for large, breadboard friendly AVRs, all running [Optiboot 6](https://github.com/Optiboot/optiboot). Major libraries such as SD, Servo, SPI and Wire are modified to work with this core. Still, a large amount of third-party libraries often works without any modifications. 
<br/> <br/>
This core requires at least Arduino IDE v1.6, where v1.6.5+ is recommended. <b>Please don't update to IDE v1.6.10 just yet, as there's still some issues to resolve.</b>
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
* [Link time optimization / LTO](#link-time-optimization--lto)
* **[Pinout](#pinout)**
* [Programmers](#programmers)
* [Write to own flash](#write-to-own-flash)
* **[How to install](#how-to-install)**
	- [Boards Manager Installation](#boards-manager-installation)
	- [Manual Installation](#manual-installation)
	- [PlatformIO](#platformio)
* **[Getting started with MightyCore](#getting-started-with-mightycore)**
* [Wiring reference](#wiring-reference)	
* [Library porting](#library-porting)	
* [Hardware](#hardware)	
* **[Minimal setup](#minimal-setup)**


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
* 12 MHz external oscillator
* 8 MHz external oscillator
* 8 MHz internal oscillator <b>*</b>
* 1 MHz internal oscillator 
 
Select your microcontroller in the boards menu, then select the clock frequency. You'll have to hit "Burn bootloader" in order to set the correct fuses and upload the correct bootloader. <br/>
Make sure you connect an ISP programmer, and select the correct one in the "Programmers" menu. For time critical operations an external oscillator is recommended. 
</br></br>
<b>*</b> There might be some issues related to the internal oscillator. It's factory calibrated, but may be a little "off" depending on the calibration, ambient temperature and operating voltage. If uploading failes while using the 8 MHz internal oscillator you have three options:
* Edit the baudrate line in the [boards.txt](https://github.com/MCUdude/MightyCore/blob/a1d4a54df392290ebfd5b67f41fd93fec2b94313/avr/boards.txt#L83) file, and choose either 115200, 57600, 38400 or 19200 baud.
* Upload the code using a programmer (USBasp, USBtinyISP etc.) and drop the bootloader
* Use the 1 MHz option instead


##BOD option
Brown out detection, or BOD for short lets the microcontroller sense the input voltage and shut down if the voltage goes below the brown out setting. For microcontrollers with an extended fuse (ATmega164/324/644/1284) there is a separate BOD option. To change the BOD settings you'll have to connect an ISP programmer and hit "Burn bootloader".

##Link time optimization / LTO
After Arduino IDE 1.6.11 where released, There have been support for link time optimization or LTO for short. The LTO optimizes the code at link time, making the code (often) significantly smaller without making it "slower". In Arduino IDE 1.6.11 and newer LTO is enabled by default. I've chosen to disable this by default to make sure the core keep its backwards compatibility. Enabling LTO in IDE 1.6.10 and older will return an error. 
I encourage you to try the new LTO option and see how much smaller your code gets! Note that you don't need to hit "Burn Bootloader" in order to enable LTO. Simply enable it in the "Tools" menu, and your code is ready for compilation. If you want to read more about LTO and GCC flags in general, head over to the [GNU GCC website](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)!

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
Please check out the [Optiboot flasher example](https://github.com/MCUdude/MightyCore/blob/master/avr/libraries/Optiboot_flasher/examples/SerialReadWrite/SerialReadWrite.ino) for more info about how this feature works, and how you can try it on your MightyCore compatible microcontroller.


##How to install
#### Boards Manager Installation
This installation method requires Arduino IDE version 1.6.4 or greater.
* Open the Arduino IDE.
* Open the **File > Preferences** menu item.
* Enter the following URL in **Additional Boards Manager URLs**: `https://mcudude.github.io/MightyCore/package_MCUdude_MightyCore_index.json`
  * Separate the URLs using a comma ( **,** ) if you have more than one URL
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
 

##Getting started with MightyCore
Ok, so you're downloaded and installed MightyCore, but do I get the wheels spinning? Here's a quick start guide:
* Hook up your microcontroller as shown in the [pinout diagram](#pinout).
	- If you're not planning to use the bootloader (uploading code using a USB to serial adapter), the FTDI header and the 100 nF capacitor on the reset pin can be omitted. 
* Open the **Tools > Board** menu item, and select a MighyCore compatible microcontroller.
* If the *BOD option* is presented, you can select at what voltage the microcontroller will shut down at. Read more about BOD [here](#bod-option).
* Select your prefered pinout. Personally I prefer the standard pinout because it's "cleaner", but the Bobuino pinout is better at Arduino UNO pin compatibility. Read more about the different pinouts [here](#pinouts).
* Select your prefered clock frequency. **16 MHz** is standard on most Arduino boards.
* Select what kind of programmer you're using under the **Programmers** menu.
* If the *Variants* option is presented, you'll have to specify what version of the microcontroller you're using. E.g the ATmega1284 and the ATmega1284P got different device signatures, so selecting the wrong one will result in an error.
* Hit **Burn Bootloader**. If an LED is connected to pin PB0, it should flash twice every second.
* Now that the correct fuse settings is sat and the bootloader burnt, you can upload your code in two ways:
	- Disconnect your programmer tool, and connect a USB to serial adapter to the microcontroller, like shown in the [minimal setup circuit](#minimal-setup). Then select the correct serial port under the **Tools** menu, and click the **Upload** button. If you're getting some kind of timeout error, it means your RX and TX pins are swapped, or your auto reset circuity isn't working properly (the 100 nF capacitor on the reset line).
	- Keep your programmer connected, and hold down the `shift` button while clicking **Upload**. This will erase the bootloader and upload your code using the programmer tool.

Your code should now be running on your microcontroller! If you experience any issues related to bootloader burning or serial uploading, please use *[this forum post](https://forum.arduino.cc/index.php?topic=379427.0)* or create an issue on Github.


##Wiring reference
To extend this core's functionality a bit futher, I've added a few missing Wiring functions. As many of you know Arduino is based on Wiring, but that doesn't mean the Wiring development isnt active. These functions is used as "regular" Arduino functions, and there's no need to include an external library.<br/>
I hope you find this useful, because they really are!

###Function list
* portMode()
* portRead()
* portWrite()
* sleepMode()
* sleep()
* noSleep()
* enablePower()	
* disablePower()

###For further information please view the [Wiring reference page](https://github.com/MCUdude/MightyCore/blob/master/Wiring_reference.md)!


##Library porting
Some users have reported issues when trying to use some 3rd party libraries with the ATmega8535, ATmega16 or ATmega32.
A simple guide to port a library can be found <b>[here](https://github.com/MCUdude/MightyCore/blob/master/Library_porting.md)</b>.

##Hardware
I've designed a development board for this particular core. I've added all the functionality I missed with the original Arduino boards, and added the original AVR pinout. **And for just 30$ it's a really good deal!**
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

