// This sketch shows how to fix all the problems shown
// in the sketch progmem_fail. By using the macro PROGMEM_FAR
// on tab1, the user structure tab0, the string stored with the F-macro
// and the lookup tables for the Arduino core functions can now
// all be allocated in the lowert 64kB area. And so, the LED woll blink,
// and the output will be:
//
// PROGMEM test
// 1
// 8161
// 8B76
// 162

#include <avr/pgmspace.h>
#include <progmem_far.h> 

const byte tab0[5] PROGMEM = { 1, 2, 3};
const byte tab1[32767] PROGMEM_FAR = {  };
const byte tab2[32767] PROGMEM = {  };

void setup()
{
  Serial.begin(19200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  Serial.println();
  Serial.println(F("PROGMEM test"));
  Serial.println(pgm_read_byte(&tab0[0]));
  Serial.println(pgm_get_far_address(tab0), HEX);
  Serial.println(pgm_get_far_address(tab1), HEX);
  Serial.println(pgm_get_far_address(tab2), HEX);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

