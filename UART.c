/*
 * UART.c
 *
 *  Created on: Oct 22, 2018
 *      Author: Andrea Perez ie698276@iteso.mx
 */
#include <UART.h>
#include "NVIC.h"
#include "MK64F12.h"

UART_MailBoxType UART0_MailBox = {0};
uint16_t baudRate;
uint8_t temp;

void UART_init(UART_ChannelType uartChannel, uint32 system_clock, UART_BaudRateType baud_rate){
	baudRate = (system_clock)/(baud_rate * MULT);
	temp = (system_clock/(baud_rate * MULT) - baudRate)*MULT_2;
	switch(uartChannel){
		case UART_0:{
			SIM->SCGC4 = SIM_SCGC4_UART0_MASK;
			UART0->C2 &= ~(UART_C2_RE_MASK);
			UART0->C2 &= ~(UART_C2_TE_MASK);
			UART0->C1 = 0;
			UART0->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART0->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART0->C4 = temp & UART_C4_BRFA_MASK;
			UART0->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_1:{
			SIM->SCGC4 = SIM_SCGC4_UART1_MASK;
			UART1->C2 &= ~(UART_C2_RE_MASK);
			UART1->C2 &= ~(UART_C2_TE_MASK);
			UART1->C1 = 0;
			UART1->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART1->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART1->C4 = temp & UART_C4_BRFA_MASK;
			UART1->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_2:{
			SIM->SCGC4 = SIM_SCGC4_UART2_MASK;
			UART2->C2 &= ~(UART_C2_RE_MASK);
			UART2->C2 &= ~(UART_C2_TE_MASK);
			UART2->C1 = 0;
			UART2->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART2->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART2->C4 = temp & UART_C4_BRFA_MASK;
			UART2->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_3:{
			SIM->SCGC4 = SIM_SCGC4_UART3_MASK;
			UART3->C2 &= ~(UART_C2_RE_MASK);
			UART3->C2 &= ~(UART_C2_TE_MASK);
			UART3->C1 = 0;
			UART3->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART3->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART3->C4 = temp & UART_C4_BRFA_MASK;
			UART3->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_4:{
			SIM->SCGC1 = SIM_SCGC1_UART4_MASK;
			UART4->C2 &= ~(UART_C2_RE_MASK);
			UART4->C2 &= ~(UART_C2_TE_MASK);
			UART4->C1 = 0;
			UART4->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART4->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART4->C4 = temp & UART_C4_BRFA_MASK;
			UART4->C2 = UART_C2_RE_MASK |UART_C2_TE_MASK;
			break;
		}
		case UART_5:{
			SIM->SCGC1 = SIM_SCGC1_UART4_MASK;
			UART5->C2 &= ~(UART_C2_RE_MASK);
			UART5->C2 &= ~(UART_C2_TE_MASK);
			UART5->C1 = 0;
			UART5->BDH = (baudRate & UART_BDH_SBR_MASK)>> SHIFT;
			UART5->BDL = (baudRate & UART_BDL_SBR_MASK);
			UART5->C4 = temp & UART_C4_BRFA_MASK;
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

void UART_putChar (UART_ChannelType uartChannel, uint8 character)
{
	switch(uartChannel){
	case UART_0:{
		UART0->S1;
		while(!(UART0->S1 & UART_S1_TC_MASK));
		UART0->D = character;
		break;
	}
	case UART_1:{
		UART1->S1;
		while(!(UART1->S1 & UART_S1_TC_MASK));
		UART1->D = character;
		break;
	}
	case UART_2:{
		UART2->S1;
		while(!(UART2->S1 & UART_S1_TC_MASK));
		UART2->D = character;
		break;
	}
	case UART_3:{
		UART3->S1;
		while(!(UART3->S1 & UART_S1_TC_MASK));
		UART3->D = character;
		break;
	}
	case UART_4:{
		UART4->S1;
		while(!(UART4->S1 & UART_S1_TC_MASK));
		UART4->D = character;
		break;
	}
	case UART_5:
		UART5->S1;
		while(!(UART5->S1 & UART_S1_TC_MASK));
		UART5->D = character;
		break;
	}
}


void UART_putString(UART_ChannelType uartChannel, sint8* string){
	switch(uartChannel){
		case UART_0:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
		case UART_1:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
		case UART_2:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
		case UART_3:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
		case UART_4:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
		case UART_5:{
			if(*string)
				UART_putChar(uartChannel, *string++);
			break;
		}
	}
}

void UART0_RX_TX_IRQHandler(void){
	while(!(UART0->S1 & UART_S1_RDRF_MASK)){
		UART0_MailBox.flag = TRUE;
		UART0_MailBox.mailBox = UART0->D;
	}
}


