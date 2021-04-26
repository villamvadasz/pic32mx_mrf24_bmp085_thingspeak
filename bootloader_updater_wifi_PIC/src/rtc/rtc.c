#include <string.h>
#include "rtc.h"

#define MONTH_MIN 1
#define MONTH_MAX 12
#define MONTH_LEAP 0

unsigned char do_sec1s = 0;
TimeDate timeDate = {0,42,19,2,1,2009,0,0};
const unsigned char day_in_month [13] = {29,31,28,31,30,31,30,31,31,30,31,30,31};

static unsigned int rtc_isDateValid(TimeDate *ptr);

void isr_rtc_1ms(void) {
	static unsigned int rtc1sCnt = 0;
	rtc1sCnt ++;
	if (rtc1sCnt >= 1000) {
		rtc1sCnt = 0;
		do_sec1s = 1;
	}
}

void isr_rtc_1s(void) {
	do_sec1s = 1;
}

unsigned char rtc_is_leap_year (unsigned int year) {
	unsigned char result = 0;
	if ((year % 400) == 0) {
		result = 1;
	} else {
		if ((year % 100) == 0) {
			result = 0;
		} else {
			if ((year % 4) == 0) {
				result = 1;
			} else {
				result = 0;
			}
		}
	}
	return result;
}

unsigned int rtc_get_day_in_year(unsigned int year) {
	unsigned int result = 1;
	if (rtc_is_leap_year(year)) {
		result = 366;
	} else {
		result = 365;
	}
	return result;
}

unsigned char rtc_get_day_in_month(unsigned int year, unsigned int month) {
	unsigned char result = 1;
	if ((month >= MONTH_MIN) && (month <= MONTH_MAX)) {
		if ((month == 2) && (rtc_is_leap_year(year) == 1)) {
			result = day_in_month[MONTH_LEAP];
		} else {
			result = day_in_month[month];
		}
	}
	return result;
}

void rtc_calendar(TimeDate *ptr) {
	if (ptr != NULL) {
		unsigned int x_year = 1900;
		unsigned int y_month = 1;

		if (ptr->year >= 2000) {
			ptr->dofw_calendar = 5;//first day of year 2000 Szombat
			for (x_year = 2000; x_year < ptr->year; x_year++) {
				for (y_month = 1; y_month <= 12; y_month ++) {
					ptr->dofw_calendar += rtc_get_day_in_month(x_year, y_month);
					ptr->dofw_calendar %= 7;
				}
			}
		}
		rtc_CalculateWeekAndDay(ptr);
	}
}

void init_rtc(void) {
	TimeDate timeDate;
	timeDate.sec = 0;
	timeDate.min = 37;
	timeDate.hour = 20;
	timeDate.day = 14;
	timeDate.month = 1;
	timeDate.year = 2020;
	rtc_SetTimeDate(&timeDate);
}

void do_rtc(void) {
	if (do_sec1s == 1) {
		do_sec1s = 0;
		//inc_sec(&timeDate);
		timeDate.sec++;
		if (timeDate.sec >= 60) {
			timeDate.sec = 0;
			timeDate.min++;
			if (timeDate.min >= 60) {
				timeDate.min = 0;
				timeDate.hour ++;
				if (timeDate.hour >= 24) {
					timeDate.hour = 0;
					timeDate.day++;
					if ((rtc_get_day_in_month(timeDate.year, timeDate.month) + 1) <= timeDate.day) {
						timeDate.day = 1;
						timeDate.month++;
						if (timeDate.month > 12) {
							timeDate.month = 1;
							timeDate.year ++;
						}
					}
					rtc_calendar(&timeDate);
				}
			}
		}
	}
}

unsigned int rtc_GetTimeDate(TimeDate *ptr) {
	unsigned int result = 0;
	if (ptr != NULL) {
		*ptr = timeDate;
		result = 1;
	}
	return result;
}

unsigned int rtc_SetTimeDate(TimeDate *ptr) {
	unsigned int result = 0;
	if (ptr != NULL) {
		if (rtc_isDateValid(ptr) != 0) {
			timeDate = *ptr;
			rtc_calendar(&timeDate);
			result = 1;
		}
	}
	return result;
}

static unsigned int rtc_isDateValid(TimeDate *ptr) {
	unsigned int result = 0;
	if (ptr != NULL) {
		if ((ptr->sec < 60) && (ptr->sec >= 0)) {
			if ((ptr->min < 60) && (ptr->min >= 0)) {
				if ((ptr->hour < 24) && (ptr->hour >= 0)) {
					if ((ptr->month <= 12) && (ptr->month >= 0)) {
						if ((ptr->day <= rtc_get_day_in_month(ptr->year, ptr->month)) && (ptr->day >= 0)) {
							result = 1;
						}
					}
				}
			}
		}
	}
	return result;
}

