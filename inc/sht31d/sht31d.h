#ifndef _SHT31_H_
#define _SHT31_H_

	extern float sht31d_getTemp(void);
	extern float sht31d_getHumidity(void);

	extern void init_sht31d(void);
	extern void do_sht31d(void);
	extern void isr_sht31d_1ms(void);

#endif
