#include <math.h>
#include "app.h"

#include "k_stdtype.h"
#include "tcpip.h"
#include "tmr.h"
#include "ringBuffer.h"

#define APP_THINGSPEAK_TX_LEN 256
#define APP_THINGSPEAK_RX_LEN 256

#define APP_THINGSPEAK_DNS_RESOLVE_TIMEOUT 6000
#define APP_THINGSPEAK_SOCKET_TIMEOUT 8000
#define APP_THINGSPEAK_SEND_TIMEOUT 8000

typedef enum _TransportStates {
    TRANSPORT_HOME = 0,
    TRANSPORT_BEGIN,
    TRANSPORT_NAME_RESOLVE,
    TRANSPORT_OBTAIN_SOCKET,
    TRANSPORT_SOCKET_OBTAINED,
    TRANSPORT_CLOSE
} TransportStates;

volatile unsigned int do_app_thingspeak_1ms = 0;
TransportStates TransportState = TRANSPORT_HOME;
uint8 app_thingspeak_trigger = 0;
char app_thingspeak_server[] = "api.thingspeak.com";
IP_ADDR app_thingspeak_server_ip; // IP address of the remote SMTP server
TCP_SOCKET app_thingspeak_socket = INVALID_SOCKET; // Socket currently in use by the SMTP client
unsigned int app_thingspeak_port = 80;
unsigned char app_thingspeak_socket_was_connected = 0;
Timer app_thingspeak_timeout;
unsigned int app_thingspeak_internal_comm_state = 0;

float app_thingspeak_temperature = 20.0f;
float app_thingspeak_pressure = 1040.0f;
float app_thingspeak_humidity = 62.0f;
float app_thingspeak_CO2 = 480.0f;
float app_thingspeak_LiPoVoltage = 4.1f;
float app_thingspeak_res1 = 0.0;
float app_thingspeak_res2 = 1.0;
float app_thingspeak_res3 = 2.0;

RingBuffer myRingBuffer_app_thingspeak_tx;
unsigned char app_thingspeak_tx[APP_THINGSPEAK_TX_LEN];
RingBuffer myRingBuffer_app_thingspeak_rx;
unsigned char app_thingspeak_rx[APP_THINGSPEAK_RX_LEN];

unsigned long app_thingspeak_missed_tx_char = 0;
unsigned long app_thingspeak_missed_rx_char = 0;

char app_thingspeak_get_string[256];
unsigned int app_thingspeak_get_string_cnt = 0;
unsigned int app_thingspeak_get_string_cnt_max = 0;
char app_thingspeak_temperatureStr[32];
char app_thingspeak_pressureStr[32];
char app_thingspeak_humidityStr[32];
char app_thingspeak_CO2Str[32];
char app_thingspeak_LiPoVoltageStr[32];
char app_thingspeak_reserve1Str[32];
char app_thingspeak_reserve2Str[32];
char app_thingspeak_reserve3Str[32];

float my_pow(float a, float b);

void init_thingspeak(void) {
	ringBuffer_initBuffer(&myRingBuffer_app_thingspeak_tx, app_thingspeak_tx, sizeof(app_thingspeak_tx) / sizeof(*app_thingspeak_tx));
	ringBuffer_initBuffer(&myRingBuffer_app_thingspeak_rx, app_thingspeak_rx, sizeof(app_thingspeak_rx) / sizeof(*app_thingspeak_rx));

	init_timer(&app_thingspeak_timeout);
}

