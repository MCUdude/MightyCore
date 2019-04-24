/*
  DHCP-based IP printer

  This sketch uses the DHCP extensions to the Ethernet library
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.

  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi


  MightyCore Standard/Sanguino pinout:
  Wiznet      AVR
  SS/CS  ->   D4 
  MOSI   ->   D5
  MISO   ->   D6
  SCK    ->   D7

  MightyCore Bobuino pinout:
  Wiznet      AVR
  SS/CS  ->   D10
  MOSI   ->   D11
  MISO   ->   D12
  SCK    ->   D13
 
  */

#include <Ethernet.h>
#include <SPI.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // this check is only needed on the Leonardo:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  printIPAddress();
}

void loop() {
  switch (Ethernet.maintain()) {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      //renewed success
      Serial.println("Renewed success");
      //print your local IP address:
      printIPAddress();
      break;

    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      //rebind success
      Serial.println("Rebind success");
      //print your local IP address:
      printIPAddress();
      break;

    default:
      //nothing happened
      break;
  }
}

void printIPAddress() {
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}
