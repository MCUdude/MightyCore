#include "Ethernet.h"
#include "w5100.h"

uint16_t EthernetServer::server_port[MAX_SOCK_NUM];


void EthernetServer::begin()
{
  uint8_t sockindex = Ethernet.socketBegin(SnMR::TCP, _port);
  if (sockindex < MAX_SOCK_NUM) {
    if (Ethernet.socketListen(sockindex)) {
      server_port[sockindex] = _port;
    } else {
      Ethernet.socketDisconnect(sockindex);
    }
  }
}

EthernetClient EthernetServer::available()
{
  bool listening = false;
  uint8_t sockindex = MAX_SOCK_NUM;

  for (uint8_t i=0; i < MAX_SOCK_NUM; i++) {
    if (server_port[i] == _port) {
      uint8_t stat = Ethernet.socketStatus(i);
      if (stat == SnSR::ESTABLISHED || stat == SnSR::CLOSE_WAIT) {
        if (Ethernet.socketRecvAvailable(i) > 0) {
          sockindex = i;
        } else {
          // remote host closed connection, our end still open
          if (stat == SnSR::CLOSE_WAIT) {
            Ethernet.socketDisconnect(i);
            // status becomes LAST_ACK for short time
          }
        }
      } else if (stat == SnSR::LISTEN) {
        listening = true;
      } else if (stat == SnSR::CLOSED) {
        server_port[i] = 0;
      }
    }
  }
  if (!listening) begin();
  return EthernetClient(sockindex);
}

#if 0
void EthernetServer::statusreport()
{
  Serial.printf("EthernetServer, port=%d\n", _port);
  for (uint8_t i=0; i < MAX_SOCK_NUM; i++) {
    uint16_t port = server_port[i];
    uint8_t stat = Ethernet.socketStatus(i);
    const char *name;
    switch (stat) {
      case 0x00: name = "CLOSED"; break;
      case 0x13: name = "INIT"; break;
      case 0x14: name = "LISTEN"; break;
      case 0x15: name = "SYNSENT"; break;
      case 0x16: name = "SYNRECV"; break;
      case 0x17: name = "ESTABLISHED"; break;
      case 0x18: name = "FIN_WAIT"; break;
      case 0x1A: name = "CLOSING"; break;
      case 0x1B: name = "TIME_WAIT"; break;
      case 0x1C: name = "CLOSE_WAIT"; break;
      case 0x1D: name = "LAST_ACK"; break;
      case 0x22: name = "UDP"; break;
      case 0x32: name = "IPRAW"; break;
      case 0x42: name = "MACRAW"; break;
      case 0x5F: name = "PPPOE"; break;
      default: name = "???";
    }
    int avail = Ethernet.socketRecvAvailable(i);
    Serial.printf("  %d: port=%d, status=%s (0x%02X), avail=%d\n",
      i, port, name, stat, avail);
  }
}
#endif

size_t EthernetServer::write(uint8_t b) 
{
  return write(&b, 1);
}

size_t EthernetServer::write(const uint8_t *buffer, size_t size) 
{
  available();
  for (uint8_t i=0; i < MAX_SOCK_NUM; i++) {
    if (server_port[i] == _port) {
      if (Ethernet.socketStatus(i) == SnSR::ESTABLISHED) {
        Ethernet.socketSend(i, buffer, size);
      }
    }
  }
  return size;
}
