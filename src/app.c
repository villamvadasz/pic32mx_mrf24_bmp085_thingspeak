#include <string.h>
#include <stdlib.h>
#include "app.h"
#include "mal.h"

#include "k_stdtype.h"
#include "sleep.h"
#include "ad.h"
#include "bme280.h"
#include "sht31d.h"
#include "ccs811.h"

#define APP_SEND_MEASUREMENT_TIME (20) //[min]

volatile unsigned int do_app_10ms = 0;
volatile unsigned int do_app_1000ms = 0;
float app_Temperature = 0.0f;
float app_Pressure = 0.0f;
float app_Humiditiy = 0.0f;
float app_CO2 = 0.0f;
float app_LiPo_Voltage = 0.0f;
float app_LiPo_Percentage = 0.0f;
unsigned int app_BootloaderTrigger = 0;
float app_LiPoVoltage_To_Percentage(float voltage);

void init_app(void) {
	init_thingspeak();
	app_thingspeak_send_measurement(20.0f, 1040.0f, 62.0f, 480.0f, 4.2f, 1.0f, 2.0f, 3.0f);
}

void do_app(void) {
	static unsigned char appSingleShoot = 1;
	do_app_thingspeak();
	if (appSingleShoot) {
		appSingleShoot = 0;
	}
	if (do_app_10ms) {
		do_app_10ms = 0;
		{
			app_Temperature = getBME280Temp();
			app_Pressure = getBME280PressureAtSeeLevel(386.0f);
			app_Humiditiy = getBME280Humidity();
			app_CO2 = ccs811_get_CO2();
		}
		{
			uint16 resultAd = 0;
			resultAd = getAd(0);
			app_LiPo_Voltage = resultAd;
			app_LiPo_Voltage *= 4.0; //Resistor divider
			app_LiPo_Voltage *= 3.3; //Analog reference voltage
			app_LiPo_Voltage /= 1024.0;//10 bit
			
			app_LiPo_Percentage = app_LiPoVoltage_To_Percentage(app_LiPo_Voltage);
		}
	}
	if (do_app_1000ms) {
		do_app_1000ms = 0;
		{
			static unsigned int app_send_measurement = (APP_SEND_MEASUREMENT_TIME * 60);
			app_send_measurement++;
			if (app_send_measurement >= APP_SEND_MEASUREMENT_TIME * 60) {
				app_send_measurement = 0;
				{
					float temperature = getBME280Temp();
					float pressure = getBME280PressureAtSeeLevel(386.0f);
					float humidity = getBME280Humidity();
					float CO2 = ccs811_get_CO2();
					float LiPoVoltage = app_LiPo_Voltage;
					float res1 = 1.0f;
					float res2 = 2.0f;
					float res3 = 3.0f;
					ccs811_set_TemperatureAndHumidity(temperature, humidity);
					app_thingspeak_send_measurement(temperature, pressure, humidity, CO2, LiPoVoltage, res1, res2, res3);
				}
			}
		}
	}
}

void isr_app_1ms(void) {
	isr_app_thingspeak_1ms();
	{
		static unsigned int app_10ms_cnt = 0;
		app_10ms_cnt++;
		if (app_10ms_cnt >= 10) {
			app_10ms_cnt = 0;
			do_app_10ms = 1;
		}
	}
	{
		static unsigned int app_1000ms_cnt = 0;
		app_1000ms_cnt++;
		if (app_1000ms_cnt >= 1000) {
			app_1000ms_cnt = 0;
			do_app_1000ms = 1;
		}
	}
}

void isr_app_100us(void) {
}

void isr_app_custom(void) {
}

uint8 backToSleep(void) {
	uint8 result = 0;
	return result;
}

void eepManager_NotifyUserFailedRead(int item, uint8 type) {
}

float app_LiPoVoltage_To_Percentage(float voltage) {
	float result = 0.0f;
	if (voltage <= 3.27f) {
		result = 0.0f;
	} else if (voltage <= 3.61f) {
		result = 5.0f;
	} else if (voltage <= 3.69f) {
		result = 10.0f;
	} else if (voltage <= 3.71f) {
		result = 15.0f;
	} else if (voltage <= 3.73f) {
		result = 20.0f;
	} else if (voltage <= 3.75f) {
		result = 25.0f;
	} else if (voltage <= 3.77f) {
		result = 30.0f;
	} else if (voltage <= 3.79f) {
		result = 35.0f;
	} else if (voltage <= 3.80f) {
		result = 40.0f;
	} else if (voltage <= 3.82f) {
		result = 45.0f;
	} else if (voltage <= 3.84f) {
		result = 50.0f;
	} else if (voltage <= 3.85f) {
		result = 55.0f;
	} else if (voltage <= 3.87f) {
		result = 60.0f;
	} else if (voltage <= 3.91f) {
		result = 65.0f;
	} else if (voltage <= 3.95f) {
		result = 70.0f;
	} else if (voltage <= 3.98f) {
		result = 75.0f;
	} else if (voltage <= 4.02f) {
		result = 80.0f;
	} else if (voltage <= 4.08f) {
		result = 85.0f;
	} else if (voltage <= 4.11f) {
		result = 90.0f;
	} else if (voltage <= 4.15f) {
		result = 95.0f;
	} else if (voltage <= 4.20f) {
		result = 100.0f;
	} else {
		result = 100.0f;
	}
	return result;
}
