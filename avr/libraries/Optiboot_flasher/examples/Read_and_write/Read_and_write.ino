/*---------------- Flasher example for the MightyCore ----------------------|
 |                                                                          |
 | Created May 2016 by MCUdude, https://github.com/MCUdude                  |
 | Based on the work done by by Marek Wodzinski, https://github.com/majekw  | 
 | Released to public domain                                                |
 |                                                                          |
 | This is example how to use optiboot.h together with Optiboot             |
 | bootloader to write to FLASH memory by application code.                 |
 |                                                                          |
 | IMPORTANT THINGS:                                                        |
 | - All flash content gets erased after each upload cycle                  |
 | - Buffer must be page aligned (see declaration of flash_buffer)          |
 | - Interrupts must be disabled during SPM                                 |
 | - Writing to EEPROM destroys temporary buffer                            |
 | - You can write only once into one location of temporary buffer          |
 | - Only safely and always working sequence is erase-fill-write            |
 | - If you want to do fill-erase-write, you must put code in NRWW          |
 |   and pass data!=0 for erase. It's not easy, but possible.               |
 |                                                                          |
 | WRITE SEQUENCE - OPTION 1 (used in this example)                         |
 | 1. Erase page by optiboot_page_erase                                     |
 | 2. Write contents of page into temporary buffer by optiboot_page_fill    |
 | 3. Write temporary buffer to FLASH by optiboot_page_write                |
 |                                                                          |
 | WRITE SEQUENCE - OPTION 2 (works only for code in NRWW)                  |
 | 1. Write contents of page into temporary buffer by optiboot_page_fill    |
 | 2. Erase page by optiboot_page_erase (set data to NOT zero)              |
 | 3. Write temporary buffer to FLASH by optiboot_page_write                |
 |-------------------------------------------------------------------------*/

#include "optiboot.h"

// Define the number of pages you want to write to here (limited by flash size)
#define NUMBER_OF_PAGES 8

// Define your termination character here
const char terminationChar = '@';


// This array allocates the space you'll be able to write to
const char flash_buffer[SPM_PAGESIZE * NUMBER_OF_PAGES] __attribute__ (( aligned(SPM_PAGESIZE) )) PROGMEM = {
  "This some default content stored on page one."
};


uint8_t ramBuffer[SPM_PAGESIZE];
uint8_t charBuffer;

uint8_t menuOption;
uint16_t pageNumber;


// Method to read a flash page
void readPage(uint16_t page)
{
  uint8_t buffer;
  for(uint16_t j = 0; j < SPM_PAGESIZE; j++) 
  {
    buffer = pgm_read_byte(&flash_buffer[j + SPM_PAGESIZE*(page-1)]);
    if (buffer != 0 && buffer != 255) 
      Serial.write(buffer);
    else
      Serial.print(".");
  }
}


//Method to write data to a flash page
void writePage(uint8_t data[], uint16_t page)
{
   uint16_t wordBuffer = 0; 
   // Erase flash page
    Serial.println(F("Erasing buffer"));
    optiboot_page_erase((optiboot_addr_t)(void*) &flash_buffer[0 + SPM_PAGESIZE*(page-1)]);

    
    // Copy ram buffer to temporary flash buffer
    Serial.println(F("Writing to temporary flash buffer"));
    
  
    for (uint16_t i = 0; i < SPM_PAGESIZE; i++) 
    {
      if (i % 2 == 0) // We must write words
        wordBuffer = data[i];
      else 
      {
        wordBuffer += (data[i] << 8);
        optiboot_page_fill((optiboot_addr_t)(void*) &flash_buffer[i + SPM_PAGESIZE*(page-1)], wordBuffer);
      }
    }
    
    // Writing temporary buffer to FLASH
    Serial.println(F("Writing buffer to flash"));
    optiboot_page_write((optiboot_addr_t)(void*) &flash_buffer[0 + SPM_PAGESIZE*(page-1)]);
  
    Serial.println(F("Write done, thank you!"));   
}


void setup()
{
  // Initialize serial
  Serial.begin(9600);
}


