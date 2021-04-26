#ifndef _IIC_MASTER_H_
#define _IIC_MASTER_H_

	#include "k_stdtype.h"

	typedef enum _IIC_Result {
		IIC_Result_Error = 0,//NACK
		IIC_Result_Busy = 1,
		IIC_Result_OK = 3,//ACK
	} IIC_Result;

	extern IIC_Result iic_write_async(uint8 addr, uint8 *data, uint32 size, uint8 repeat, uint32 freq);
	extern IIC_Result iic_read_async(uint8 addr, uint8 *data, uint32 size, uint32 freq);
	extern IIC_Result iic_getState_async(void);


	extern void init_iic_master(void);
	extern void deinit_iic_master(void);
	extern void do_iic_master(void);
	extern void isr_iic_master_1ms(void);
	extern void isr_iic_master_100us(void);
	extern void isr_iic_master_10us(void);
	extern void isr_iic_master(void);


#endif
