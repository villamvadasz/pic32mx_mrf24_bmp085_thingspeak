#include <string.h>
#include "k_stdtype.h"
#include "rtc.h"
#include "daylight.h"

void rtc_UTCtoLocalTime(TimeDate *ptr, sint8 timeZone, uint8 useDayLightSaving) {
	if (ptr != NULL) {
		//Substracting timezone
		uint16 i = 0;
		uint16 cnt = 0;
		uint8 decrementTime = 0;
		if (timeZone > 0) {
			decrementTime = 1;
			cnt = timeZone;
		} else if (timeZone < 0) {
			decrementTime = 0;
			cnt = -timeZone;
		}
		for (i = 0; i < cnt; i++) {
			if (decrementTime) {
				rtc_inc_hour(ptr);
			} else {
				rtc_dec_hour(ptr);
			}
		}
		if (useDayLightSaving) {
			//Substracting daylight saving
			if (daylight_isDaylightSavings(ptr->year, ptr->month, ptr->day, ptr->hour, ptr->min, ptr->sec) == DayLightGui_Summer) {
				rtc_inc_hour(ptr);
			}
		}
	}
}

void rtc_LocalTimeToUTC(TimeDate *ptr, sint8 timeZone, uint8 useDayLightSaving) {
	if (ptr != NULL) {
		//Substracting timezone
		uint16 i = 0;
		uint16 cnt = 0;
		uint8 decrementTime = 0;
		if (timeZone > 0) {
			decrementTime = 1;
			cnt = timeZone;
		} else if (timeZone < 0) {
			decrementTime = 0;
			cnt = -timeZone;
		}
		for (i = 0; i < cnt; i++) {
			if (decrementTime) {
				rtc_dec_hour(ptr);
			} else {
				rtc_inc_hour(ptr);
			}
		}
		if (useDayLightSaving) {
			//Substracting daylight saving
			if (daylight_isDaylightSavings(ptr->year, ptr->month, ptr->day, ptr->hour, ptr->min, ptr->sec) == DayLightGui_Summer) {
				rtc_dec_hour(ptr);
			}
		}
	}
}