void loop() 
{
   // Print main menu
  Serial.println();
  Serial.println(F("|------------------------------------------------|"));
  Serial.println(F("| Welcome to the Optiboot flash writer example!  |"));
  Serial.print(F("| Each flash page is "));
  Serial.print(SPM_PAGESIZE);
  Serial.println(F(" bytes long.             |"));
  Serial.println(F("|                                                |"));
  Serial.println(F("| Please tell me what you want to do:            |"));
  Serial.println(F("| 1. Show current flash content                  |"));
  Serial.println(F("| 2. Write to flash memory                       |"));
  Serial.println(F("|------------------------------------------------|"));
  Serial.println();

  
  // Get menu option from the serial monitor
  do
  {
    while(!Serial.available());
    menuOption = Serial.parseInt();
    if(menuOption < 1 || menuOption > 2)
      Serial.print(F("\nPlease enter a valid option! "));
  }
  while(menuOption < 1 || menuOption > 2);
  
  Serial.print(F("Option "));
  Serial.print(menuOption);
  Serial.println(F(" selected."));

    
  // Flash read option selected
  if(menuOption == 1)
  {
    Serial.print(F("What page number do you want to read? Page: "));

    //Get page number from the serial monitor
    do
    {
      while(!Serial.available());
      pageNumber = Serial.parseInt();
      if(pageNumber < 1 || pageNumber > NUMBER_OF_PAGES)
      {
        Serial.print(F("\nPlease enter a valid page between 1 and "));
        Serial.print(NUMBER_OF_PAGES);
        Serial.println(F(". The number of pages can be extended by changing NUMBER_OF_PAGES constant"));
      }
    }
    while(pageNumber < 1 || pageNumber > NUMBER_OF_PAGES);
    Serial.println(pageNumber);
   
  
    // Print page content
    Serial.print(F("\nContent of page "));
    Serial.print(pageNumber);
    Serial.println(F(":"));
    readPage(pageNumber);
  }  // End of flash read option


 
  // Flash write option selected
  else if(menuOption == 2)
  {
    // Clear pageNumber
    pageNumber = 0;


    //Get page number from the serial monitor
    Serial.print(F("\nWhat page do you want to write to? Page: "));
    do
    {
      while(!Serial.available());
      pageNumber = Serial.parseInt();
      if(pageNumber < 1 || pageNumber > NUMBER_OF_PAGES)
      {
        Serial.print(F("\nPlease enter a valid page between 1 and "));
        Serial.print(NUMBER_OF_PAGES);
        Serial.println(F(". The number of pages can be extended by changing NUMBER_OF_PAGES constant"));
      }
    }
    while(pageNumber < 1 || pageNumber > NUMBER_OF_PAGES);
    Serial.println(pageNumber);


    // Print prompt to enter some new characters to write to flash
    Serial.print(F("Please type the characters you want to store (max "));
    Serial.print(SPM_PAGESIZE);
    Serial.println(F(" characters)"));
    Serial.print(F("End the line by sending the '"));
    Serial.write(terminationChar);
    Serial.println(F("' character:"));
    

    // Get all characters from the serial monitor
    uint16_t counter = 0;
    while (counter < SPM_PAGESIZE && charBuffer != terminationChar) 
    {
      if(Serial.available() > 0) 
      {
        charBuffer = Serial.read(); // read character from serial
        if(charBuffer != terminationChar)
        {
          Serial.write(charBuffer); // echo character back
          ramBuffer[counter] = charBuffer;
          counter++;
        }      
      }
    }
    Serial.println(F("\n\nAll chars received"));

    // Write data to flash
    writePage(ramBuffer, pageNumber);
    Serial.println(F("Now you can reset or power cycle board and check for new contents!"));
  } // End of flash write option


  //Return to the main menu if 'm' is sent
  Serial.println(F("\ntype the character 'm' to return to to the main menu"));
  char returnToMenu;
  do
  {
    while(!Serial.available());
    returnToMenu = Serial.read();
    if(returnToMenu != 'm')
      Serial.print(F("\nPlease type a valid character! "));
  }
  while(returnToMenu != 'm');

} // End of loop




 
