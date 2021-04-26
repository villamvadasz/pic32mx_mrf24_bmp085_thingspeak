#include <string.h>
#include "ccs811.h"
#include "c_ccs811.h"

#include "iic_master_multi.h"
#include "tmr.h"

#define CCS811_ADDRESS (0x5A)
#define CCS811_HW_ID_CODE 0x81
#define CCS811_REF_RESISTOR 100000

typedef enum _Ccs811_states {
	ccs811_states_Init = 0,
	ccs811_states_Reset,
	ccs811_states_Reset_Poll,
	ccs811_states_HW_ID_READ,
	ccs811_states_HW_ID_READ_Poll,
	ccs811_states_StartApp,
	ccs811_states_StartApp_Poll,
	ccs811_states_StartApp_WaitDelay,
	ccs811_states_CheckStatus,
	ccs811_states_CheckStatus_Poll,
	ccs811_states_DisableInterrupt,
	ccs811_states_DisableInterrupt_Poll,
	ccs811_states_DriveMode,
	ccs811_states_DriveMode_Poll,
	ccs811_states_WaitAvailable,
	ccs811_states_WaitAvailable_Poll,
	ccs811_states_ReadData,
	ccs811_states_ReadData_Poll,
	ccs811_states_ReadData_Value,
	ccs811_states_ReadData_Value_Poll,
	ccs811_states_EnvUpdate,
	ccs811_states_EnvUpdate_Poll,
} Ccs811_states;

typedef enum _Ccs811_Registers {
	CCS811_STATUS = 0x00,
	CCS811_MEAS_MODE = 0x01,
	CCS811_ALG_RESULT_DATA = 0x02,
	CCS811_RAW_DATA = 0x03,
	CCS811_ENV_DATA = 0x05,
	CCS811_NTC = 0x06,
	CCS811_THRESHOLDS = 0x10,
	CCS811_BASELINE = 0x11,
	CCS811_HW_ID = 0x20,
	CCS811_HW_VERSION = 0x21,
	CCS811_FW_BOOT_VERSION = 0x23,
	CCS811_FW_APP_VERSION = 0x24,
	CCS811_ERROR_ID = 0xE0,
	CCS811_SW_RESET = 0xFF,
} Ccs811_Registers;

typedef enum _Ccs811_Bootloader {
	CCS811_BOOTLOADER_APP_ERASE = 0xF1,
	CCS811_BOOTLOADER_APP_DATA = 0xF2,
	CCS811_BOOTLOADER_APP_VERIFY = 0xF3,
	CCS811_BOOTLOADER_APP_START = 0xF4
} Ccs811_Bootloader;

typedef enum _Ccs811_Drive_Mode {
	CCS811_DRIVE_MODE_IDLE = 0x00,
	CCS811_DRIVE_MODE_1SEC = 0x01,
	CCS811_DRIVE_MODE_10SEC = 0x02,
	CCS811_DRIVE_MODE_60SEC = 0x03,
	CCS811_DRIVE_MODE_250MS = 0x04,
} Ccs811_Drive_Mode;


typedef enum _Ccs811_read_states {
	ccs811_read_states_idle,
	ccs811_read_states_write_address,
	ccs811_read_states_write_address_Poll,
	ccs811_read_states_read_data,
	ccs811_read_states_read_data_Poll,
	ccs811_read_states_finished,
} Ccs811_read_states;


typedef struct _Ccs811_status {
	/* 0: no error
	*  1: error has occurred
	*/
	uint8_t ERROR : 1;
	uint8_t reserved_1 : 1;
	uint8_t reserved_2 : 1;

	/* 0: no samples are ready
	*  1: samples are ready
	*/
	uint8_t DATA_READY : 1;
	uint8_t APP_VALID : 1;
	uint8_t APP_VERIFY : 1;
	uint8_t APP_ERASE : 1;

	/* 0: boot mode, new firmware can be loaded
	*  1: application mode, can take measurements
	*/
	uint8_t FW_MODE : 1;
} Ccs811_status;

