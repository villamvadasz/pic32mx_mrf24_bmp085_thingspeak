#ifndef _C_BME280_H_
#define _C_BME280_H_

	#include "c_iic_master_multi.h"

	#define BME280_IIC_MASTER_MULTI_USER IIC_MASTER_MULTI_HANDLE_USER0
	
	#define BME280_FREQ (1000000u)

	#define BME280_SAMPLING_TIME 1000 //[ms]

	#define BME280_ADDRESS 0x77			//7bit address
	//#define BME280_ADDRESS 0x76		//7bit address

	#define BME280_OSS_T 16
	#define BME280_OSS_H 16
	#define BME280_OSS_P 16
	#define BME280_FILTER_BIT 4 //16
	#define BME280_SB_BIT 0x7 //20ms

#endif
