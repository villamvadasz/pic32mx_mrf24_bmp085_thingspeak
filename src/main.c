#include "main.h"
#include "c_main.h"

#include "k_stdtype.h"
#include "mal.h"
#include "version.h"
#include "sleep.h"
#include "tmr.h"
#include "iic_master_multi.h"
#include "iic_master.h"
#include "bme280.h"
#include "ccs811.h"
#include "sht31d.h"
#include "stackmeasure.h"
#include "isr.h"
#include "bootloader_interface.h"

#include "c_app.h"

#include "ad.h"
#include "app.h"
#include "eep_manager.h"
#include "isr.h"
#include "dee.h"
#include "wifi.h"

#define SW_YEAR 0x2021
#define SW_MONTH 0x04
#define SW_DAY 0x23
#define SW_TYPE TYPE_OLIMEX_WIFI_THINGSPEAK
#define SW_VERSION 0x0100

SoftwareIdentification softwareIdentification = {SW_YEAR, SW_MONTH, SW_DAY, SW_VERSION, SW_TYPE};
unsigned char VERSION_ID[] = "olimex_wifi_thingspeak_1_0_0";
const char VERSION_DATE[]  __attribute__ ((address(0x9D010100))) = __DATE__;
const char VERSION_TIME[]  __attribute__ ((address(0x9D010120))) = __TIME__;
const char VERSION_ID_FIX[]  __attribute__ ((address(0x9D010140))) = "olimex_wifi_thingspeak_1_0_0";

volatile unsigned char do_loopCnt = 0;
unsigned long loopCntTemp = 0;
unsigned long loopCnt = 0;
unsigned int tick_count = 0;

unsigned long loopCntHistory[60];
unsigned int loopCntHistoryCnt = 0;


int main (void) {

	init_mal();

	init_stackmeasure();

	init_ad();

	init_dee();
	init_eep_manager();

	init_tmr(); //this should be the first beceaus it clears registered timers.

	init_iic_master();
	init_iic_master_multi();
	init_bme280();
	init_ccs811();
	init_sht31d();
	init_app();
	init_isr();

	init_wifi();
	do_loopCnt = 0;

	bootloader_interface_clearRequest();
	
	while (1) {
		if (do_loopCnt) {
			do_loopCnt = 0;
			loopCnt = loopCntTemp; //Risk is here that interrupt corrupts the value, but it is taken
			loopCntHistory[loopCntHistoryCnt] = loopCnt;
			loopCntHistoryCnt++;
			loopCntHistoryCnt %= ((sizeof(loopCntHistory)) / (sizeof(*loopCntHistory)));
			loopCntTemp = 0;
			if (loopCnt < 1000) { //1run/ms
				/*while (1) {
					Nop();
					ERROR_LED = 1;
				}*/
			}
		}

		do_stackmeasure();
		do_ad();
		do_eep_manager();
		do_app();
		do_tmr();
		do_dee();
		do_wifi();
		do_iic_master();
		do_iic_master_multi();
		do_bme280();
		do_ccs811();
		do_sht31d();

		loopCntTemp++;
	}
	return 0;
}

void isr_main_1ms(void) {
	static uint16 loopCntTmr = 0;

	tick_count++;

	loopCntTmr ++;
	if (loopCntTmr == 1000) {
		loopCntTmr = 0;
		do_loopCnt = 1;
	}

	isr_ad_1ms();
	isr_eep_manager_1ms();
	isr_ad_1ms();
	//isr_iic_master_1ms(); //Use on of 1ms, 100us or 10us
	isr_iic_master_multi_1ms();
	isr_bme280_1ms();
	isr_ccs811_1ms();
	isr_sht31d_1ms();
	isr_app_1ms();
	isr_dee_1ms();
	isr_wifi_1ms();
}

void isr_main_100us(void) {
	isr_app_100us();
	isr_iic_master_100us(); //Use on of 1ms, 100us or 10us
}

void isr_main_custom(void) {
	isr_app_custom();
}

void isr_main_10us(void) {
	//isr_iic_master_10us(); //Use on of 1ms, 100us or 10us
}
