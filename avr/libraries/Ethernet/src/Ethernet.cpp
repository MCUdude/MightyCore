#include "Ethernet.h"
#include "w5100.h"
#include "Dhcp.h"

IPAddress EthernetClass::_dnsServerAddress;
DhcpClass* EthernetClass::_dhcp = NULL;

int EthernetClass::begin(uint8_t *mac, unsigned long timeout, unsigned long responseTimeout)
{
	static DhcpClass s_dhcp;
	_dhcp = &s_dhcp;

	// Initialise the basic info
	W5100.init();
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.setMACAddress(mac);
	W5100.setIPAddress(IPAddress(0,0,0,0).raw_address());
	SPI.endTransaction();

	// Now try to get our config info from a DHCP server
	int ret = _dhcp->beginWithDHCP(mac, timeout, responseTimeout);
	if (ret == 1) {
		// We've successfully found a DHCP server and got our configuration
		// info, so set things accordingly
		SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
		W5100.setIPAddress(_dhcp->getLocalIp().raw_address());
		W5100.setGatewayIp(_dhcp->getGatewayIp().raw_address());
		W5100.setSubnetMask(_dhcp->getSubnetMask().raw_address());
		SPI.endTransaction();
		_dnsServerAddress = _dhcp->getDnsServerIp();
		socketPortRand(micros());
	}
	return ret;
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip)
{
	// Assume the DNS server will be the machine on the same network as the local IP
	// but with last octet being '1'
	IPAddress dns = ip;
	dns[3] = 1;
	begin(mac, ip, dns);
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns)
{
	// Assume the gateway will be the machine on the same network as the local IP
	// but with last octet being '1'
	IPAddress gateway = ip;
	gateway[3] = 1;
	begin(mac, ip, dns, gateway);
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway)
{
	IPAddress subnet(255, 255, 255, 0);
	begin(mac, ip, dns, gateway, subnet);
}

void EthernetClass::begin(uint8_t *mac, IPAddress ip, IPAddress dns, IPAddress gateway, IPAddress subnet)
{
	W5100.init();
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.setMACAddress(mac);
#if ARDUINO > 106 || TEENSYDUINO > 121
	W5100.setIPAddress(ip._address.bytes);
	W5100.setGatewayIp(gateway._address.bytes);
	W5100.setSubnetMask(subnet._address.bytes);
#else
	W5100.setIPAddress(ip._address);
	W5100.setGatewayIp(gateway._address);
	W5100.setSubnetMask(subnet._address);
#endif
	SPI.endTransaction();
	_dnsServerAddress = dns;
}

void EthernetClass::init(uint8_t sspin)
{
	W5100.setSS(sspin);
}

int EthernetClass::maintain()
{
	int rc = DHCP_CHECK_NONE;
	if (_dhcp != NULL) {
		// we have a pointer to dhcp, use it
		rc = _dhcp->checkLease();
		switch (rc) {
		case DHCP_CHECK_NONE:
			//nothing done
			break;
		case DHCP_CHECK_RENEW_OK:
		case DHCP_CHECK_REBIND_OK:
			//we might have got a new IP.
			SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
			W5100.setIPAddress(_dhcp->getLocalIp().raw_address());
			W5100.setGatewayIp(_dhcp->getGatewayIp().raw_address());
			W5100.setSubnetMask(_dhcp->getSubnetMask().raw_address());
			SPI.endTransaction();
			_dnsServerAddress = _dhcp->getDnsServerIp();
			break;
		default:
			//this is actually a error, it will retry though
			break;
		}
	}
	return rc;
}

IPAddress EthernetClass::localIP()
{
	IPAddress ret;
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.getIPAddress(ret.raw_address());
	SPI.endTransaction();
	return ret;
}

IPAddress EthernetClass::subnetMask()
{
	IPAddress ret;
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.getSubnetMask(ret.raw_address());
	SPI.endTransaction();
	return ret;
}

IPAddress EthernetClass::gatewayIP()
{
	IPAddress ret;
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);
	W5100.getGatewayIp(ret.raw_address());
	SPI.endTransaction();
	return ret;
}












EthernetClass Ethernet;
