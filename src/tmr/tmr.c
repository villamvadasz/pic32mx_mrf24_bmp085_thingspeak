#include <string.h>
#include <stdio.h>
#include "mal.h"
#include "tmr.h"
#include "c_tmr.h"

#include "c_main.h"
#include "k_stdtype.h"
#include "c_isr.h"

#define T1_ON                           (1 << _T1CON_ON_POSITION)       /* Timer1 ON */
#define T1_OFF                          (0)

// Stop-in-idle control - values are mutually exclusive
#define T1_IDLE_STOP                    (1 << _T1CON_SIDL_POSITION)     /* stop during idle */
#define T1_IDLE_CON                     (0)                             /* operate during idle */

// Asynchronous write control - values are mutually exclusive
#define T1_TMWDIS_ON                    (1 << _T1CON_TWDIS_POSITION)    /* Asynchronous Write Disable */
#define T1_TMWDIS_OFF                   (0)

// Timer gate control - values are mutually exclusive
#define T1_GATE_ON                      (1 << _T1CON_TGATE_POSITION)    /* Timer Gate accumulation mode ON */
#define T1_GATE_OFF                     (0)

// Timer prescaler control - values are mutually exclusive
#define T1_PS_1_256                     (3 << _T1CON_TCKPS_POSITION)    /* Prescaler 1:256 */
#define T1_PS_1_64                      (2 << _T1CON_TCKPS_POSITION)    /*           1:64 */
#define T1_PS_1_8                       (1 << _T1CON_TCKPS_POSITION)    /*           1:8 */
#define T1_PS_1_1                       (0)                             /*           1:1 */

// Sync option - values are mutually exclusive
#define T1_SYNC_EXT_ON                  (1 << _T1CON_TSYNC_POSITION)    /* Synch external clk input */
#define T1_SYNC_EXT_OFF                 (0)

// Source selection - values are mutually exclusive
#define T1_SOURCE_EXT                   (1 << _T1CON_TCS_POSITION)      /* External clock source */
#define T1_SOURCE_INT                   (0)                             /* Internal clock source */

// Interrupt on/off - values are mutually exclusive
#define T1_INT_ON                       (1 << 15)
#define T1_INT_OFF                      (0)

// Interrupt priority - values are mutually exclusive
#define T1_INT_PRIOR_7                  (7) // Timer int priority 7
#define T1_INT_PRIOR_6                  (6) // Timer int priority 6
#define T1_INT_PRIOR_5                  (5) // Timer int priority 5
#define T1_INT_PRIOR_4                  (4) // Timer int priority 4
#define T1_INT_PRIOR_3                  (3) // Timer int priority 3
#define T1_INT_PRIOR_2                  (2) // Timer int priority 2
#define T1_INT_PRIOR_1                  (1) // Timer int priority 1
#define T1_INT_PRIOR_0                  (0) // Timer int priority 0

// Interrupt sub-priority - values are mutually exclusive
#define T1_INT_SUB_PRIOR_3              (3 << 4) // Timer int sub priority 3
#define T1_INT_SUB_PRIOR_2              (2 << 4) // Timer int sub priority 2
#define T1_INT_SUB_PRIOR_1              (1 << 4) // Timer int sub priority 1
#define T1_INT_SUB_PRIOR_0              (0 << 4) // Timer int sub priority 0

#define T2_ON                           (1 << _T2CON_ON_POSITION)       /* Timer2 ON */
#define T2_OFF                          (0)
        
// Stop-in-idle control - values are mutually exclusive
#define T2_IDLE_STOP                    (1 << _T2CON_SIDL_POSITION)     /* stop during idle */
#define T2_IDLE_CON                     (0)                             /* operate during idle */

// Timer gate control - values are mutually exclusive
#define T2_GATE_ON                      (1 << _T2CON_TGATE_POSITION)    /* Timer Gate accumulation mode ON */
#define T2_GATE_OFF                     (0)

