#ifndef _C_WIFI_H_
#define _C_WIFI_H_

	#define MY_DEFAULT_HOST_NAME            "APPLICATION"

	#define MY_DEFAULT_SSID_NAME	"CHANGEME"	/* if WF_SECURITY_WPS_PUSH_BUTTON must be "" (empty string) */
	#define MY_DEFAULT_PSK_PHRASE 	"CHANGEME"

	//#define WIFI_STACK_USE_USB
	//#define WIFI_STACK_USE_UART1
	//#define WIFI_STACK_USE_UART2

	//#define WIFI_STACK_USE_RTC
	//#define STACK_USE_UART                         // Application demo using UART for IP address display and stack configuration
	//#define STACK_USE_MQTT_CLIENT
	//#define STACK_USE_UART_SNIFF_SNTP
	//#define STACK_USE_UART2TCP_BRIDGE            // UART to TCP Bridge application example
	#define STACK_USE_IP_GLEANING
	#define STACK_USE_ICMP_SERVER                  // Ping query and response capability
	//#define STACK_USE_ICMP_CLIENT                // Ping transmission capability
	#define STACK_USE_HTTP2_SERVER                 // New HTTP server with POST, Cookies, Authentication, etc.
	#define STACK_USE_HTTP_CLIENT
	//#define STACK_USE_SSL_SERVER                 // SSL server socket support (Requires SW300052)
	//#define STACK_USE_SSL_CLIENT                 // SSL client socket support (Requires SW300052)
	//#define STACK_USE_AUTO_IP                    // Dynamic link-layer IP address automatic configuration protocol
	#define STACK_USE_DHCP_CLIENT                  // Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
	//#define STACK_USE_DHCP_SERVER                // Single host DHCP server
	//#define STACK_USE_FTP_SERVER                 // File Transfer Protocol (old)
	//#define STACK_USE_SMTP_CLIENT                  // Simple Mail Transfer Protocol for sending email
	//#define STACK_USE_TFTP_CLIENT                // Trivial File Transfer Protocol client
	//#define STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE // HTTP Client example in generic_tcp_client.c
	//#define STACK_USE_GENERIC_TCP_SERVER_EXAMPLE // ToUpper server example in generic_tcp_server.c
	//#define STACK_USE_TELNET_SERVER              // Telnet server
	#define STACK_USE_ANNOUNCE                     // Microchip Embedded Ethernet Device Discoverer server/client
	#define STACK_USE_DNS_CLIENT                   // Domain Name Service Client for resolving hostname strings to IP addresses
	//#define STACK_USE_DNS_SERVER                 // Domain Name Service Server for redirection to the local device
	#define STACK_USE_NBNS                         // NetBIOS Name Service Server for repsonding to NBNS hostname broadcast queries
	#define STACK_USE_REBOOT_SERVER              // Module for resetting this PIC remotely.  Primarily useful for a Bootloader.
	#define STACK_USE_SNTP_CLIENT                  // Simple Network Time Protocol for obtaining current date/time from Internet
	//#define STACK_USE_UDP_PERFORMANCE_TEST       // Module for testing UDP TX performance characteristics.  NOTE: Enabling this will cause a huge amount of UDP broadcast packets to flood your network on the discard port.  Use care when enabling this on production networks, especially with VPNs (could tunnel broadcast traffic across a limited bandwidth connection).
	//#define STACK_USE_TCP_PERFORMANCE_TEST       // Module for testing TCP TX performance characteristics
	//#define STACK_USE_DYNAMICDNS_CLIENT          // Dynamic DNS client updater module
	//#define STACK_USE_BERKELEY_API               // Berekely Sockets APIs are available
	//#define STACK_USE_ZEROCONF_LINK_LOCAL          // Zeroconf IPv4 Link-Local Addressing
	//#define STACK_USE_ZEROCONF_MDNS_SD             // Zeroconf mDNS and mDNS service discovery


#endif