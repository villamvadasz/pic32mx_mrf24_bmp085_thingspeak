#include "sht31d.h"
#include "c_sht31d.h"

#include "k_stdtype.h"
#include "iic_master_multi.h"
#include "tmr.h"

#define CMD_SINGLE_CLKSTRETCH_REPHIGH     0x2c06
#define CMD_SINGLE_NOCLKSTRETCH_REPHIGH   0x2400
#define CMD_GETSERIAL                     0x3780

#define MEASUREMENT_DURATION_HIGH_MS      15

#define SHT31D_IIC_ADDRESS	0x44
//#define SHT31D_IIC_ADDRESS	0x45

typedef enum _SHT31D_state_machine {
	SHT31D_idle = 0,
	SHT31D_SendCommand_1,
	SHT31D_SendCommand_1_Wait,
	SHT31D_WaitMeasurement,
	SHT31D_WaitMeasurement_Wait,
	SHT31D_ReadResult,
	SHT31D_ReadResult_Wait,
	SHT31D_ConvertMeasurement
} SHT31D_state_machine;

unsigned char do_sht31d_1ms = 0;
SHT31D_state_machine sht31d_state_machine = SHT31D_idle;
uint8 sht31d_data[6];
Timer sht31d_measurement_tmr;
Timer sht31d_measurement_poll;
float sht31d_temp = 0.0f;
float sht31d_humidity = 0.0f;

float sht3xd_calculate_temp_c(uint8_t msb, uint8_t lsb);
float sht3xd_calculate_humid(uint8_t msb, uint8_t lsb);
unsigned char sht31d_CRC8(unsigned char *idata, int len);

void init_sht31d(void) {
	init_timer(&sht31d_measurement_tmr);
	init_timer(&sht31d_measurement_poll);
}

void do_sht31d(void) {
	if (do_sht31d_1ms) {
		do_sht31d_1ms = 0;
		{
			switch (sht31d_state_machine) {
				case SHT31D_idle : {
					if (read_timer(&sht31d_measurement_poll) == 0) {
						write_timer(&sht31d_measurement_poll, 1000);
						sht31d_state_machine = SHT31D_SendCommand_1;
					}
					break;
				}
				case SHT31D_SendCommand_1 : {
					IIC_Result result = IIC_Result_Error;
					sht31d_data[0] = ((CMD_SINGLE_NOCLKSTRETCH_REPHIGH >> 8) & 0xFF);//CMD_SINGLE_NOCLKSTRETCH_REPHIGH
					sht31d_data[1] = (CMD_SINGLE_NOCLKSTRETCH_REPHIGH & 0xFF);
					result = iic_write_async_multi(IIC_MASTER_MULTI_HANDLE_SHT31D, SHT31D_IIC_ADDRESS, sht31d_data, 2, 0, SHT31D_FREQ);
					if (result == IIC_Result_Busy) {
						sht31d_state_machine = SHT31D_SendCommand_1;
					} else if (result == IIC_Result_OK) {
						sht31d_state_machine = SHT31D_SendCommand_1_Wait;
					} else if (result == IIC_Result_Error) {
						sht31d_state_machine = SHT31D_idle;
					} else {
						sht31d_state_machine = SHT31D_idle;
					}
					break;
				}
				case SHT31D_SendCommand_1_Wait : {
					IIC_Result result = iic_getState_async_multi(IIC_MASTER_MULTI_HANDLE_SHT31D);
					if (result == IIC_Result_Busy) {
					} else if (result == IIC_Result_OK) {
						sht31d_state_machine = SHT31D_WaitMeasurement;
					} else if (result == IIC_Result_Error) {
						sht31d_state_machine = SHT31D_idle;
					} else {
						sht31d_state_machine = SHT31D_idle;
					}
					break;
				}
				case SHT31D_WaitMeasurement : {
					write_timer(&sht31d_measurement_tmr, MEASUREMENT_DURATION_HIGH_MS);
					sht31d_state_machine = SHT31D_WaitMeasurement_Wait;
					break;
				}
				case SHT31D_WaitMeasurement_Wait : {
					if (read_timer(&sht31d_measurement_tmr) == 0) {
						sht31d_state_machine = SHT31D_ReadResult;
					}
					break;
				}
				case SHT31D_ReadResult : {
					IIC_Result result = IIC_Result_Error;
					result = iic_read_async_multi(IIC_MASTER_MULTI_HANDLE_SHT31D, SHT31D_IIC_ADDRESS, sht31d_data, 6, SHT31D_FREQ);
					if (result == IIC_Result_Busy) {
						sht31d_state_machine = SHT31D_ReadResult;
					} else if (result == IIC_Result_OK) {
						sht31d_state_machine = SHT31D_ReadResult_Wait;
					} else if (result == IIC_Result_Error) {
						sht31d_state_machine = SHT31D_idle;
					} else {
						sht31d_state_machine = SHT31D_idle;
					}
					break;
				}
				case SHT31D_ReadResult_Wait : {
					IIC_Result result = iic_getState_async_multi(IIC_MASTER_MULTI_HANDLE_SHT31D);
					if (result == IIC_Result_Busy) {
					} else if (result == IIC_Result_OK) {
						sht31d_state_machine = SHT31D_ConvertMeasurement;
					} else if (result == IIC_Result_Error) {
						sht31d_state_machine = SHT31D_idle;
					} else {
						sht31d_state_machine = SHT31D_idle;
					}
					break;
				}
				case SHT31D_ConvertMeasurement : {

					//check CRC
					if (sht31d_CRC8(&sht31d_data[0], 2) == sht31d_data[2]) {
						sht31d_temp = sht3xd_calculate_temp_c(sht31d_data[0], sht31d_data[1]);
					}
					if (sht31d_CRC8(&sht31d_data[3], 2) == sht31d_data[5]) {
						sht31d_humidity = sht3xd_calculate_humid(sht31d_data[3], sht31d_data[4]);
					}
					sht31d_state_machine = SHT31D_idle;
					break;
				}
				default : {
					break;
				}
			}
		}
	}
}

void isr_sht31d_1ms(void) {
	do_sht31d_1ms = 1;
}

float sht31d_getTemp(void) {
	float result = 0;
	result = sht31d_temp;
	return result;
}

float sht31d_getHumidity(void) {
	float result = 0;
	result = sht31d_humidity;
	return result;
}


float sht3xd_calculate_temp_c(uint8_t msb, uint8_t lsb) {
	uint16_t val = 0;
	float temp = 0.0f;

	val = msb << 8 | lsb;
	temp = 175.0f * ((float)val / 65535.0f) - 45.0f;

	return (temp);
}

float sht3xd_calculate_humid(uint8_t msb, uint8_t lsb) {
    uint16_t val = 0;
    float humid = 0.0f;

    val = msb << 8 | lsb;
    humid = 100.0f * ((float)val / 65535.0f);

    return (humid);
}

unsigned char sht31d_CRC8(unsigned char *idata, int len) {
    /*
        Polynomial: 0x31 (x8 + x5 + x4 + 1)
        Initialization: 0xFF
        Final XOR: 0x00
        Example: CRC (0xBEEF) = 0x92
    */
    const unsigned char POLYNOMIAL = 0x31;
    unsigned char CRC = 0xFF;
	int j = 0;
	int i = 0;
    
    for ( j = len; j; --j ) {
        CRC ^= *idata++;
        for ( i = 8; i; --i ) {
            CRC = ( CRC & 0x80 ) ? (CRC << 1) ^ POLYNOMIAL : (CRC << 1);
        }
    }
    return CRC;
}