// Prescale values - values are mutually exclusive
#define T2_PS_1_256                     (7 << _T2CON_TCKPS_POSITION)    /* Prescaler 1:256 */
#define T2_PS_1_64                      (6 << _T2CON_TCKPS_POSITION)    /*           1:64 */
#define T2_PS_1_32                      (5 << _T2CON_TCKPS_POSITION)    /*           1:32 */
#define T2_PS_1_16                      (4 << _T2CON_TCKPS_POSITION)    /*           1:16 */
#define T2_PS_1_8                       (3 << _T2CON_TCKPS_POSITION)    /*           1:8 */
#define T2_PS_1_4                       (2 << _T2CON_TCKPS_POSITION)    /*           1:4 */
#define T2_PS_1_2                       (1 << _T2CON_TCKPS_POSITION)    /*           1:2 */
#define T2_PS_1_1                       (0)                             /*           1:1 */

// 32-bit or 16-bit - values are mutually exclusive
#define T2_32BIT_MODE_ON                (1 << _T2CON_T32_POSITION)      /* Enable 32-bit mode */
#define T2_32BIT_MODE_OFF               (0)

// Sync external clock option - values are mutually exclusive
#define T2_SOURCE_EXT                   (1 << _T2CON_TCS_POSITION)      /* External clock source */
#define T2_SOURCE_INT                   (0)                             /* Internal clock source */

// Interrupt on/off - values are mutually exclusive
#define T2_INT_ON                       (1 << 15)       /* T2 Interrupt Enable */
#define T2_INT_OFF                      (0)

// Interrupt priority - values are mutually exclusive
#define T2_INT_PRIOR_7                  (7)
#define T2_INT_PRIOR_6                  (6)
#define T2_INT_PRIOR_5                  (5)
#define T2_INT_PRIOR_4                  (4)
#define T2_INT_PRIOR_3                  (3)
#define T2_INT_PRIOR_2                  (2)
#define T2_INT_PRIOR_1                  (1)
#define T2_INT_PRIOR_0                  (0)

// Interrupt sub-priority - values are mutually exclusive
#define T2_INT_SUB_PRIOR_3              (3 << 4)
#define T2_INT_SUB_PRIOR_2              (2 << 4)
#define T2_INT_SUB_PRIOR_1              (1 << 4)
#define T2_INT_SUB_PRIOR_0              (0 << 4)


#define T4_ON                           (1 << _T4CON_ON_POSITION)       /* Timer1 ON */
#define T4_OFF                          (0)

// Stop-in-idle control - values are mutually exclusive
#define T4_IDLE_STOP                    (1 << _T4CON_SIDL_POSITION)     /* stop during idle */
#define T4_IDLE_CON                     (0)                             /* operate during idle */

// Asynchronous write control - values are mutually exclusive
#define T4_TMWDIS_ON                    (1 << _T4CON_TWDIS_POSITION)    /* Asynchronous Write Disable */
#define T4_TMWDIS_OFF                   (0)

// Timer gate control - values are mutually exclusive
#define T4_GATE_ON                      (1 << _T4CON_TGATE_POSITION)    /* Timer Gate accumulation mode ON */
#define T4_GATE_OFF                     (0)

// Timer prescaler control - values are mutually exclusive
#define T4_PS_1_256                     (7 << _T4CON_TCKPS_POSITION)    /* Prescaler 1:256 */
#define T4_PS_1_64                      (6 << _T4CON_TCKPS_POSITION)    /*           1:64 */
#define T4_PS_1_32                      (5 << _T4CON_TCKPS_POSITION)    /*           1:32 */
#define T4_PS_1_16                      (4 << _T4CON_TCKPS_POSITION)    /*           1:16 */
#define T4_PS_1_8                       (3 << _T4CON_TCKPS_POSITION)    /*           1:8 */
#define T4_PS_1_4                       (2 << _T4CON_TCKPS_POSITION)    /*           1:4 */
#define T4_PS_1_2                       (1 << _T4CON_TCKPS_POSITION)    /*           1:2 */
#define T4_PS_1_1                       (0)                             /*           1:1 */

