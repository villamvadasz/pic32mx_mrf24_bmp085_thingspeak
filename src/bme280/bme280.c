#include <math.h>
#include "bme280.h"
#include "c_bme280.h"
#include "bme280_conversion.h"

#include "iic_master_multi.h"
#include "mal.h"
#include "k_stdtype.h"
#include "tmr.h"

#ifndef BME280_ADDRESS
	//#define BME280_ADDRESS 0x77			//7bit address
	#define BME280_ADDRESS 0x76		//7bit address
#endif

#define BME280_MODE_SLEEP_BIT 0x0
#define BME280_MODE_FORCED_BIT 0x1
#define BME280_MODE_NORMAL_BIT 0x3

#if (BME280_OSS_H == 1)
	#define BME280_OSS_H_BIT 0x1
#endif
#if (BME280_OSS_H == 2)
	#define BME280_OSS_H_BIT 0x2
#endif
#if (BME280_OSS_H == 4)
	#define BME280_OSS_H_BIT 0x3
#endif
#if (BME280_OSS_H == 8)
	#define BME280_OSS_H_BIT 0x4
#endif
#if (BME280_OSS_H == 16)
	#define BME280_OSS_H_BIT 0x5
#endif


#if (BME280_OSS_P == 1)
	#define BME280_OSS_P_BIT 0x1
#endif
#if (BME280_OSS_P == 2)
	#define BME280_OSS_P_BIT 0x2
#endif
#if (BME280_OSS_P == 4)
	#define BME280_OSS_P_BIT 0x3
#endif
#if (BME280_OSS_P == 8)
	#define BME280_OSS_P_BIT 0x4
#endif
#if (BME280_OSS_P == 16)
	#define BME280_OSS_P_BIT 0x5
#endif


#if (BME280_OSS_T == 1)
	#define BME280_OSS_T_BIT 0x1
#endif
#if (BME280_OSS_T == 2)
	#define BME280_OSS_T_BIT 0x2
#endif
#if (BME280_OSS_T == 4)
	#define BME280_OSS_T_BIT 0x3
#endif
#if (BME280_OSS_T == 8)
	#define BME280_OSS_T_BIT 0x4
#endif
#if (BME280_OSS_T == 16)
	#define BME280_OSS_T_BIT 0x5
#endif

typedef enum _Bme280States {
	Bme280State_Init = 0,
	Bme280State_Calibration_1_Start,
	Bme280State_Calibration_1_StartPoll,
	Bme280State_Calibration_1,
	Bme280State_Calibration_1_Poll,
	Bme280State_Control,
	Bme280State_Control_Poll,
	Bme280State_Idle,
	Bme280State_StartConverion,
	Bme280State_StartConverion_Poll,
	Bme280State_WaitForResult_Address,
	Bme280State_WaitForResult_Address_Poll,
	Bme280State_WaitForResult,
	Bme280State_WaitForResult_Poll,
	Bme280State_ReadResult_Address,
	Bme280State_ReadResult_Address_Poll,
	Bme280State_ReadResult,
	Bme280State_ReadResult_Poll,
	Bme280State_CalculateTemp,
	Bme280State_CalculatePressure,
	Bme280State_CalculateHumidity,
} Bme280States;

unsigned short dig_T1 = 0; 		//0x88 0x89		
signed short dig_T2 = 0; 		//0x8A 0x8B
signed short dig_T3 = 0; 		//0x8C 0x8D

unsigned short dig_P1 = 0; 		//0x8E 0x8F
signed short dig_P2 = 0; 		//0x90 0x91
signed short dig_P3 = 0; 		//0x92 0x93

signed short dig_P4 = 0; 		//0x94 0x95
signed short dig_P5 = 0; 		//0x96 0x97
signed short dig_P6 = 0; 		//0x98 0x99
signed short dig_P7 = 0; 		//0x9A 0x9B
signed short dig_P8 = 0; 		//0x9C 0x9D
signed short dig_P9 = 0; 		//0x9E 0x9F

unsigned char dig_H1 = 0; 		//0xA1
signed short dig_H2 = 0; 		//0xE1 0xE2
unsigned char dig_H3 = 0; 		//0xE3
signed short dig_H4 = 0; 		//0xE4 0xE5
signed short dig_H5 = 0; 		//0xE5 0xE7
signed char dig_H6 = 0; 		//0xE7

