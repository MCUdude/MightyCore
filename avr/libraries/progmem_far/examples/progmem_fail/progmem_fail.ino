// This sketch demonstrates that there are multiple 
// silent failures when using the ordinary PROGMEM macros.
// Compiled and uploaded on a chip with more then 64kB,
// the LED will not blink and it will output something like:
//
// DU
// 10
// 160
// 8161
// 162
//
// instead of:
//
// PROGMEM test
// 1
// 10160
// 8161
// 162


#include <avr/pgmspace.h>

const byte tab0[5] PROGMEM = { 1, 2, 3};
const byte tab1[32767] PROGMEM = {  };
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
  Serial.println((unsigned int)&tab0, HEX);
  Serial.println((unsigned int)&tab1, HEX);
  Serial.println((unsigned int)&tab2, HEX);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
