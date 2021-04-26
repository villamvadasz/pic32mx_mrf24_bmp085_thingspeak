#include <stdio.h>
#include "iic_master.h"
#include "c_iic_master.h"

#include "mal.h"
#include "k_stdtype.h"
#include "tmr.h"

#define IIC_ACK		0
#define IIC_NACK	1

#define SDA_HIZ()	IIC_SDA_TRIS = 1;\
					IIC_PORT_SYNC()

#define SCL_HIZ() 	IIC_SCL_TRIS = 1;\
					IIC_PORT_SYNC()

#define SDA_LO()	IIC_SDA_LAT = 0;\
					IIC_PORT_SYNC();\
					IIC_SDA_TRIS = 0;\
					IIC_PORT_SYNC()

#define SCL_LO() 	IIC_SCL_LAT = 0;\
					IIC_PORT_SYNC();\
					IIC_SCL_TRIS = 0;\
					IIC_PORT_SYNC()

typedef enum _IIC_master_states {
	IIC_master_states_Idle = 0,
	IIC_master_states_Start,
	IIC_master_states_Addr,
	IIC_master_states_Data,
	IIC_master_states_Stop,
	IIC_master_states_Finished_ACK,
	IIC_master_states_Finished_Stop_NACK,
	IIC_master_states_Finished_NACK,
} IIC_master_states;

static uint8 i2c_start_async(void);
static uint8 i2c_stop_async(void);
static uint8 i2c_rx_async(uint8 *data, uint8 ack);
static uint8 i2c_tx_async(uint8 d);
static uint8 IIC_TX_BIT(uint8 b);
static uint8 IIC_RX_BIT(void);

uint8 *iic_buffer_master_rx = NULL;
uint8 *iic_buffer_master_tx = NULL;
uint32 missedRxCharI2C = 0;
uint32 missedTxCharI2C = 0;

uint8 iic_master_tx_addr = 0;
uint8 iic_master_repeat = 0;

IIC_master_states iic_master_write_state = IIC_master_states_Idle;
IIC_master_states iic_master_read_state = IIC_master_states_Idle;
uint32 iic_master_read_size = 0;
uint32 iic_master_read_size_current = 0;
uint32 iic_master_write_size = 0;
uint32 iic_master_write_size_current = 0;
volatile uint32 do_iic_master_1ms = 0;
volatile uint32 do_iic_master_100us = 0;
volatile uint32 do_iic_master_10us = 0;
uint8 do_iic_master_task = 0;
uint8 iic_master_tmp_data = 0;
uint8 iic_delay_debug = 0;
#define IIC_DELAY_DEBUG_CNT 0

uint8 i2c_start_async_cnt = 0;
uint8 i2c_stop_async_cnt = 0;
uint8 i2c_tx_async_cnt = 0;
uint8 i2c_rx_async_cnt = 0;
uint8 IIC_TX_BIT_cnt = 0;
uint8 IIC_RX_BIT_cnt = 0;
IIC_Result iic_getState_async_state = IIC_Result_Error;
uint32 iic_master_freq = 1000000;

void init_iic_master(void) {
	IIC_MAL_CONFIG();
	
	IIC_SDA_TRIS = 1;
	IIC_SCL_TRIS = 1;
	IIC_SCL_LAT = 0;
	IIC_SDA_LAT = 0;
	
	IIC_PORT_SYNC();
}

void deinit_iic_master(void) {
	IIC_MAL_CONFIG();
	
	IIC_SDA_TRIS = 1;
	IIC_SCL_TRIS = 1;
	
	IIC_PORT_SYNC();
}

