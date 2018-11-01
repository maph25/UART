/*
 * UART.c
 *
 *  Created on: Oct 22, 2018
 *      Author: Andy
 */
#include "UART.h"
#include "NVIC.h"
#include "MK64F12.h"

UART_MailBoxType UART0_MailBox = {0};

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
		SIM->SCGC4 = SIM_SCGC4_UART0_MASK;
		UART0->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
		UART0->BDH = 0;
		UART0->BDL = 0x0B;
		UART0->C4 = UART_C4_BRFA(baudRate);
		UART0->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
}
void UART0_interruptEnable(UART_ChannelType uartChannel){
	UART0->C2 = UART_C2_RIE_MASK;
	NVIC_EnableIRQ(UART0_RX_TX_IRQn);
}

void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	if(UART0->S1 & ~(UART_S1_TDRE_MASK))
	UART0->D = character;
}

void UART_putString(UART_ChannelType uartChannel, sint8* string){
	if(*string)
		UART_putChar(uartChannel, *string++);
}

void UART0_RX_TX_IRQHandler(void){
	if(UART0->S1 & ~(UART_S1_RDRF_MASK)) {
		UART0_MailBox.flag = TRUE;
		UART0_MailBox.mailBox = UART0->D;
	}
}


