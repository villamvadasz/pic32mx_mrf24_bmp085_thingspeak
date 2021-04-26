#ifndef _BME280_H_
#define _BME280_H_

	extern float getBME280Temp(void);
	extern float getBME280Pressure(void);
	extern float getBME280Altitude(void);
	extern float getBME280Humidity(void);
	extern float getBME280PressureAtSeeLevel(float altitude);
	
	extern void init_bme280(void);
	extern void deinit_bme280(void);
	extern void do_bme280(void);
	extern void isr_bme280_1ms(void);

#endif