uint32 UT = 0;
uint32 UP = 0;
uint32 UH = 0;

unsigned char bme280_addressTable[] = {0x88, 0x8A, 0x8C, 0x8E, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9A, 0x9C, 0x9E, 0xA1, 0xE1, 0xE3, 0xE4, 0xE5, 0xE7};
unsigned char bme280_sizeTable[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1};
unsigned char bme280_loadTable[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0};
void *        bme280_ptrTable[] = {&dig_T1, &dig_T2, &dig_T3, &dig_P1, &dig_P2, &dig_P3, &dig_P4, &dig_P5, &dig_P6, &dig_P7, &dig_P8, &dig_P9, &dig_H1, &dig_H2, &dig_H3, &dig_H4, &dig_H5, &dig_H6};
unsigned char bme280_loaderCnt = 0;

sint32 t_fine;

Bme280States bme280States = Bme280State_Init;
float resultTemp = 0.0;
float resultPressure = 0.0;
float resultAltitude = 0.0;
float resultHumidity = 0.0;
unsigned char bme280TempData[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8 do_bme280_1ms = 0;
Timer bme280_conversionTimer = 0;
uint32 bme280_conversionTimerValue = 100;
Timer bme280_samplingTimer = 0;
volatile uint32 resultPressureError = 0;
volatile uint32 iicStateMachineError = 0;

sint32 BME280_compensate_T_int32(sint32 adc_T);
uint32 BME280_compensate_P_int64(sint32 adc_P);
uint32 bme280_compensate_H_int32(sint32 adc_H);

void init_bme280(void) {
	bme280_conversionTimerValue = 1 + (2*BME280_OSS_T) + (2*BME280_OSS_P) + (2*BME280_OSS_H) + 1 + 5;   
	bme280States = Bme280State_Init;
	init_timer(&bme280_conversionTimer);
	init_timer(&bme280_samplingTimer);
}

void deinit_bme280(void) {
}

void do_bme280(void) {
	if (do_bme280_1ms) {
		do_bme280_1ms = 0;
		switch (bme280States) {
			case Bme280State_Init : {
				bme280_loaderCnt = 0;
				iicStateMachineError++;
				bme280States = Bme280State_Calibration_1_Start;
				break;
			}
			case Bme280State_Calibration_1_Start : {
				unsigned char address = bme280_addressTable[bme280_loaderCnt];
				bme280TempData[0] = address;
				IIC_Result retVal = iic_write_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 1, 0, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_Calibration_1_StartPoll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Calibration_1_StartPoll : {
				IIC_Result retVal = iic_getState_async_multi(BME280_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_Calibration_1;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Calibration_1 : {
				IIC_Result retVal = IIC_Result_Error;

				if (bme280_sizeTable[bme280_loaderCnt] == 2) {
					retVal = iic_read_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 2, BME280_FREQ);
				} else if (bme280_sizeTable[bme280_loaderCnt] == 1) {
					retVal = iic_read_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 1, BME280_FREQ);
				} else {
				}

				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_Calibration_1_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Calibration_1_Poll : {
				IIC_Result retVal = iic_getState_async_multi(BME280_IIC_MASTER_MULTI_USER);

				if (retVal == IIC_Result_OK) {
					if (bme280_sizeTable[bme280_loaderCnt] == 2) {
						if (bme280_loadTable[bme280_loaderCnt] == 0) {
							*((uint16 *)bme280_ptrTable[bme280_loaderCnt]) = (uint16) ((bme280TempData[1] << 8) | bme280TempData[0]);
						} else if (bme280_loadTable[bme280_loaderCnt] == 1) {//H4
							*((uint16 *)bme280_ptrTable[bme280_loaderCnt]) = (uint16) ((bme280TempData[0] << 4) | (bme280TempData[1] & 0x0F));
						} else if (bme280_loadTable[bme280_loaderCnt] == 2) {//H5
							*((uint16 *)bme280_ptrTable[bme280_loaderCnt]) = (uint16) (((bme280TempData[0] & 0xF0) >> 4) | ((bme280TempData[1]) << 4));
						}
					} else if (bme280_sizeTable[bme280_loaderCnt] == 1) {
						*((uint8 *)bme280_ptrTable[bme280_loaderCnt]) = (uint8)bme280TempData[0];
					} else {
					}
					bme280_loaderCnt++;
					if (bme280_loaderCnt >= (sizeof(bme280_ptrTable) / sizeof(*bme280_ptrTable)) ) {
						bme280States = Bme280State_Control;
					} else {
						bme280States = Bme280State_Calibration_1_Start;
					}
					
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Control : {
				IIC_Result retVal = IIC_Result_Error;
				bme280TempData[0] = 0xF2;

				bme280TempData[1] = (BME280_OSS_H_BIT);//0xF2
				bme280TempData[2] = 0;//0xF3
				bme280TempData[3] = (BME280_OSS_T_BIT << 5) | (BME280_OSS_P_BIT << 2) | BME280_MODE_SLEEP_BIT;//0xF4
				bme280TempData[4] = (BME280_SB_BIT << 5) | (BME280_FILTER_BIT << 2) | 0;//0xF5
				retVal = iic_write_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 5, 0, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_Control_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Control_Poll : {
				IIC_Result retVal = iic_getState_async_multi(BME280_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_Idle;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_Idle : {
				if (read_timer(&bme280_samplingTimer) == 0) {
					write_timer(&bme280_samplingTimer, BME280_SAMPLING_TIME);
					bme280States = Bme280State_StartConverion;
				}
				break;
			}
			case Bme280State_StartConverion : {
				IIC_Result retVal = IIC_Result_Error;
				bme280TempData[0] = 0xF4;
				bme280TempData[1] = (BME280_OSS_T_BIT << 5) | (BME280_OSS_P_BIT << 2) | BME280_MODE_FORCED_BIT;//0xF4
				retVal = iic_write_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 2, 0, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_StartConverion_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_StartConverion_Poll : {
				IIC_Result retVal = iic_getState_async_multi(BME280_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					write_timer(&bme280_conversionTimer, bme280_conversionTimerValue);
					bme280States = Bme280State_WaitForResult_Address;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_WaitForResult_Address : {
				if (read_timer(&bme280_conversionTimer) == 0) {
					unsigned char address = 0xF3;
					bme280TempData[0] = address;
					IIC_Result retVal = iic_write_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 1, 0, BME280_FREQ);
					if (retVal == IIC_Result_OK) {
						bme280States = Bme280State_WaitForResult_Address_Poll;
					} else if (retVal == IIC_Result_Busy) {
						bme280States = Bme280State_Init;
					} else if (retVal == IIC_Result_Error) {
						bme280States = Bme280State_Init;
					}
				}
				break;
			}
			case Bme280State_WaitForResult_Address_Poll : {
				IIC_Result retVal = iic_getState_async_multi(BME280_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_WaitForResult;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_WaitForResult : {
				IIC_Result retVal = iic_read_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 1, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_WaitForResult_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}		
			case Bme280State_WaitForResult_Poll : {
				IIC_Result retVal = iic_getState_async_multi(0);
				if (retVal == IIC_Result_OK) {
					uint8 result = 0;
					result = bme280TempData[0];
					if ((result & 0x09) == 0) {
						bme280States = Bme280State_ReadResult_Address;
					} else {
						bme280States = Bme280State_WaitForResult_Address;
					}
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_ReadResult_Address : {
				unsigned char address = 0xF7;
				bme280TempData[0] = address;
				IIC_Result retVal = iic_write_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 1, 0, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_ReadResult_Address_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_ReadResult_Address_Poll : {
				IIC_Result retVal = iic_getState_async_multi(0);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_ReadResult;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_ReadResult : {
				IIC_Result retVal = iic_read_async_multi(BME280_IIC_MASTER_MULTI_USER, BME280_ADDRESS, bme280TempData, 8, BME280_FREQ);
				if (retVal == IIC_Result_OK) {
					bme280States = Bme280State_ReadResult_Poll;
				} else if (retVal == IIC_Result_Busy) {
					bme280States = Bme280State_Init;
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_ReadResult_Poll : {
				IIC_Result retVal = iic_getState_async_multi(0);
				if (retVal == IIC_Result_OK) {
					UP = (bme280TempData[0] << 12) | (bme280TempData[1] << 4) | ((bme280TempData[2]&0xF0) >> 4);
					UT = (bme280TempData[3] << 12) | (bme280TempData[4] << 4) | ((bme280TempData[5]&0xF0) >> 4);
					UH = (bme280TempData[6] << 8) | (bme280TempData[7]);
					bme280States = Bme280State_CalculateTemp;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					bme280States = Bme280State_Init;
				}
				break;
			}
			case Bme280State_CalculateTemp : {
				resultTemp = ((float)BME280_compensate_T_int32(UT) / 100.0);
				bme280States = Bme280State_CalculatePressure;
				break;
			}
			case Bme280State_CalculatePressure : {
				resultPressure = ((float)BME280_compensate_P_int64(UP) / 256.0);
				bme280States = Bme280State_CalculateHumidity;
				if (resultPressure >= 100000.0) {
					resultPressureError ++;
				}
				break;
			}
			case Bme280State_CalculateHumidity : {
				resultHumidity = ((float)bme280_compensate_H_int32(UH) / 1024.0);
				bme280States = Bme280State_Idle;
				break;
			}
			default : {
				bme280States = Bme280State_Idle;
				break;
			}
		}
	}
}

void isr_bme280_1ms(void) {
	{
		static unsigned int tempCnt = 0;
		if (tempCnt != 0) {
			tempCnt --;
		}
		if (tempCnt == 0) {
			tempCnt = 100;
			do_bme280_1ms = 1;
		}
	}
   	//do_bme280_1ms = 1;
}

// Returns temperature in DegC, resolution is 0.01 DegC. Output value of �5123� equals 51.23 DegC. 
// t_fine carries fine temperature as global value 
sint32 BME280_compensate_T_int32(sint32 adc_T) {
	sint32 var1, var2, T;
	var1  = ((((adc_T>>3) - ((sint32)dig_T1<<1))) * ((sint32)dig_T2)) >> 11;
	var2  = (((((adc_T>>4) - ((sint32)dig_T1)) * ((adc_T>>4) - ((sint32)dig_T1))) >> 12) * ((sint32)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T  = (t_fine * 5 + 128) >> 8;
	return T;
}

// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits). 
// Output value of ?24674867? represents 24674867/256 = 96386.2 Pa = 963.862 hPa 
uint32 BME280_compensate_P_int64(sint32 adc_P) {
	sint64 var1, var2, p;
	var1 = ((sint64)t_fine) - 128000;
	var2 = var1 * var1 * (sint64)dig_P6;
	var2 = var2 + ((var1*(sint64)dig_P5)<<17);
	var2 = var2 + (((sint64)dig_P4)<<35);
	var1 = ((var1 * var1 * (sint64)dig_P3)>>8) + ((var1 * (sint64)dig_P2)<<12);
	var1 = (((((sint64)1)<<47)+var1))*((sint64)dig_P1)>>33;
	if (var1 == 0)  {
		return 0;
		// avoid exception caused by division by zero  
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((sint64)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((sint64)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((sint64)dig_P7)<<4);
	return (uint32)p;
}

// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits). 
// Output value of ?47445? represents 47445/1024 = 46.333 %RH 
uint32 bme280_compensate_H_int32(sint32 adc_H) {
	sint32 v_x1_u32r;
	v_x1_u32r = (t_fine - ((sint32)76800));
	v_x1_u32r = (((((adc_H << 14) - (((sint32)dig_H4) << 20) - (((sint32)dig_H5) * v_x1_u32r)) + ((sint32)16384)) >> 15) * (((((((v_x1_u32r * ((sint32)dig_H6)) >> 10) * (((v_x1_u32r * ((sint32)dig_H3)) >> 11) + ((sint32)32768))) >> 10) + ((sint32)2097152)) * ((sint32)dig_H2) + 8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((sint32)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32)(v_x1_u32r>>12);
}

float getBME280Temp(void) {
	float result = 0.0;
	result = (float)resultTemp;
	return result;
}

float getBME280Pressure(void) {
	float result = 0.0;
	result = (float)resultPressure;
	return result;
}

float getBME280Altitude(void) {
	float result = 0.0;
	result = (float)resultAltitude;
	return result;
}

float getBME280Humidity(void) {
	float result = 0.0;
	result = (float)resultHumidity;
	return result;
}

float getBME280PressureAtSeeLevel(float altitude) {
	float result = 0;
	
	float pressureAtCurrentHeight = getBME280Pressure();
	result = calculateSeeLevelPressure(pressureAtCurrentHeight, altitude);
	
	result = pressureAtCurrentHeight / pow(1.0 - (altitude / 44330.0), 5.255);
	
	result /= 100.0;

	return result;
}
