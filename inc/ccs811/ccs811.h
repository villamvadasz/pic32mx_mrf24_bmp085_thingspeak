#ifndef _CCS811_H_
#define _CCS811_H_

	extern double ccs811_get_CO2(void);
	extern double ccs811_get_TVOC(void);
	extern void ccs811_set_TemperatureAndHumidity(float temp, float humi);

	extern void init_ccs811(void);
	extern void do_ccs811(void);
	extern void isr_ccs811_1ms(void);

#endif