// measurement and conditions register
typedef struct _Ccs811_meas_mode {
	uint8_t reserved_1 : 1;
	uint8_t reserved_2 : 1;

	/* 0: interrupt mode operates normally
	*  1: Interrupt mode (if enabled) only asserts the nINT signal (driven low) if
	the new ALG_RESULT_DATA crosses one of the thresholds set in the THRESHOLDS
	register by more than the hysteresis value (also in the THRESHOLDS register)
	*/
	uint8_t INT_THRESH : 1;

	/* 0: int disabled
	*  1: The nINT signal is asserted (driven low) when a new sample is ready in
	ALG_RESULT_DATA. The nINT signal will stop being driven low
	when ALG_RESULT_DATA is read on the I²C interface.
	*/
	uint8_t INT_DATARDY : 1;

	uint8_t DRIVE_MODE : 3;

	uint8_t reserved_3 : 1;
} Ccs811_meas_mode;

typedef struct _Ccs811_error_id {
	/* The CCS811 received an I²C write request addressed to this station but
	with invalid register address ID */
	uint8_t WRITE_REG_INVALID : 1;

	/* The CCS811 received an I²C read request to a mailbox ID that is invalid
	*/
	uint8_t READ_REG_INVALID : 1;

	/* The CCS811 received an I²C request to write an unsupported mode to
	MEAS_MODE */
	uint8_t MEASMODE_INVALID : 1;

	/* The sensor resistance measurement has reached or exceeded the maximum
	range */
	uint8_t MAX_RESISTANCE : 1;

	/* The Heater current in the CCS811 is not in range */
	uint8_t HEATER_FAULT : 1;

	/*  The Heater voltage is not being applied correctly */
	uint8_t HEATER_SUPPLY : 1;
	uint8_t reserved_1 : 1;
	uint8_t reserved_2 : 1;
} Ccs811_error_id;

Ccs811_read_states ccs811_read_states = ccs811_read_states_idle;
uint8 ccs811_read_trigger = 0;
uint8 ccs811_read_result = 0;
uint8 ccs811_read_address = CCS811_ERROR_ID;
uint8 ccs811_read_data = 0;

Ccs811_status ccs811_status;
Ccs811_meas_mode ccs811_meas_mode;
Ccs811_error_id ccs811_error_id;
Ccs811_states ccs811_states = ccs811_states_Init;
uint8 do_ccs811_1ms = 0;
double ccs811_CO2 = 0.0;
double ccs811_TVOC = 0.0;
uint8 ccs811_TempData[32];
Timer ccs811_delayTimer = 0;

uint16 ccs811_eCO2_raw = 0;
uint16 ccs811_TVOC_raw = 0;

uint16 ccs811_temp_compensation = 0;
uint16 ccs811_humi_compensation = 0;
uint8 ccs811_env_comp_available = 0;

void ccs811_status_set(uint8_t data);
uint8_t ccs811_meas_mode_get(void);
void ccs811_error_id_set(uint8_t data);

void ccs811_trigger_read_register(uint8 address);
sint8 ccs811_trigger_get_data(uint8 *data);

void init_ccs811(void) {
	ccs811_states = ccs811_states_Init;
	init_timer(&ccs811_delayTimer);
}