void rtc_inc_year(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->year ++;
		rtc_calendar(ptr);
	}
}

void rtc_dec_year(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->year --;
		rtc_calendar(ptr);
	}
}

void rtc_inc_month(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->month++;
		if (ptr->month > 12) {
			ptr->month = 1;
			rtc_inc_year(ptr);
		} else {
			rtc_calendar(ptr);
		}
	}
}

void rtc_dec_month(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->month--;
		if (ptr->month < 1) {
			rtc_dec_year(ptr);
			ptr->month = 12;
		} else {
			rtc_calendar(ptr);
		}
	}
}


void rtc_inc_day(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->day++;
		if (ptr->day >= (rtc_get_day_in_month(ptr->year, ptr->month)+1)) {
			ptr->day = 1;
			rtc_inc_month(ptr);
		} else {
			rtc_calendar(ptr);
		}
	}
}

void rtc_dec_day(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->day--;
		if (ptr->day < 1) {
			rtc_dec_month(ptr);
			ptr->day = rtc_get_day_in_month(ptr->year, ptr->month);
		} else {
			rtc_calendar(ptr);
		}
	}
}

void rtc_inc_hour(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->hour++;
		if (ptr->hour >= 24) {
			ptr->hour = 0;
			rtc_inc_day(ptr);
		}
	}
}

void rtc_dec_hour(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->hour--;
		if (ptr->hour < 0) {
			ptr->hour = 23;
			rtc_dec_day(ptr);
		}
	}
}

void rtc_inc_min(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->min++;
		if (ptr->min >= 60) {
			ptr->min = 0;
			rtc_inc_hour(ptr);
		}
	}
}

void rtc_dec_min(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->min--;
		if (ptr->min < 0) {
			ptr->min = 59;
			rtc_dec_hour(ptr);
		}
	}
}

void rtc_inc_sec(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->sec++;
		if (ptr->sec >= 60) {
			ptr->sec = 0;
			rtc_inc_min(ptr);
		}
	}
}

void rtc_dec_sec(TimeDate *ptr) {
	if (ptr != NULL) {
		ptr->sec--;
		if (ptr->sec < 0) {
			ptr->sec = 59;
			rtc_dec_min(ptr);
		}
	}
}

void rtc_CalculateWeekAndDay(TimeDate *ptr) {
	if (ptr != NULL) {
		unsigned char i = 0;
		ptr->week_calendar = 0;
		if (ptr->dofw_calendar < 3) {
			ptr->week_calendar ++;
		}

		for (i = 1; i < ptr->month; i++) {
			ptr->dofw_calendar += rtc_get_day_in_month(ptr->year, i) % 7;
			ptr->week_calendar += rtc_get_day_in_month(ptr->year, i) / 7;
		}
		ptr->dofw_calendar += (ptr->day - 1) % 7;
		ptr->week_calendar += (ptr->day - 1) / 7;
		ptr->week_calendar += ptr->dofw_calendar / 7;
		ptr->dofw_calendar = ptr->dofw_calendar % 7;
	}
}

void rtc_CalculateNtpToDate(uint32 ntp_seconds, TimeDate *ptr) {
	if (ptr != NULL) {
		uint32 days = 0;
		
		days = ntp_seconds / 86400;
		ntp_seconds -= (days * 86400);
		ptr->hour = ntp_seconds / 3600;
		ntp_seconds -= (ptr->hour * 3600);
		ptr->min = ntp_seconds / 60;
		ntp_seconds -= (ptr->min * 60);
		ptr->sec = ntp_seconds;
		
		ptr->year = 1970;
		while (1) {
			unsigned int days_in_year = rtc_get_day_in_year(ptr->year);
			if (days_in_year <= days) {
				ptr->year++;
				days -= days_in_year;
			} else {
				break;
			}
		}

		ptr->month = 1;
		while (1) {
			unsigned char days_in_month = rtc_get_day_in_month(ptr->year, ptr->month);
			if (days_in_month <= days) {
				ptr->month++;
				days -= days_in_month;
			} else {
				break;
			}
		}
        ptr->day = 1;
		ptr->day += days;
		rtc_calendar(ptr);
		
		rtc_UTCtoLocalTime(ptr, 1, 1);
		
	}
}