// Sync option - values are mutually exclusive
#define T4_SYNC_EXT_ON                  (1 << _T4CON_TSYNC_POSITION)    /* Synch external clk input */
#define T4_SYNC_EXT_OFF                 (0)

// Source selection - values are mutually exclusive
#define T4_SOURCE_EXT                   (1 << _T4CON_TCS_POSITION)      /* External clock source */
#define T4_SOURCE_INT                   (0)                             /* Internal clock source */

// Interrupt on/off - values are mutually exclusive
#define T4_INT_ON                       (1 << 15)
#define T4_INT_OFF                      (0)

// Interrupt priority - values are mutually exclusive
#define T4_INT_PRIOR_7                  (7) // Timer int priority 7
#define T4_INT_PRIOR_6                  (6) // Timer int priority 6
#define T4_INT_PRIOR_5                  (5) // Timer int priority 5
#define T4_INT_PRIOR_4                  (4) // Timer int priority 4
#define T4_INT_PRIOR_3                  (3) // Timer int priority 3
#define T4_INT_PRIOR_2                  (2) // Timer int priority 2
#define T4_INT_PRIOR_1                  (1) // Timer int priority 1
#define T4_INT_PRIOR_0                  (0) // Timer int priority 0

// Interrupt sub-priority - values are mutually exclusive
#define T4_INT_SUB_PRIOR_3              (3 << 4) // Timer int sub priority 3
#define T4_INT_SUB_PRIOR_2              (2 << 4) // Timer int sub priority 2
#define T4_INT_SUB_PRIOR_1              (1 << 4) // Timer int sub priority 1
#define T4_INT_SUB_PRIOR_0              (0 << 4) // Timer int sub priority 0



uint32 globalTime = 0;
uint32 globalTimeUs = 0;
static volatile uint32 delayCnt = 0;
static volatile uint8 delayCntLock = 0;
static Timer *ptrList[TIMERCNT];
#define SIZEOFPTR (sizeof(ptrList)/sizeof(*ptrList))

void init_tmr (void) {
	uint8 x = 0;

	#ifndef TMR_USE_TMR4_1MS
		//TMR1 1ms
		T1CON = ((T1_ON | T1_SOURCE_INT | T1_PS_1_256)&~(T1_ON));
		TMR1 = 0;
		PR1 = (PR1_CONFIG);
		T1CONSET =((T1_ON | T1_SOURCE_INT | T1_PS_1_256)&(T1_ON));

		IFS0CLR = _IFS0_T1IF_MASK;
		IPC1CLR = _IPC1_T1IP_MASK, IPC1SET = (((T1_INT_ON | ISR_IPLV_TMR1) & 7) << _IPC1_T1IP_POSITION);
		IPC1CLR = _IPC1_T1IS_MASK, IPC1SET = ((((T1_INT_ON | ISR_IPLV_TMR1) >> 4) & 3) << _IPC1_T1IS_POSITION);
		IEC0CLR = _IEC0_T1IE_MASK, IEC0SET = (((T1_INT_ON | ISR_IPLV_TMR1) >> 15) << _IEC0_T1IE_POSITION);
	#endif
	#ifdef TMR_USE_TMR4_1MS
		//TMR4 1ms
		OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, PR1_CONFIG);
		ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_2);
	#endif
	#ifdef TMR_USE_TMR1_SOSC
		OSCCONbits.SOSCEN = 1;
		OpenTimer1(T1_ON | T1_SOURCE_EXT | T1_PS_1_1, 32768);
		ConfigIntTimer1(T1_INT_ON | ISR_IPLV_TMR1);
	#endif

	#ifndef TMR_DISABLE_TMR2_100US
		//TMR2 100uS
		T2CON = ((T2_ON | T2_SOURCE_INT | T2_PS_1_16)&~(T2_ON));
		TMR2 = 0;
		PR2 = (PR2_CONFIG);
		T2CONSET =((T2_ON | T2_SOURCE_INT | T2_PS_1_16)&(T2_ON));

		IFS0CLR = _IFS0_T2IF_MASK;
		IPC2CLR = _IPC2_T2IP_MASK, IPC2SET = (((T2_INT_ON | ISR_IPLV_TMR2) & 7) << _IPC2_T2IP_POSITION);
		IPC2CLR = _IPC2_T2IS_MASK, IPC2SET = ((((T2_INT_ON | ISR_IPLV_TMR2) >> 4) & 3) << _IPC2_T2IS_POSITION);
		IEC0CLR = _IEC0_T2IE_MASK, IEC0SET = (((T2_INT_ON | ISR_IPLV_TMR2) >> 15) << _IEC0_T2IE_POSITION);

	#endif

	#ifdef TMR_USE_TMR4_10US
		//TMR4 10uS
		T4CON = ((T4_ON | T4_SOURCE_INT | T4_PS_1_8)&~(T4_ON));
		TMR4 = 0;
		PR4 = (PR4_CONFIG);
		T4CONSET = ((T4_ON | T4_SOURCE_INT | T4_PS_1_8)&(T4_ON));

		#ifndef TMR_USE_TMR4_10US_DISABLE_INTERRUPT
			IFS0CLR = _IFS0_T4IF_MASK;
			IPC4CLR = _IPC4_T4IP_MASK, IPC4SET = (((T4_INT_ON | ISR_IPLV_TMR4) & 7) << _IPC4_T4IP_POSITION);
			IPC4CLR = _IPC4_T4IS_MASK, IPC4SET = ((((T4_INT_ON | ISR_IPLV_TMR4) >> 4) & 3) << _IPC4_T4IS_POSITION);
			IEC0CLR = _IEC0_T4IE_MASK, IEC0SET = (((T4_INT_ON | ISR_IPLV_TMR4) >> 15) << _IEC0_T4IE_POSITION);
		#endif
	#endif
		
	for (x = 0; x < SIZEOFPTR; x++) {
		ptrList[x] = NULL;
	}
}