void do_app_thingspeak(void) {
	if (do_app_thingspeak_1ms) {
		do_app_thingspeak_1ms = 0;
		{
		    switch (TransportState) {
    			case TRANSPORT_HOME: {
					if (app_thingspeak_trigger) {
						app_thingspeak_trigger = 0;
						app_thingspeak_socket_was_connected = 0;
						app_thingspeak_internal_comm_state = 0;
						TransportState = TRANSPORT_BEGIN;
					}
					break;
				}
    			case TRANSPORT_BEGIN: {
			        if (DNSBeginUsage()) {
						DNSResolve((unsigned char *)app_thingspeak_server, DNS_TYPE_A);
						write_timer(&app_thingspeak_timeout, APP_THINGSPEAK_DNS_RESOLVE_TIMEOUT);
				        TransportState = TRANSPORT_NAME_RESOLVE;
					}			
					break;
				}
    			case TRANSPORT_NAME_RESOLVE: {
			        // Wait for the DNS server to return the requested IP address
			        if (!DNSIsResolved(&app_thingspeak_server_ip)) {
			            // Timeout after 6 seconds of unsuccessful DNS resolution
			            if (read_timer(&app_thingspeak_timeout) == 0) {
			                TransportState = TRANSPORT_HOME;
			                DNSEndUsage();
			            }
			            break;
			        }
			
			        // Release the DNS module, we no longer need it
			        if (!DNSEndUsage()) {
			            // An invalid IP address was returned from the DNS
			            // server.  Quit and fail permanantly if host is not valid.
			            TransportState = TRANSPORT_HOME;
			            break;
			        }
			
			        TransportState = TRANSPORT_OBTAIN_SOCKET;
					break;
				}
    			case TRANSPORT_OBTAIN_SOCKET: {
			        // Connect a TCP socket to the remote SMTP server
			        app_thingspeak_socket = TCPOpen(app_thingspeak_server_ip.Val, TCP_OPEN_IP_ADDRESS, app_thingspeak_port, TCP_PURPOSE_HTTP_CLIENT_CLIENT);
			
			        // Abort operation if no TCP sockets are available
			        // If this ever happens, add some more
			        // TCP_PURPOSE_DEFAULT sockets in tcpip_config.h
			        if (app_thingspeak_socket == INVALID_SOCKET) {
			            break;
					}
					write_timer(&app_thingspeak_timeout, APP_THINGSPEAK_SOCKET_TIMEOUT);			
			        TransportState = TRANSPORT_SOCKET_OBTAINED;
					break;
				}
    			case TRANSPORT_SOCKET_OBTAINED: {
					uint8_t rxData = 0;

			        if (!TCPIsConnected(app_thingspeak_socket)) {
			            // Don't stick around in the wrong state if the
			            // server was connected, but then disconnected us.
			            // Also time out if we can't establish the connection
			            // to the SMTP server
			            if ((app_thingspeak_socket_was_connected) || (read_timer(&app_thingspeak_timeout) == 0)) {
			                TransportState = TRANSPORT_CLOSE;
			            }
			            break;
			        }
					app_thingspeak_socket_was_connected = 1;

			        // See if the server sent us anything
        			while (TCPIsGetReady(app_thingspeak_socket)) {
            			TCPGet(app_thingspeak_socket, &rxData);
						if (ringBuffer_addItem(&myRingBuffer_app_thingspeak_rx, rxData) != -1) {
						} else {
							app_thingspeak_missed_rx_char++;
						}
						//process here RX data;
					}

			        // Generate new data in the TX buffer, as needed, if possible
        			if (TCPIsPutReady(app_thingspeak_socket) < 64u) {
						break;
					} else {
						unsigned char data = 0;
						unsigned int cnt = 0;
						while (ringBuffer_getItem(&myRingBuffer_app_thingspeak_tx, &data) != 0) {
							TCPPut(app_thingspeak_socket, data);
							cnt++;
							if (cnt >= 64) {
								break;
							}
						}
						if (cnt != 0) {
							TCPFlush(app_thingspeak_socket);
						}
					}

					{//Thingspeak communication
						switch (app_thingspeak_internal_comm_state) {
							case 0 : {
								{//Airpressure
									volatile float pressure = app_thingspeak_pressure;
									double dpressure = 0.0;
									dpressure = pressure;
									sprintf(app_thingspeak_pressureStr, (const char *)"%.1f", dpressure);
								}
								{//Temperature
									float temperature = app_thingspeak_temperature;
									double dtemperature = 0.0;
									if (temperature > 99.0) {
										temperature = 99.0;
									} else if (temperature < -99.0) {
										temperature = -99.0;
									}
									dtemperature = temperature;
									sprintf(app_thingspeak_temperatureStr, (const char *)"%.1f", dtemperature);
								}
								{//Humidtiy
									float humidity = app_thingspeak_humidity;
									double dhumidity = 0.0;
									if (humidity > 1500.0) {
										humidity = 1500.0;
									} else if (humidity < 0.0) {
										humidity = 0.0;
									}
									dhumidity = humidity;
									sprintf(app_thingspeak_humidityStr, (const char *)"%.1f", dhumidity);
								}
								{//CO2
									float co2 = app_thingspeak_CO2;
									double dco2 = 0.0f;
									if (co2 >= 1000.0) {
										co2 = 1000.0;
									} else if (co2 <= 0.0) {
										co2 = 0.0f;
									}
									dco2 = co2;
									sprintf(app_thingspeak_CO2Str, (const char *)"%.1f", dco2);
								}
								{//LiPo Voltage
									float voltage = app_thingspeak_LiPoVoltage;
									double dvoltage = 0.0f;
									if (voltage >= 5.0) {
										voltage = 5.0;
									} else if (voltage <= 0.0) {
										voltage = 0.0f;
									}
									dvoltage = voltage;
									sprintf(app_thingspeak_LiPoVoltageStr, (const char *)"%.2f", dvoltage);
								}
								{//Reserve1..3
									sprintf(app_thingspeak_reserve1Str, (const char *)"%.1f", (double)app_thingspeak_res1);
									sprintf(app_thingspeak_reserve2Str, (const char *)"%.1f", (double)app_thingspeak_res2);
									sprintf(app_thingspeak_reserve3Str, (const char *)"%.1f", (double)app_thingspeak_res3);
								}

								sprintf(app_thingspeak_get_string, 
											"GET https://api.thingspeak.com/update?api_key=CHANGEME&field1=%s&field2=%s&field3=%s&field4=%s&field5=%s&field6=%s&field7=%s&field8=%s\r\n",
											app_thingspeak_temperatureStr, app_thingspeak_pressureStr, app_thingspeak_humidityStr, 
											app_thingspeak_CO2Str, 
											app_thingspeak_LiPoVoltageStr, 
											app_thingspeak_reserve1Str, app_thingspeak_reserve2Str, app_thingspeak_reserve3Str);
								app_thingspeak_get_string_cnt = 0;
								app_thingspeak_get_string_cnt_max = strlen(app_thingspeak_get_string);
								app_thingspeak_internal_comm_state = 1;
								break;
							}
							case 1 : {
								unsigned int cnt = 0;
								while (1) {
									unsigned char data = 0;
									if (app_thingspeak_get_string_cnt >= app_thingspeak_get_string_cnt_max) {
										write_timer(&app_thingspeak_timeout, APP_THINGSPEAK_SEND_TIMEOUT);
										app_thingspeak_internal_comm_state = 2;
										break;
									}
									data = app_thingspeak_get_string[app_thingspeak_get_string_cnt];
									app_thingspeak_get_string_cnt++;
									if (ringBuffer_addItem(&myRingBuffer_app_thingspeak_tx, data) != -1) {
									} else {
										app_thingspeak_missed_tx_char++;
									}
									
									cnt++;
									if (cnt >= 16) {
										cnt = 0;
										break;
									}
								}
								break;
							}
							case 2 : {
								//The other side will close the connection, so we just wait. If not then this timeout will close it.
								//The answer does not matter, so that is received but not really processed
								if (read_timer(&app_thingspeak_timeout) == 0) {
									TransportState = TRANSPORT_CLOSE;
								}
							}
							default : {
								app_thingspeak_internal_comm_state = 0;
								break;
							}
						}
					}

					break;
				}
    			case TRANSPORT_CLOSE: {
					unsigned char data = 0;
			        TCPDisconnect(app_thingspeak_socket);
			        app_thingspeak_socket = INVALID_SOCKET;

					while (ringBuffer_getItem(&myRingBuffer_app_thingspeak_tx, &data) != 0);
					while (ringBuffer_getItem(&myRingBuffer_app_thingspeak_rx, &data) != 0);
			
			        TransportState = TRANSPORT_HOME;
			        break;
				}
				default : {
					TransportState = TRANSPORT_HOME;
					break;
				}
			}
		}
	}
}

void isr_app_thingspeak_1ms(void) {
	do_app_thingspeak_1ms = 1;
}

void app_thingspeak_send_measurement(float temperature, float pressure, float humidity, float CO2, float LiPoVoltage, float res1, float res2, float res3) {
	app_thingspeak_temperature = temperature;
	app_thingspeak_pressure = pressure;
	app_thingspeak_humidity = humidity;
	app_thingspeak_CO2 = CO2;
	app_thingspeak_LiPoVoltage = LiPoVoltage;
	app_thingspeak_res1 = res1;
	app_thingspeak_res2 = res2;
	app_thingspeak_res3 = res3;
	app_thingspeak_trigger = 1;
}
