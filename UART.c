/*
 * UART.c
 *
 *  Created on: Oct 22, 2018
 *      Author: Andrea Perez ie698276@iteso.mx
 */
#include "UART.h"
#include "NVIC.h"
#include "MK64F12.h"

UART_MailBoxType UART0_MailBox = {0};
uint16_t baudRate;
uint8_t temp;

void UART_init(UART_ChannelType uartChannel, uint32 system_clock, UART_BaudRateType baud_rate){
		baudRate = (system_clock)/(baud_rate*MULT);
		switch(uartChannel){
		case UART_0:{
			SIM->SCGC4 = SIM_SCGC4_UART0_MASK;
			temp = UART0->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART0->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART0->C1 = 0;
			UART0->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART0->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART0->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_1:{
			SIM->SCGC4 = SIM_SCGC4_UART1_MASK;
			temp = UART1->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART1->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART1->C1 = 0;
			UART1->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART1->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART1->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_2:{
			SIM->SCGC4 = SIM_SCGC4_UART2_MASK;
			temp = UART2->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART2->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART2->C1 = 0;
			UART2->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART2->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART2->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_3:{
			SIM->SCGC4 = SIM_SCGC4_UART3_MASK;
			temp = UART3->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART3->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART3->C1 = 0;
			UART3->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART3->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART3->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_4:{
			SIM->SCGC1 = SIM_SCGC1_UART4_MASK;
			temp = UART4->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART4->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART4->C1 = 0;
			UART4->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART4->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART4->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_5:{
			SIM->SCGC1 = SIM_SCGC1_UART4_MASK;
			temp = UART5->BDH & ~(UART_BDH_SBR(UART_BDH_SBR_MASK));
			UART5->C2 = ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
			UART5->C1 = 0;
			UART5->BDH = temp | (((baudRate & UART_BDH_MASK) >> SHIFT));
			UART5->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART5->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
	}

}
void UART_interruptEnable(UART_ChannelType uartChannel){
	switch(uartChannel){
		case UART_0:{
			UART0->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART0_RX_TX_IRQn);
			break;
		}
		case UART_1:{
			UART1->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART1_RX_TX_IRQn);
			break;
		}
		case UART_2:{
			UART2->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART2_RX_TX_IRQn);
			break;
		}
		case UART_3:{
			UART3->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART3_RX_TX_IRQn);
			break;
		}
		case UART_4:{
			UART4->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART4_RX_TX_IRQn);
			break;
		}
		case UART_5:{
			UART5->C2 = UART_C2_RIE_MASK;
			NVIC_EnableIRQ(UART5_RX_TX_IRQn);
			break;
		}
	}
}

void UART_putChar (UART_ChannelType uartChannel, uint8 character){
	switch(uartChannel){
		case UART_0:{
			while(!(UART0->S1) && (UART_S1_TDRE_MASK));
			UART0->D = character;
			break;
		}
		case UART_1:{
			while(!(UART1->S1) && (UART_S1_TDRE_MASK));
			UART1->D = character;
			break;
		}
		case UART_2:{
			while(!(UART2->S1) && (UART_S1_TDRE_MASK));
			UART2->D = character;
			break;
		}
		case UART_3:{
			while(!(UART3->S1) && (UART_S1_TDRE_MASK));
			UART3->D = character;
			break;
		}
		case UART_4:{
			while(!(UART4->S1) &&(UART_S1_TDRE_MASK));
			UART4->D = character;
			break;
		}
		case UART_5:{
			while(!(UART5->S1) && (UART_S1_TDRE_MASK));
			UART5->D = character;
			break;
		}
	}

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


