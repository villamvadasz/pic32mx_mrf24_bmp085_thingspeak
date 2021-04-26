#ifndef _BME280_CONVERSION_H_
#define _BME280_CONVERSION_H_

	extern float convertPressureToAltitude(float sealevelPressure, float pressure);
	extern float calculateSeeLevelPressure(float pressure, float altitude);

#endif
