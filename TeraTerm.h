/*
 * TeraTerm.h
 *
 *  Created on: Nov 10, 2018
 *      Author: Andy
 */

#ifndef TERATERM_H_
#define TERATERM_H_

#include "Bits.h"

typedef struct{
	uint8 hour_decimal;
	uint8 hour_unit;
	uint8 minute_decimal;
	uint8 minute_unit;
	uint8 second_decimal;
	uint8 second_unit;
}TERATERM_clock_t;

typedef struct{
	uint8 weekday;
	uint8 day_decimal;
	uint8 day_unit;
	uint8 month_decimal;
	uint8 month_unit;
	uint8 year_decimal;
	uint8 year_unit;
}TERATERM_calendar_t;

void TERATERM_get_clock();
#endif /* TERATERM_H_ */