void deinit_tmr (void) {
	uint8 x = 0;

	#ifndef TMR_USE_TMR4_1MS
		//TMR1 1ms
		T1CON = ((T1_OFF | T1_SOURCE_INT | T1_PS_1_256)&~(T1_ON));
		TMR1 = 0;
		PR1 = (0);
		T1CONSET=((T1_OFF | T1_SOURCE_INT | T1_PS_1_256)&(T1_ON));
	#endif
	#ifdef TMR_USE_TMR4_1MS
		//TMR4 1ms
		OpenTimer4(T4_OFF, 0);
	#endif
	#ifdef TMR_USE_TMR1_SOSC
		OSCCONbits.SOSCEN = 0;
		OpenTimer1(T1_OFF, 0);
	#endif

	#ifndef TMR_DISABLE_TMR2_100US
		//TMR2 100uS
		T2CON = ((T2_OFF)&~(T2_ON));
		TMR2 = 0;
		PR2 = (0);
		T2CONSET=((T2_OFF)&(T2_ON));
	#endif

	#ifdef TMR_USE_TMR4_10US
		//TMR4 10uS
		T4CON = ((T4_OFF | T4_SOURCE_INT | T4_PS_1_8)&~(T4_ON));
		TMR4 = 0;
		PR4 = (0);
		T4CONSET=((T4_OFF | T4_SOURCE_INT | T4_PS_1_8)&(T4_ON));

		#ifndef TMR_USE_TMR4_10US_DISABLE_INTERRUPT
			IFS0CLR = _IFS0_T4IF_MASK;
			IPC1CLR = _IPC4_T4IP_MASK, IPC4SET = (((T4_INT_OFF | ISR_IPLV_TMR4) & 7) << _IPC4_T4IP_POSITION);
			IPC1CLR = _IPC4_T4IS_MASK, IPC4SET = ((((T4_INT_OFF | ISR_IPLV_TMR4) >> 4) & 3) << _IPC4_T4IS_POSITION);
			IEC0CLR = _IEC0_T4IE_MASK, IEC0SET = (((T4_INT_OFF | ISR_IPLV_TMR4) >> 15) << _IEC0_T4IE_POSITION);
		#endif
	#endif
		
	for (x = 0; x < SIZEOFPTR; x++) {
		ptrList[x] = NULL;
	}
}

