#ifndef _RTC_H_
#define _RTC_H_

	#include "k_stdtype.h"

	typedef struct _TimeDate {
		signed char sec;
		signed char min;
		signed char hour;
		signed char day;
		signed char month;
		signed int year;
		unsigned char dofw_calendar;
		unsigned char week_calendar;
	} TimeDate;

	extern unsigned int rtc_GetTimeDate(TimeDate *ptr);
	extern unsigned int rtc_SetTimeDate(TimeDate *ptr);

	extern void rtc_inc_year(TimeDate *ptr);
	extern void rtc_dec_year(TimeDate *ptr);
	extern void rtc_inc_month(TimeDate *ptr);
	extern void rtc_dec_month(TimeDate *ptr);
	extern void rtc_inc_day(TimeDate *ptr);
	extern void rtc_dec_day(TimeDate *ptr);
	extern void rtc_inc_hour(TimeDate *ptr);
	extern void rtc_dec_hour(TimeDate *ptr);
	extern void rtc_inc_min(TimeDate *ptr);
	extern void rtc_dec_min(TimeDate *ptr);
	extern void rtc_inc_sec(TimeDate *ptr);
	extern void rtc_dec_sec(TimeDate *ptr);

	extern void rtc_CalculateWeekAndDay(TimeDate *ptr);

	extern void rtc_UTCtoLocalTime(TimeDate *ptr, sint8 timeZone, uint8 useDayLightSaving);
	extern void rtc_LocalTimeToUTC(TimeDate *ptr, sint8 timeZone, uint8 useDayLightSaving);

	extern void rtc_calendar(TimeDate *ptr);

	extern void rtc_CalculateNtpToDate(uint32 ntp_seconds, TimeDate *ptr);
	extern unsigned char rtc_is_leap_year(unsigned int year);
	extern unsigned int rtc_get_day_in_year(unsigned int year);
	extern unsigned char rtc_get_day_in_month(unsigned int year, unsigned int month);

	extern void init_rtc(void);
	extern void do_rtc(void);
	extern void isr_rtc_1ms(void);
	extern void isr_rtc_1s(void);

	
#endif
