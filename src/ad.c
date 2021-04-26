#include <stdio.h>
#include <string.h>

#include "ad.h"
#include "c_ad.h"

#include "mal.h"

#define E_MEASUREMENT_TRIS TRISFbits.TRISF1
#define E_MEASUREMENT_PORT PORTFbits.RF1
#define E_MEASUREMENT_LAT LATFbits.LATF1

uint16 adResults[AD_CHANNEL_NUM];

uint8 doAd10ms = 0;
uint8 ad_currentChannel = 0;
uint32 ad_extend_sampling_time = 0;

void init_ad(void) {
	memset(adResults, 0x00, sizeof(adResults));

	E_MEASUREMENT_TRIS = 0;
	E_MEASUREMENT_LAT = 0;

	#ifdef __32MX440F256H__
		AD1PCFG = 0xFFFF;
		//E_MEASUREMENT LOW LiPo AN12
		AD1PCFGbits.PCFG12 = 0;
	#else
		#ifdef __32MX795F512H__
			AD1PCFG = 0xFFFF;
			//E_MEASUREMENT LOW LiPo AN12
			AD1PCFGbits.PCFG12 = 0;
		#else
			#error TODO Implement
		#endif
	#endif

	AD1CON1CLR = 0x8000;    // disable ADC before configuration

	//Tad min 65ns or 15MHz
	//PB      25ns    40MHz 
	//ADCS Tad 4 * 25ns = 100ns
	//SAMC Tsamp 31 * 100ns = 3100ns
	
	AD1CON1 = 0x00E0;       // internal counter ends sampling and starts conversion (auto-convert), manual sample
	AD1CON2 = 0;            // AD1CON2<15:13> set voltage reference to pins AVSS/AVDD
	AD1CON3 = 0x1F01;       // SAMC 31Tad, ADCS 4 * Tpb = Tad
	AD1CON1SET = 0x8000;    // Enable ADC

	ad_currentChannel = 12;
	AD1CHSbits.CH0SA = ad_currentChannel;
	AD1CON1bits.SAMP = 1;
}

void do_ad(void) {
	if (doAd10ms) {
		doAd10ms = 0;
		{
			if ((AD1CON1bits.SAMP == 0) && (AD1CON1bits.DONE == 1)) {
				if (ad_extend_sampling_time != 0) {
					ad_extend_sampling_time--;
	                AD1CHSbits.CH0SA = ad_currentChannel;
					AD1CON1bits.SAMP = 1;
				} else {
					switch (ad_currentChannel) {
						case 12 : {
							ad_extend_sampling_time = 100;
							adResults[0] = ADC1BUF0;
							ad_currentChannel = 12;
							break;
						}
						default : { 
							ad_extend_sampling_time = 100;
							adResults[0] = ADC1BUF0;
							ad_currentChannel = 12;
							break;
						}
					}
	                AD1CHSbits.CH0SA = ad_currentChannel;
					AD1CON1bits.SAMP = 1;
				}
			}
		}
	}
}

void isr_ad_1ms(void) {
	static uint8 doAd10msCnt = 0;
	doAd10msCnt ++;
	if (doAd10msCnt >= 10) {
		doAd10msCnt = 0;
		doAd10ms = 1;
	}
}

uint16 getAd(unsigned char ch) {
	uint16 result = 0;
	if (ch < AD_CHANNEL_NUM) {
		result = adResults[ch];
	}
	return result;
}