void do_tmr(void) {
}

void delayms(uint32 dt) {
	uint16 temp1 = 0;
	uint16 temp2 = 1;
	delayCntLock = 1;
	delayCnt = dt;
	delayCntLock = 0;
	while (1) {
		temp1 = delayCnt;
		temp2 = delayCnt;
		if (temp1 == temp2) {
			if (temp1 == 0) {
				break;
			}
		}
	}
}

void init_timer(Timer *ptr) {
	remove_timer(ptr);
	add_timer(ptr);
	write_timer(ptr, 0);
}

void add_timer(Timer *ptr) {
	uint8 x = 0;
	lock_isr();
	for (x = 0; x < SIZEOFPTR; x++) {
		if (ptrList[x] == NULL) {
			ptrList[x] = ptr;
			break;
		}
	}
	unlock_isr();
}

void remove_timer(Timer *ptr) {
	uint8 x = 0;
	lock_isr();
	for (x = 0; x < SIZEOFPTR; x++) {
		if (ptrList[x] == ptr) {
			ptrList[x] = NULL;
			break;
		}
	}
	unlock_isr();
}

uint32 read_timer(const Timer *ptr) {
	uint32 result = 0;
	if (ptr != NULL) {
		lock_isr();
		result = *ptr;
		unlock_isr();	
	}
	return result;
}

void write_timer(Timer *ptr, uint32 newValue) {
	if (ptr != NULL) {
		lock_isr();
		*ptr = newValue;
		unlock_isr();	
	}
}

void setTimer(uint32 d) {
	delayCntLock = 1;
	delayCnt = d;
	delayCntLock = 0;
}

uint32 getTimer(void) {
	uint32 temp1 = 0;
	uint32 temp2 = 1;
	while (temp1 != temp2) {
		temp1 = delayCnt;
		temp2 = delayCnt;
	}
	return temp2;
}

void isr_tmr4(void) { //xxus
	TMR4_FUNCTIONS();
}

void isr_tmr3(void) { //custom
	TMR3_FUNCTIONS();
}

void isr_tmr2(void) { //100us
	globalTimeUs += 100;
	TMR2_FUNCTIONS();
}

void isr_tmr1(void) { //1ms
	uint8 x = 0;
	static uint8 ms10Cnt = 0;
	static uint8 ms100Cnt = 0;
	static uint8 ms250Cnt = 0;
	static uint16 ms500Cnt = 0;
	static uint16 ms1000Cnt = 0;
	
	ClearWDT();

	globalTime++;

	TMR1_FUNCTIONS();

	if (delayCntLock == 0) {
		if (delayCnt != 0) {
			delayCnt--;
		}
	}

	ms10Cnt ++;
	if (ms10Cnt == 10) {
		ms10Cnt = 0;
	}

	ms100Cnt ++;
	if (ms100Cnt == 100) {
		ms100Cnt = 0;
	}
	
	ms250Cnt ++;
	if (ms250Cnt == 250) {
		ms250Cnt = 0;
	}

	ms500Cnt ++;
	if (ms500Cnt == 500) {
		ms500Cnt = 0;
	}

	ms1000Cnt ++;
	if (ms1000Cnt == 1000) {
		ms1000Cnt = 0;
	}

	for (x = 0; x < SIZEOFPTR; x++) {
		if (ptrList[x] != NULL) {
			if (*(ptrList[x]) != 0) {
				(*(ptrList[x]))--;
			}
		}
	}
}

uint32 getGlobalTime(void) {
	uint32 result = 0;
	lock_isr();
	result = globalTime;
	unlock_isr();
	return result;
}

uint32 getGlobalTimeUs(void) {
	uint32 result = 0;
	lock_isr();
	result = globalTimeUs;
	unlock_isr();
	return result;
}
