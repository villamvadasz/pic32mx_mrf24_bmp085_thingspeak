#ifndef _APP_H_
#define _APP_H_

	extern float app_LiPo_Voltage;
	extern float app_LiPo_Percentage;
	extern float app_Temperature;
	extern float app_Pressure;
	extern float app_Humiditiy;
	extern float app_CO2;
	extern unsigned int app_BootloaderTrigger;

	extern void app_thingspeak_send_measurement(float temperature, float pressure, float humidity, float CO2, float LiPoVoltage, float res1, float res2, float res3);

	extern void init_app(void);
	extern void do_app(void);

	extern void isr_app_1ms(void);
	extern void isr_app_100us(void);
	extern void isr_app_custom(void);
	extern void isr_t4(void);

	extern void init_thingspeak(void);
	extern void do_app_thingspeak(void);
	extern void isr_app_thingspeak_1ms(void);

#endif
