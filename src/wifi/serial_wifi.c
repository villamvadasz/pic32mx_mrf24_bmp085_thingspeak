#include "serial_wifi.h"
#include "c_serial_wifi.h"

#include "k_stdtype.h"
#include "ringBuffer.h"
#include "mal.h"

RingBuffer myRingBuffer_wifi_tx;
unsigned char wifi_tx[TX_LEN_WIFI];
RingBuffer myRingBuffer_wifi_rx;
unsigned char wifi_rx[RX_LEN_WIFI];

unsigned long missedTxCharWifi = 0;
unsigned long missedRxCharWifi = 0;

int isCharOutBuffer_wifi(void);

#include "tcpip.h"

UDP_PORT         serverPort = 9756;    // server port
UDP_SOCKET       udpSkt;        // communication handle
extern unsigned char ReceivedDataBuffer[64];
extern unsigned char ToSendDataBuffer[64];


void init_serial_wifi(void) {
	ringBuffer_initBuffer(&myRingBuffer_wifi_tx, wifi_tx, sizeof(wifi_tx) / sizeof(*wifi_tx));
	ringBuffer_initBuffer(&myRingBuffer_wifi_rx, wifi_rx, sizeof(wifi_rx) / sizeof(*wifi_rx));

	// UDP open
	udpSkt = UDPOpen(serverPort, 0, 0);	}

void deinit_serial_wifi(void) {
	UDPClose(udpSkt);
}

void do_serial_wifi(void) {
	INT nBytes = 0;
    if (udpSkt == INVALID_UDP_SOCKET) {
	} else {
		{
			if (isCharOutBuffer_wifi() != -1) {
				unsigned char data = 0;
				uint32 i = 0;
				memset(ToSendDataBuffer, 0x00 , 64);
				while (ringBuffer_getItem(&myRingBuffer_wifi_tx, &data) != 0) {
					ToSendDataBuffer[1 + i] = data;
					i++;
					if (i >= 63) {
						break;
					}
				}
				ToSendDataBuffer[0] = i;

				{
					UINT txLen = 0;
					txLen = 64;
					while(nBytes < txLen)
					{
						StackTask();
						nBytes = UDPIsPutReady(udpSkt);
					}	
					
					nBytes = UDPPutArray( (UINT8*)ToSendDataBuffer, txLen);
					UDPFlush();	
				}
			}
		}
		{
			INT avlBytes = 0;
			avlBytes = UDPIsGetReady(udpSkt);
			if(avlBytes >= sizeof(ReceivedDataBuffer)) {
				// PC application is pumping more data than device can handle.
				UDPFlush();	
			} else {
				if(avlBytes)  {
					nBytes = UDPGetArray((BYTE*)ReceivedDataBuffer, avlBytes ); 		  		
					if(nBytes) {
						unsigned char data = 0;
						uint32 i = ReceivedDataBuffer[0];
						uint32 j = 0;
						while (i) {
							data = ReceivedDataBuffer[1 + j];
							if (ringBuffer_addItem(&myRingBuffer_wifi_rx, data) != -1) {
							} else {
								 missedRxCharWifi++;
							}					
							i--;
							j++;
						}
					}					 
				}			
			}	
		}
	}
}

int isCharInBuffer_wifi(void) {
	int result = -1;
	unsigned int cnt = ringBuffer_getFillness(&myRingBuffer_wifi_rx);
	if (cnt != 0) {
		result = cnt;
	}
	return result;
}

int isCharOutBuffer_wifi(void) {
	int result = -1;
	unsigned int cnt = ringBuffer_getFillness(&myRingBuffer_wifi_tx);
	if (cnt != 0) {
		result = cnt;
	}
	return result;
}

int getChar_wifi(void) {
	int result = -1;
	unsigned char data = 0;
	if (ringBuffer_getItem(&myRingBuffer_wifi_rx, &data) != 0) {
		result = data;
	}
	return result;
}

void putChar_wifi(unsigned char data) {
	if (ringBuffer_addItem(&myRingBuffer_wifi_tx, data) != -1) {
	} else {
		missedTxCharWifi++;
	}
}
