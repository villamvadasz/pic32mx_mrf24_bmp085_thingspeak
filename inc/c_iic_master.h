#ifndef _C_IIC_MASTER_H_
#define _C_IIC_MASTER_H_

	#define IIC_PORT_SYNC() MAL_SYNC()
	//#define IIC_PORT_SYNC() Nop();Nop();Nop();Nop()

	#define IIC_MAL_CONFIG()     	CNPUEbits.CNPUE15 = 1;\
									CNPUEbits.CNPUE16 = 1;

	#define IIC_TASK_CNT 1
	
	#define IIC_SCL_PORT	PORTDbits.RD6
	#define IIC_SCL_TRIS	TRISDbits.TRISD6
	#define IIC_SCL_LAT		LATDbits.LATD6

	#define IIC_SDA_PORT	PORTDbits.RD7
	#define IIC_SDA_TRIS	TRISDbits.TRISD7
	#define IIC_SDA_LAT		LATDbits.LATD7

#endif
