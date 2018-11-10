/*
 * RTC.h
 *
 *  Created on: Nov 7, 2018
 *      Author: Andy
 */

#ifndef RTC_H_
#define RTC_H_

#include "Bits.h"

/*Addresses*/
#define RTC_ADDRESS 		0xDE
#define RTC_SLAVE_ADDRESS	0xDF
#define RTC_SECONDS 		0x00
#define RTC_MINUTES 		0x01
#define RTC_HOURS			0x02
#define RTC_WEEKDAY 		0x03
#define RTC_DAY 			0x04
#define RTC_MONTH 			0x05
#define RTC_YEAR 			0x06
/*Init mask*/
#define RTC_INIT 			0x80

/*Enable oscillator*/
void RTC_init();


/*Set Time and Date*/
void set_seconds(uint8 second);
void set_minutes(uint8 minute);
void set_hours(uint8 hour);
void set_weekday(uint8 weekday);
void set_day(uint8 day);
void set_month(uint8 month);
void set_year(uint8 year);

/*Get Time and Date*/
uint8 get_seconds();
uint8 get_minutes();
uint8 get_hours();
uint8 get_weekday();
uint8 get_day();
uint8 get_month();
uint8 get_year();

#endif /* RTC_H_ */
