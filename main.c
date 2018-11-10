#include "I2C.h"
#include "MK64F12.h"
#include "RTC.h"


int main(void) {

	I2C_init(I2C_0, 21000000, 9600);
	RTC_init();

    while(1) {

    }
    return 0 ;
}
