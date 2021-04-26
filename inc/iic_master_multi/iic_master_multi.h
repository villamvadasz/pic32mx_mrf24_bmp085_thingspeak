#ifndef _IIC_MASTER_MULTI_H_
#define _IIC_MASTER_MULTI_H_

	#include "k_stdtype.h"
	#include "iic_master.h"

	extern IIC_Result iic_write_async_multi(uint32 handle, uint8 addr, uint8 *data, uint32 size, uint8 repeat, uint32 freq);
	extern IIC_Result iic_read_async_multi(uint32 handle, uint8 addr, uint8 *data, uint32 size, uint32 freq);
	extern IIC_Result iic_getState_async_multi(uint32 handle);

	extern void init_iic_master_multi(void);
	extern void deinit_iic_master_multi(void);
	extern void do_iic_master_multi(void);
	extern void isr_iic_master_multi_1ms(void);
	extern void isr_iic_master_multi_100us(void);

#endif
