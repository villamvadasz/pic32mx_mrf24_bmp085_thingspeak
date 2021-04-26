#ifndef _WIFI_H_
#define _WIFI_H_

    #include "k_stdtype.h"

    extern uint8 wifi_is_connected(void);

	extern void init_wifi(void);
	extern void do_wifi(void);
	extern void deinit_wifi(void);
	extern void isr_wifi_1ms(void);
	extern void isr_eint_wifi(void);

#endif