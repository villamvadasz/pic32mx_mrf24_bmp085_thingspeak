#define __TICK_C_

#include "tcpip.h"

#include "mal.h"

// Internal counter to store Ticks.  This variable is incremented in an ISR and
// therefore must be marked volatile to prevent the compiler optimizer from
// reordering code to use this value in the main context while interrupts are
// disabled.
static volatile uint32_t dwInternalTicks = 0;
static volatile uint32_t dwInternalTicks_DIV256 = 0;
static volatile uint32_t dwInternalTicks_DIV65536 = 0;

void TickInit(void) {
	//Empty function
}

uint32_t TickGet(void) {
	uint32_t result = 0;
	lock_isr();
	result = dwInternalTicks;
	unlock_isr();
	return result;
}

uint32_t TickGetDiv256(void) {
	uint32_t result = 0;
	lock_isr();
	result = dwInternalTicks_DIV256;
	unlock_isr();
	return result;
}

uint32_t TickGetDiv64K(void) {
	uint32_t result = 0;
	lock_isr();
	result = dwInternalTicks_DIV65536;
	unlock_isr();
	return result;
}

void isr_wifi_tick_1ms(void) {
    dwInternalTicks++;
	{
		static unsigned int dwInternalTicks_DIV256_cnt = 0;
		dwInternalTicks_DIV256_cnt++;
		if (dwInternalTicks_DIV256_cnt >= 256) {
			dwInternalTicks_DIV256_cnt = 0;
	    	dwInternalTicks_DIV256++;
		}
	}
	{
		static unsigned int dwInternalTicks_DIV65536_cnt = 0;
		dwInternalTicks_DIV65536_cnt++;
		if (dwInternalTicks_DIV65536_cnt >= 65536) {
			dwInternalTicks_DIV65536_cnt = 0;
	    	dwInternalTicks_DIV65536++;
		}
	}
}