void do_iic_master(void) {
	if (do_iic_master_10us || do_iic_master_100us || do_iic_master_1ms) {
		static uint8 do_iic_master_taskCnt = 0;
		do_iic_master_10us = 0;
		do_iic_master_100us = 0;
		do_iic_master_1ms = 0;
		
		do_iic_master_taskCnt++;
		if (do_iic_master_taskCnt >= IIC_TASK_CNT) {
			do_iic_master_taskCnt = 0;
			do_iic_master_task = 1;
		}
		
	}
	if (do_iic_master_task) {
		#ifndef IIC_MASTER_POLL_EVERY_CYCLE
			do_iic_master_task = 0;
		#endif
		if (iic_master_read_state == IIC_master_states_Idle) {
			switch (iic_master_write_state) {
				case IIC_master_states_Idle : {
					i2c_start_async_cnt = 0;
					i2c_stop_async_cnt = 0;
					break;
				}
				case IIC_master_states_Start : {
					if (i2c_start_async() != 0) {
						i2c_tx_async_cnt = 0;
						iic_master_write_state = IIC_master_states_Addr;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Addr : {
					uint8 retVal = 0;
					uint8 addrByte = iic_master_tx_addr;
					iic_delay_debug = IIC_DELAY_DEBUG_CNT;
					addrByte = ((addrByte << 1) & 0b11111110);	//lsb is 0 because write
					retVal = i2c_tx_async(addrByte);
					
					if (retVal == (1 + IIC_NACK)) {
						iic_master_write_state = IIC_master_states_Finished_Stop_NACK;
					} else if (retVal == 0) {
					} else if (retVal == (1 + IIC_ACK)) {
						if (iic_master_write_size_current < iic_master_write_size) {
							i2c_tx_async_cnt = 0;
							iic_master_tmp_data = iic_buffer_master_tx[iic_master_write_size_current++];
							iic_master_write_state = IIC_master_states_Data;
						} else {
							iic_master_write_state = IIC_master_states_Finished_Stop_NACK;
						}
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Data : {
					if (iic_delay_debug != 0) {
						iic_delay_debug --;
					}
					if (iic_delay_debug == 0) {
						uint8 retVal = 0;
						retVal = i2c_tx_async(iic_master_tmp_data);
						if (retVal == (1 + IIC_NACK)) {
							iic_master_write_state = IIC_master_states_Finished_Stop_NACK;
						} else if (retVal == 0) {
						} else if (retVal == (1 + IIC_ACK)) {
							if (iic_master_write_size_current < iic_master_write_size) {
								i2c_tx_async_cnt = 0;
								iic_master_tmp_data = iic_buffer_master_tx[iic_master_write_size_current++];
								iic_delay_debug = IIC_DELAY_DEBUG_CNT;
							} else {
								iic_master_write_state = IIC_master_states_Stop;
							}
						}
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Stop : {
					if (iic_master_repeat == 0) {
						if (i2c_stop_async() != 0) { //no repated start condition, so stop will be generated.
							iic_master_write_state = IIC_master_states_Finished_ACK;
						}
					} else {
						iic_master_write_state = IIC_master_states_Finished_ACK;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Finished_ACK : {
					iic_master_write_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_OK;
					break;
				}
				case IIC_master_states_Finished_Stop_NACK : {
					if (iic_master_repeat == 0) {
						if (i2c_stop_async() != 0) {; //no repated start condition, so stop will be generated.
							iic_master_write_state = IIC_master_states_Finished_NACK;
						}
					} else {
						iic_master_write_state = IIC_master_states_Finished_NACK;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Finished_NACK : {
					iic_master_write_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_Error;
					break;
				}
				default : {
					iic_buffer_master_tx = NULL;
					iic_master_write_size = 0;
					iic_master_write_size_current = 0;
					iic_master_write_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_Error;
					break;
				}
			}
		}
		if (iic_master_write_state == IIC_master_states_Idle) {
			switch (iic_master_read_state) {
				case IIC_master_states_Idle : {
					i2c_start_async_cnt = 0;
					i2c_stop_async_cnt = 0;
					break;
				}
				case IIC_master_states_Start : {
					iic_master_read_size_current = 0;
					if (i2c_start_async() != 0) {
						i2c_tx_async_cnt = 0;
						iic_master_read_state = IIC_master_states_Addr;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Addr : {
					uint8 retVal = 0;
					uint8 addrByte = iic_master_tx_addr;
					iic_delay_debug = IIC_DELAY_DEBUG_CNT;
					addrByte = ((addrByte << 1) & 0b11111110);	//lsb is 1 because read
					addrByte |= 0b00000001;
					retVal = i2c_tx_async(addrByte);
					if (retVal == (1 + IIC_NACK)) {
						iic_master_read_state = IIC_master_states_Finished_Stop_NACK;
					} else if (retVal == 0) {
					} else if (retVal == (1 + IIC_ACK)) {
						i2c_rx_async_cnt = 0;
						iic_master_read_state = IIC_master_states_Data;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Data : {
					if (iic_delay_debug != 0) {
						iic_delay_debug --;
					}
					if (iic_delay_debug == 0) {
						uint8 retVal = 0;
						uint8 data = 0;
						uint8 ackBit = 0;
						if (iic_master_read_size_current < (iic_master_read_size - 1)) {
							ackBit = IIC_ACK;
						} else {
							ackBit = IIC_NACK;
						}
						retVal = i2c_rx_async(&data, ackBit);
						if (retVal == (1 + IIC_NACK)) {
							iic_master_read_state = IIC_master_states_Finished_Stop_NACK;
						} else if (retVal == 0) {
						} else if (retVal == (1 + IIC_ACK)) {
							i2c_rx_async_cnt = 0;
							if (ackBit == IIC_NACK) {
								iic_master_read_state = IIC_master_states_Stop;
							}
							if (iic_master_read_size_current < iic_master_read_size) {
								iic_buffer_master_rx[iic_master_read_size_current] = data;
								iic_delay_debug = IIC_DELAY_DEBUG_CNT;
							} else {
								iic_master_read_state = IIC_master_states_Finished_Stop_NACK;
							}
							iic_master_read_size_current++;
						}
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Stop : {
					if (iic_master_repeat == 0) {
						if (i2c_stop_async() != 0) { //no repated start condition, so stop will be generated.
							iic_master_read_state = IIC_master_states_Finished_ACK;
						}
					} else {
						iic_master_read_state = IIC_master_states_Finished_ACK;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Finished_ACK : {
					iic_master_read_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_OK;
					break;
				}
				case IIC_master_states_Finished_Stop_NACK : {
					if (iic_master_repeat == 0) {
						if (i2c_stop_async() != 0) { //no repated start condition, so stop will be generated.
							iic_master_read_state = IIC_master_states_Finished_NACK;
						}
					} else {
						iic_master_read_state = IIC_master_states_Finished_NACK;
					}
					iic_getState_async_state = IIC_Result_Busy;
					break;
				}
				case IIC_master_states_Finished_NACK : {
					iic_master_read_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_Error;
					break;
				}
				default : {
					iic_buffer_master_rx = NULL;
					iic_master_read_size = 0;
					iic_master_read_size_current = 0;
					iic_master_read_state = IIC_master_states_Idle;
					iic_getState_async_state = IIC_Result_Error;
					break;
				}
			}
		}
	}
}

void isr_iic_master_1ms(void) {
	do_iic_master_1ms = 1;
}

void isr_iic_master_100us(void) {
	do_iic_master_100us = 1;
}

void isr_iic_master_10us(void) {
	do_iic_master_10us = 1;
}

void isr_iic_master(void) {
	//not used
}

IIC_Result iic_write_async(uint8 addr, uint8 *data, uint32 size, uint8 repeat, uint32 freq) {
	IIC_Result result = IIC_Result_Error;
	
	if (data != NULL) {
		if (
			(iic_master_read_state == IIC_master_states_Idle) && 
			(iic_master_write_state == IIC_master_states_Idle)
		) {
			i2c_start_async_cnt = 0;
			i2c_stop_async_cnt = 0;
			iic_master_tx_addr = addr;
			iic_master_repeat = repeat;			
			iic_master_write_size = size;
			iic_master_write_size_current = 0;
			iic_buffer_master_tx = data;
			iic_master_write_state = IIC_master_states_Start;
			iic_master_freq = freq;

			iic_getState_async_state = IIC_Result_Busy;
			result = IIC_Result_OK;
		} else {
			result = IIC_Result_Busy;
		}
	}
	
	return result;
}

IIC_Result iic_read_async(uint8 addr, uint8 *data, uint32 size, uint32 freq) {
	IIC_Result result = IIC_Result_Error;
	
	if (data != NULL) {
		if (
			(iic_master_read_state == IIC_master_states_Idle) && 
			(iic_master_write_state == IIC_master_states_Idle)
		) {
			i2c_start_async_cnt = 0;
			i2c_stop_async_cnt = 0;
			iic_master_tx_addr = addr;
			iic_master_read_size = size;
			iic_master_read_size_current = 0;
			iic_master_read_state = IIC_master_states_Start;
			iic_buffer_master_rx = data;
			iic_master_freq = freq;
			
			iic_getState_async_state = IIC_Result_Busy;
			result = IIC_Result_OK;
		} else {
			result = IIC_Result_Busy;
		}
	}
	return result;
}

IIC_Result iic_getState_async(void) {
	IIC_Result result = IIC_Result_Error;
	
	result = iic_getState_async_state;
	
	return result;
}

static uint8 i2c_start_async(void) {
	uint8 result = 0;
	switch (i2c_start_async_cnt) {
		case 0 : {
			SDA_HIZ();	//hhh|HHH|HHH|LLL|LLL|
			i2c_start_async_cnt++;
			break;
		}
		case 1 : {
			SCL_HIZ();	//hhh|hhh|HHH|HHH|LLL|
			i2c_start_async_cnt++;
			break;
		}
		case 2 : {
			SDA_LO();
			i2c_start_async_cnt++;
			break;
		}
		case 3 : {
			SCL_LO();
			result = 1;
			i2c_start_async_cnt++;
			break;
		}
		default : {
			result = 1;
			break;
		}
	}
	return result;
}

static uint8 i2c_stop_async(void) {
	uint8 result = 0;
	switch (i2c_stop_async_cnt) {
		case 0 : {
			SDA_LO();
			i2c_stop_async_cnt++;
			break;
		}
		case 1 : {
			SCL_HIZ();
			i2c_stop_async_cnt++;
			break;
		}
		case 2 : {
			SDA_HIZ();
			result = 1;
			i2c_stop_async_cnt++;
			break;
		}
		default : {
			result = 1;
			break;
		}
	}
	return result;
}

static uint8 i2c_rx_async(uint8 *data, uint8 ack) {
	static uint8 temp = 0;
	uint8 result = 0;
	switch (i2c_rx_async_cnt) {
		case 0 : {
			temp = 0;
			SDA_HIZ();
			IIC_RX_BIT_cnt = 0;
			i2c_rx_async_cnt++;
			i2c_rx_async_cnt++;
			break;
		}
		case 2 + 0 : 
		case 2 + 1 : 
		case 2 + 2 : 
		case 2 + 3 : 
		case 2 + 4 : 
		case 2 + 5 : 
		case 2 + 6 : 
		case 2 + 7 : {
			{
				uint8 retVal = IIC_RX_BIT();
				if (retVal == 0) {
				} else if (retVal == (1 + 0)) { //0
					temp <<= 1;
					IIC_RX_BIT_cnt = 0;
					IIC_TX_BIT_cnt = 0;
					i2c_rx_async_cnt++;
				} else if (retVal == (1 + 1)) { // 1
					temp <<= 1;
					temp |= 1;
					IIC_RX_BIT_cnt = 0;
					IIC_TX_BIT_cnt = 0;
					i2c_rx_async_cnt++;
				}
			}
			break;
		}
		case 3 + 7 : {
			*data = temp;
			if (ack == IIC_ACK) {
				//IIC_TX_BIT_0
				uint8 retVal = IIC_TX_BIT(0);
				if (retVal == 0) {
				} else if (retVal != 0) {
					IIC_TX_BIT_cnt = 0;
					result = 1 + IIC_ACK;
				}
			} else {
				//IIC_TX_BIT_1
				uint8 retVal = IIC_TX_BIT(1);
				if (retVal == 0) {
				} else if (retVal != 0) {
					IIC_TX_BIT_cnt = 0;
					result = 1 + IIC_ACK;
				}
			}
			break;
		}
		case 16 : {
			result = 1 + IIC_NACK;
			break;
		}
		default : {
			result = 1 + IIC_NACK;
			break;
		}
	}
	return result;
}

static uint8 i2c_tx_async(uint8 d) {
	static uint8 tempD = 0;
	uint8 result = 0;
	switch (i2c_tx_async_cnt) {
		case 0 : {
			IIC_TX_BIT_cnt = 0;
			tempD = d;
			i2c_tx_async_cnt++;
		}
		case 1 + 0 : 
		case 1 + 1 : 
		case 1 + 2 : 
		case 1 + 3 : 
		case 1 + 4 : 
		case 1 + 5 : 
		case 1 + 6 : 
		case 1 + 7 : {
			if(tempD & 0x80) {
				//IIC_TX_BIT_1
				uint8 retVal = IIC_TX_BIT(1);
				if (retVal == 0) {
				} else if (retVal != 0) {
					tempD <<= 1;
					IIC_RX_BIT_cnt = 0;
					IIC_TX_BIT_cnt = 0;
					i2c_tx_async_cnt++;
				}
			} else {
				//IIC_TX_BIT_0
				uint8 retVal = IIC_TX_BIT(0);
				if (retVal == 0) {
				} else if (retVal != 0) {
					tempD <<= 1;
					IIC_RX_BIT_cnt = 0;
					IIC_TX_BIT_cnt = 0;
					i2c_tx_async_cnt++;
				}
			}
			break;
		}
		case 1 + 8 : {
			{
				uint8 retVal = IIC_RX_BIT();
				if (retVal == 0) {
				} else if (retVal == (1 + 0)) { //0
					result = 1 + 0;
					IIC_RX_BIT_cnt = 0;
				} else if (retVal == (1 + 1)) { // 1
					result = 1 + 1;
					IIC_RX_BIT_cnt = 0;
				}
			}
			break;
		}
		default : {
			result = 1 + IIC_NACK;
			break;
		}
	}
	return result;
}

static uint8 IIC_TX_BIT(uint8 b) {
	uint8 result = 0;
	switch (IIC_TX_BIT_cnt) {
		case 0 : {
			if (b == 0) {
				SDA_LO();
			} else {
				SDA_HIZ();
			}
			IIC_TX_BIT_cnt++;
			break;
		}
		case 1 : {
			SCL_HIZ();
			IIC_TX_BIT_cnt++;
			break;
		}
		case 2 : {
			if (IIC_SCL_PORT) {
				IIC_TX_BIT_cnt++;
			}
			break;
		}
		case 3 : {
			SCL_LO();
			IIC_TX_BIT_cnt++;
			break;
		}
		case 4 : {
			//SDA_HIZ();
			result = 1;
			break;
		}
		default : {
			result = 1;
			break;
		}
	}
	return result;
}

static uint8 IIC_RX_BIT(void) {
	static uint8 b = 0;
	uint8 result = 0;
	switch (IIC_RX_BIT_cnt) {
		case 0 : {
			b = 0;
			SDA_HIZ();
			IIC_RX_BIT_cnt++;
			break;
		}
		case 1 : {
			SCL_HIZ();
			IIC_RX_BIT_cnt++;
			break;
		}
		case 2 : {
			if (IIC_SCL_PORT) {
				IIC_RX_BIT_cnt++;
			}
			break;
		}
		case 3 : {
			b = IIC_SDA_PORT;
			SCL_LO();
			IIC_RX_BIT_cnt++;
			break;
		}
		case 4 : {
			result = 1 + b;
			break;
		}
		default : {
			result = 1 + 0;
			break;
		}
	}
	return result;
}
