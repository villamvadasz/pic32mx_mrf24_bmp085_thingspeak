#include <math.h>
#include "bme280_conversion.h"

float convertPressureToAltitude(float sealevelPressure, float pressure) {
	float altitude = 0.0;
	altitude = 44330.0 * (1.0 - pow(pressure / sealevelPressure, 0.1903));
	return altitude;
}

float calculateSeeLevelPressure(float pressure, float altitude) {
	float sealevelPressure = 0.0;
	sealevelPressure = pressure / pow(1.0 - (altitude / 44330.0), 5.255);
	return sealevelPressure;
}
