#include <stdio.h>
#include "iic_master_multi.h"
#include "c_iic_master_multi.h"

#include "iic_master.h"
#include "mal.h"
#include "k_stdtype.h"
#include "tmr.h"

#define IIC_MASTER_MULTI_USERS	IIC_MASTER_MULTI_HANDLE_MAX

typedef enum _Iic_master_multi_operation {
	Iic_master_multi_operation_read,
	Iic_master_multi_operation_write
} Iic_master_multi_operation;

typedef enum _Iic_master_processing_state {
	Iic_master_processing_state_0 = 0,
	Iic_master_processing_state_1,
}Iic_master_processing_state;

typedef struct _Iic_master_multi_data {
	uint8 processing;
	Iic_master_processing_state processingState;
	Iic_master_multi_operation operation;
	uint8 iic_master_tx_addr;
	uint8 *iic_buffer_master_tx;
	uint32 iic_master_write_size;
	uint8 iic_master_repeat;
	IIC_Result iic_getState_async_state;
	uint8 iic_master_rx_addr;
	uint8 *iic_buffer_master_rx;
	uint32 iic_master_read_size;
	uint32 iic_master_freq;
} Iic_master_multi_data;

volatile uint32 do_iic_master_multi_1ms = 0;
volatile uint32 do_iic_master_multi_100us = 0;
Iic_master_multi_data iic_master_multi_data[IIC_MASTER_MULTI_USERS];
uint32 foundItem = 0;

void init_iic_master_multi(void) {
	uint32 x = 0;
	for (x = 0; x < IIC_MASTER_MULTI_USERS ; x++) {
		iic_master_multi_data[x].iic_getState_async_state = IIC_Result_Error;
	}
}

void deinit_iic_master_multi(void) {
	uint32 x = 0;
	for (x = 0; x < IIC_MASTER_MULTI_USERS ; x++) {
		iic_master_multi_data[x].iic_getState_async_state = IIC_Result_Error;
	}
}

void do_iic_master_multi(void) {
	if (do_iic_master_multi_100us || do_iic_master_multi_1ms) {
		uint32 x = 0;
		uint8 found = 0;
        do_iic_master_multi_100us = 0;
		do_iic_master_multi_1ms = 0;
		for (x = 0; x < IIC_MASTER_MULTI_USERS ; x++) {
			if (iic_master_multi_data[x].processing != 0) {
				found = 1;
				foundItem = x;
				break;
				
			}
		}
		if (found) {
			switch (iic_master_multi_data[foundItem].processingState) {
				case Iic_master_processing_state_0 : {
					if (iic_getState_async() != IIC_Result_Busy) {
						if (iic_master_multi_data[foundItem].operation == Iic_master_multi_operation_read) {
							iic_master_multi_data[foundItem].iic_getState_async_state = iic_read_async(		iic_master_multi_data[foundItem].iic_master_rx_addr,
																											iic_master_multi_data[foundItem].iic_buffer_master_rx, 
																											iic_master_multi_data[foundItem].iic_master_read_size,
																											iic_master_multi_data[foundItem].iic_master_freq
																										);
							iic_master_multi_data[foundItem].iic_getState_async_state = iic_getState_async();
							iic_master_multi_data[foundItem].processingState = Iic_master_processing_state_1;
						} else if (iic_master_multi_data[foundItem].operation == Iic_master_multi_operation_write) {
							iic_master_multi_data[foundItem].iic_getState_async_state = iic_write_async(	iic_master_multi_data[foundItem].iic_master_tx_addr,
																											iic_master_multi_data[foundItem].iic_buffer_master_tx,
																											iic_master_multi_data[foundItem].iic_master_write_size,
																											iic_master_multi_data[foundItem].iic_master_repeat,
																											iic_master_multi_data[foundItem].iic_master_freq
																										);
							iic_master_multi_data[foundItem].iic_getState_async_state = iic_getState_async();
							iic_master_multi_data[foundItem].processingState = Iic_master_processing_state_1;
						} else {
							iic_master_multi_data[foundItem].processing = 0;
							iic_master_multi_data[foundItem].iic_getState_async_state = IIC_Result_Error;
						}
					}
					break;
				}
				case Iic_master_processing_state_1 : {
					iic_master_multi_data[foundItem].iic_getState_async_state = iic_getState_async();
					if (
						(iic_master_multi_data[foundItem].iic_getState_async_state == IIC_Result_OK) || 
						(iic_master_multi_data[foundItem].iic_getState_async_state == IIC_Result_Error)
					) {
						iic_master_multi_data[foundItem].processingState = Iic_master_processing_state_0;
                        iic_master_multi_data[foundItem].processing = 0;
					}
					break;
				}
				default : {
					iic_master_multi_data[foundItem].processing = 0;
					iic_master_multi_data[foundItem].iic_getState_async_state = IIC_Result_Error;
					break;
				}
			}
		} else {
			for (x = 0; x < IIC_MASTER_MULTI_USERS ; x++) {
				if (
					(iic_master_multi_data[x].processing == 0) && 
					(iic_master_multi_data[x].iic_getState_async_state == IIC_Result_Busy)
				) {
					iic_master_multi_data[x].processing = 1;
					break;
				}
			}
		}
	}
}

