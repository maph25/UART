/*
 * I2C.c
 *
 *  Created on: Nov 5, 2018
 *      Author: Andy
 */

#include "GPIO.h"
#include "Bits.h"
#include "Delay.h"
#include "I2C.h"

#define MULTIPLIER (4u)
uint32_t SCL;
gpio_pin_control_register_t ctrlReg = GPIO_MUX2;

void I2C_init(i2c_channel_t channel, uint32_t system_clock, uint16_t baud_rate){
	GPIO_clock_gating (GPIO_B);
	GPIO_pin_control_register(GPIO_B, BIT2, &ctrlReg);/*SCL*/
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, BIT2);
	GPIO_pin_control_register(GPIO_B, BIT3, &ctrlReg);/*SDA*/
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, BIT2);
	SCL = (system_clock)/(baud_rate * MULTIPLIER);

		switch (channel){
		case I2C_0:{
			SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
			I2C0->F = I2C_F_ICR(SCL);
			I2C0->F = I2C_F_MULT(2);
			I2C0->C1 |= I2C_C1_IICEN_MASK;
			break;
		}
		case I2C_1:
			SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
			I2C1->F = I2C_F_ICR(SCL);
			I2C1->F = I2C_F_MULT(2);
			I2C1->C1 |= I2C_C1_IICEN_MASK;
			break;
		case I2C_2:
			SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK;
			I2C2->F = I2C_F_ICR(SCL);
			I2C2->F = I2C_F_MULT(2);
			I2C2->C1 |= I2C_C1_IICEN_MASK;
			break;
	}/*switch*/
}

uint8_t I2C_busy(){
	uint8 busy = FALSE;
	if((I2C0->S & I2C_S_BUSY_MASK) == FALSE){

	}
	else{
		busy = TRUE;
	}
	return busy;
}

void I2C_mst_or_slv_mode(uint8_t mst_or_slv){
	if(mst_or_slv == I2C_SLV_MODE) {
		I2C0->C1 &= ~(I2C_C1_MST_MASK);
	}
	else if(mst_or_slv == I2C_MST_MODE){
		I2C0->C1 |= (I2C_C1_MST_MASK);
	}
}

void I2C_tx_rx_mode(uint8_t tx_or_rx){
	if(I2C_RX_MODE == tx_or_rx){
		I2C0->C1 &= ~(I2C_C1_TX_MASK);
	}
	else if(I2C_TX_MODE == tx_or_rx){
		I2C0->C1 |= I2C_C1_TX_MASK;
	}

}

void I2C_nack(void){
	I2C0->C1 |= I2C_C1_TXAK_MASK;
}

void I2C_repeted_start(void){
	I2C0->C1 |= I2C_C1_RSTA_MASK;
	delay(5000);
}

void I2C_write_byte(uint8_t data){
	delay(5000);
	I2C0->D = data;
}

uint8_t  I2C_read_byte(void){
	uint8 reading = I2C0->D;
	return  reading;
}

void I2C_wait(void){
	while(!(I2C0->S & I2C_S_TCF_MASK));
		I2C0->S |= I2C_S_IICIF_MASK;
}

uint8_t I2C_get_ack(void){
    delay(5000);

	while(I2C0->S & I2C_S_RXAK_MASK ){
    	return TRUE;
	}
	return FALSE;
}

void I2C_start(void){
	I2C_mst_or_slv_mode(I2C_MST_MODE);
	I2C_tx_rx_mode(I2C_TX_MODE);
}

void I2C_stop(void){
	I2C_mst_or_slv_mode(I2C_SLV_MODE);
	I2C_tx_rx_mode(I2C_RX_MODE);
	delay(5000);
}