void do_ccs811(void) {
	if (do_ccs811_1ms) {
		do_ccs811_1ms = 0;

		switch (ccs811_read_states) {
			case ccs811_read_states_idle : {
				if (ccs811_read_trigger) {
					ccs811_read_states = ccs811_read_states_write_address;
				}
				break;
			}
			case ccs811_read_states_write_address : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_read_result = 0;
				ccs811_TempData[0] = ccs811_read_address;
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 1, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_read_states = ccs811_read_states_write_address_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_read_states = ccs811_read_states_finished;
				} else if (retVal == IIC_Result_Error) {
					ccs811_read_states = ccs811_read_states_finished;
				}
				break;
			}
			case ccs811_read_states_write_address_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_read_states = ccs811_read_states_read_data;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_read_states = ccs811_read_states_finished;
				}
				break;
			}
			case ccs811_read_states_read_data : {
				IIC_Result retVal = iic_read_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 1, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_read_states = ccs811_read_states_read_data_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_read_states = ccs811_read_states_finished;
				} else if (retVal == IIC_Result_Error) {
					ccs811_read_states = ccs811_read_states_finished;
				}	
				break;
			}
			case ccs811_read_states_read_data_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_read_data = ccs811_TempData[0];
					ccs811_read_result = 1;
					ccs811_read_states = ccs811_read_states_finished;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_read_states = ccs811_read_states_finished;
				}
				break;
			}
			case ccs811_read_states_finished : {
				ccs811_read_trigger = 0;
				ccs811_read_states = ccs811_read_states_idle;
				break;
			}
			default : {
				break;
			}	
		}


		switch (ccs811_states) {
			case ccs811_states_Init : {
				ccs811_states = ccs811_states_Reset;
				break;
			}
			case ccs811_states_Reset : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_TempData[0] = CCS811_SW_RESET;
				ccs811_TempData[1] = 0x11;
				ccs811_TempData[2] = 0xE5;
				ccs811_TempData[3] = 0x72;
				ccs811_TempData[4] = 0x8A;
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 5, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_Reset_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_Reset_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_HW_ID_READ;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_HW_ID_READ : {
				ccs811_trigger_read_register(CCS811_HW_ID);
				ccs811_states = ccs811_states_HW_ID_READ_Poll;
				break;
			}
			case ccs811_states_HW_ID_READ_Poll : {
				uint8 data = 0;
				sint8 result = ccs811_trigger_get_data(&data);
				if (result == -1) {//busy
				} else if (result == 0) {//failed
					ccs811_states = ccs811_states_Init;
				} else if (result == 1) {//ok
					if (data == CCS811_HW_ID_CODE) {
						ccs811_states = ccs811_states_StartApp;
					} else {
						ccs811_states = ccs811_states_Init;
					}
				} else {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_StartApp : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_TempData[0] = CCS811_BOOTLOADER_APP_START;
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 1, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_StartApp_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_StartApp_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					write_timer(&ccs811_delayTimer, 100);
					ccs811_states = ccs811_states_StartApp_WaitDelay;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_StartApp_WaitDelay : {
				if (read_timer(&ccs811_delayTimer) == 0) {
					ccs811_states = ccs811_states_CheckStatus;
				}
				break;
			}
			case ccs811_states_CheckStatus : {
				ccs811_trigger_read_register(CCS811_STATUS);
				ccs811_states = ccs811_states_CheckStatus_Poll;
				break;
			}
			case ccs811_states_CheckStatus_Poll : {
				uint8 data = 0;
				sint8 result = ccs811_trigger_get_data(&data);
				if (result == -1) {//busy
				} else if (result == 0) {//failed
					ccs811_states = ccs811_states_Init;
				} else if (result == 1) {//ok
					ccs811_status_set(data);
					if (ccs811_status.ERROR) {
						ccs811_states = ccs811_states_Init;
					} else {
						if (ccs811_status.FW_MODE) {
							ccs811_states = ccs811_states_DisableInterrupt;
						} else {
							ccs811_states = ccs811_states_Init;
						}
					}
				} else {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_DisableInterrupt : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_meas_mode.INT_DATARDY = 0;
				ccs811_TempData[0] = CCS811_MEAS_MODE;
				ccs811_TempData[1] = ccs811_meas_mode_get();
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 2, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_DisableInterrupt_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_DisableInterrupt_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_DriveMode;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_DriveMode : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_meas_mode.DRIVE_MODE = CCS811_DRIVE_MODE_1SEC;
				ccs811_TempData[0] = CCS811_MEAS_MODE;
				ccs811_TempData[1] = ccs811_meas_mode_get();
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 2, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_DriveMode_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_DriveMode_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_WaitAvailable;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_WaitAvailable : {
				ccs811_trigger_read_register(CCS811_STATUS);
				ccs811_states = ccs811_states_WaitAvailable_Poll;
				break;
			}
			case ccs811_states_WaitAvailable_Poll : {
				uint8 data = 0;
				sint8 result = ccs811_trigger_get_data(&data);
				if (result == -1) {//busy
				} else if (result == 0) {//failed
					ccs811_states = ccs811_states_Init;
				} else if (result == 1) {//ok
					ccs811_status_set(data);
					if (ccs811_status.DATA_READY) {
						ccs811_states = ccs811_states_ReadData;
					} else {
						ccs811_states = ccs811_states_WaitAvailable;
					}				
				} else {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_ReadData : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_TempData[0] = CCS811_ALG_RESULT_DATA;
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 1, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_ReadData_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_ReadData_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_ReadData_Value;
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_ReadData_Value : {
				IIC_Result retVal = iic_read_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 8, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_ReadData_Value_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_ReadData_Value_Poll : {
				IIC_Result retVal = iic_getState_async_multi(CCS811_IIC_MASTER_MULTI_USER);
				if (retVal == IIC_Result_OK) {
					ccs811_eCO2_raw = ((uint16_t)ccs811_TempData[0] << 8) | ((uint16_t)ccs811_TempData[1]);
					ccs811_TVOC_raw = ((uint16_t)ccs811_TempData[2] << 8) | ((uint16_t)ccs811_TempData[3]);

					ccs811_CO2 = ccs811_eCO2_raw;//ppm
					ccs811_TVOC = ccs811_TVOC_raw;//ppb
					
					if (ccs811_env_comp_available) {
						ccs811_env_comp_available = 0;
						ccs811_states = ccs811_states_EnvUpdate;
					} else {
						ccs811_states = ccs811_states_WaitAvailable;
					}
					
				} else if (retVal == IIC_Result_Busy) {
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}
				break;
			}
			case ccs811_states_EnvUpdate : {
				IIC_Result retVal = IIC_Result_Error;
				ccs811_TempData[0] = CCS811_ENV_DATA;
				ccs811_TempData[1] = (ccs811_humi_compensation >> 8) & 0xFF;
				ccs811_TempData[2] = ccs811_humi_compensation & 0xFF;
				ccs811_TempData[3] = (ccs811_temp_compensation >> 8) & 0xFF;
				ccs811_TempData[4] = ccs811_temp_compensation & 0xFF;
				retVal = iic_write_async_multi(CCS811_IIC_MASTER_MULTI_USER, CCS811_ADDRESS, ccs811_TempData, 2, 0, CCS811_FREQ);
				if (retVal == IIC_Result_OK) {
					ccs811_states = ccs811_states_EnvUpdate_Poll;
				} else if (retVal == IIC_Result_Busy) {
					ccs811_states = ccs811_states_Init;
				} else if (retVal == IIC_Result_Error) {
					ccs811_states = ccs811_states_Init;
				}

				break;
			}
			case ccs811_states_EnvUpdate_Poll : {
				ccs811_states = ccs811_states_WaitAvailable;
				break;
			}
			default : {
				break;
			}
		}
	}
}

void isr_ccs811_1ms(void) {
	do_ccs811_1ms = 1;
}

void ccs811_status_set(uint8_t data) {
	ccs811_status.ERROR = data & 0x01;
	ccs811_status.DATA_READY = (data >> 3) & 0x01;
	ccs811_status.APP_VALID = (data >> 4) & 0x01;
	ccs811_status.FW_MODE = (data >> 7) & 0x01;
}

uint8_t ccs811_meas_mode_get(void) {
	return (ccs811_meas_mode.INT_THRESH << 2) | (ccs811_meas_mode.INT_DATARDY << 3) | (ccs811_meas_mode.DRIVE_MODE << 4);
}

void ccs811_error_id_set(uint8_t data) {
	ccs811_error_id.WRITE_REG_INVALID = data & 0x01;
	ccs811_error_id.READ_REG_INVALID = (data & 0x02) >> 1;
	ccs811_error_id.MEASMODE_INVALID = (data & 0x04) >> 2;
	ccs811_error_id.MAX_RESISTANCE = (data & 0x08) >> 3;
	ccs811_error_id.HEATER_FAULT = (data & 0x10) >> 4;
	ccs811_error_id.HEATER_SUPPLY = (data & 0x20) >> 5;
}

double ccs811_get_CO2(void) {
	double result = 0.0;
	result = ccs811_CO2;
	return result;
}

double ccs811_get_TVOC(void) {
	double result = 0.0;
	result = ccs811_TVOC;
	return result;
}

void ccs811_trigger_read_register(uint8 address) {
	ccs811_read_trigger = 1;
	ccs811_read_address = address;
}

sint8 ccs811_trigger_get_data(uint8 *data) {
	sint8 result = -1;
	if (ccs811_read_trigger == 1) {
		result = -1;
	} else {
		if (ccs811_read_result) {
			if (data != NULL) {
				*data = ccs811_read_data;
			}
			result = 1;
		} else {
			result = 0;
		}
	}
	return result;
}

void ccs811_set_TemperatureAndHumidity(float temp, float humi) {
	uint32 temp_u32 = temp * 512.0f;
	uint32 humi_u32 = humi * 512.0f;

	ccs811_temp_compensation = temp_u32;
	ccs811_humi_compensation = humi_u32;
	
	ccs811_env_comp_available = 1;
}
