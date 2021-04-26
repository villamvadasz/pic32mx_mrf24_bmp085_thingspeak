#ifndef _SERIAL_WIFI_H_
#define _SERIAL_WIFI_H_

	extern void init_serial_wifi(void);
	extern void deinit_serial_wifi(void);
	extern void do_serial_wifi(void);

	extern int isCharInBuffer_wifi(void);
	extern int getChar_wifi(void);
	extern void putChar_wifi(unsigned char data);

#endif
