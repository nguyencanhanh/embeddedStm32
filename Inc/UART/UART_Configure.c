/*
 * UART_Configure.c
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#include "UART_Configure.h"
#include "stm32f1xx.h"

void UART_Configure(void){
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	GPIOA->CRH &= 0xFFFFFF0F;
	GPIOA->CRH |= (11 << 4);  //TX PA9
	GPIOA->CRH &= 0xFFFFF0FF;
	GPIOA->CRH |= (1 << 10); //RX PA10
	GPIOA->CRL &= 0xFFFF0FFF;
	GPIOA->CRL |= (2 << 12);
	/* UART configure */
	USART1->BRR |= (39 << 4) | (1 << 0);
	USART1->CR1 |= (1 << 2) | (1 << 3) | (1 << 5) ;
//	NVIC_EnableIRQ(USART1_IRQn);
//	NVIC_SetPriority(USART1_IRQn, 1);
	USART1->CR1 |= (1 << 13);
}
void UART_SendData(char* str){
	while (*str){
		while (!(USART1->SR & (1 << 7)));
		USART1->DR = *str;
		str++;
	}
	while (!(USART1->SR & (1 << 6)));
}
