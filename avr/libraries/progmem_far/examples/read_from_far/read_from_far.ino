// Example using the PROGMEM_FAR macro

#include <avr/pgmspace.h>
#include <progmem_far.h>

const char PROGMEM_FAR hello[] = "Hello World";
const unsigned long PROGMEM_FAR table[] = {0xFFFFFFFF, 0xEEEEEEEE, 0xDDDDDDDD, 0x12345678, 0};

void setup () {
  unsigned long hello_far = pgm_get_far_address(hello);
  unsigned long table_far = pgm_get_far_address(table);
  char c;
  unsigned long val;

  Serial.begin(19200);
  Serial.println("\nPROGMEM_FAR test");

  for (int i=0; i < strlen_PF(hello_far); i++) {
    c = pgm_read_byte_far(hello_far+i);
    Serial.write(c);
  }
  
  Serial.println();

  do {
    val = pgm_read_dword_far(table_far);
    table_far += 4;
    Serial.println(val,HEX);
  } while (val != 0);
}

void loop () { }