void isr_iic_master_multi_1ms(void) {
	do_iic_master_multi_1ms = 1;
}

void isr_iic_master_multi_100us(void) {
	do_iic_master_multi_100us = 1;
}

IIC_Result iic_write_async_multi(uint32 handle, uint8 addr, uint8 *data, uint32 size, uint8 repeat, uint32 freq) {
	IIC_Result result = IIC_Result_Error;
	
	if (handle < IIC_MASTER_MULTI_USERS) {
		if (data != NULL) {
			if (
				(iic_master_multi_data[handle].iic_getState_async_state == IIC_Result_OK) || 
				(iic_master_multi_data[handle].iic_getState_async_state == IIC_Result_Error)
			) {
				iic_master_multi_data[handle].operation = Iic_master_multi_operation_write;
				
				
				iic_master_multi_data[handle].iic_master_tx_addr = addr;
				iic_master_multi_data[handle].iic_master_repeat = repeat;			
				iic_master_multi_data[handle].iic_master_write_size = size;
				iic_master_multi_data[handle].iic_buffer_master_tx = data;
				iic_master_multi_data[handle].iic_master_freq = freq;
				iic_master_multi_data[handle].iic_getState_async_state = IIC_Result_Busy;
				result = IIC_Result_OK;
			} else {
				result = IIC_Result_Busy;
			}
		}
	}
	
	return result;
}

IIC_Result iic_read_async_multi(uint32 handle, uint8 addr, uint8 *data, uint32 size, uint32 freq) {
	IIC_Result result = IIC_Result_Error;
	
	if (handle < IIC_MASTER_MULTI_USERS) {
		if (data != NULL) {
			if (
				(iic_master_multi_data[handle].iic_getState_async_state == IIC_Result_OK) || 
				(iic_master_multi_data[handle].iic_getState_async_state == IIC_Result_Error)
			) {
				iic_master_multi_data[handle].operation = Iic_master_multi_operation_read;

				iic_master_multi_data[handle].iic_master_rx_addr = addr;
				iic_master_multi_data[handle].iic_master_read_size = size;
				iic_master_multi_data[handle].iic_buffer_master_rx = data;
				iic_master_multi_data[handle].iic_master_freq = freq;
				
				iic_master_multi_data[handle].iic_getState_async_state = IIC_Result_Busy;
				result = IIC_Result_OK;
			} else {
				result = IIC_Result_Busy;
			}
		}
	}
	return result;
}

IIC_Result iic_getState_async_multi(uint32 handle) {
	IIC_Result result = IIC_Result_Error;

	if (handle < IIC_MASTER_MULTI_USERS) {
		result = iic_master_multi_data[handle].iic_getState_async_state;
	}
	
	return result;
}
