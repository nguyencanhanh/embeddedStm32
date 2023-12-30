/*
 * STM32F103.c
 *
 *  Created on: Jun 4, 2023
 *      Author: nguye
 */
#include "stm32f103.h"
#include <stm32f1xx.h>

void SystemInitAnh(void){
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	AFIO->MAPR |= AFIO_MAPR_SWJ_CFG;
}
void RCC_Configure(){
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1;
	while (!(FLASH->ACR & FLASH_ACR_PRFTBS));

	RCC->CFGR |= RCC_CFGR_PLLSRC;
	RCC->CFGR |= (7 << 18); // nhân RCC với 9
	RCC->CFGR |= (4 << 8); // chia để bus APB1 max 36
	RCC->CFGR |= (3 << 14); // chia ADC cho 6 = 9M
	RCC->CR |= RCC_CR_PLLON;

	while (!(RCC->CR & RCC_CR_PLLRDY));
	RCC->CFGR |= (2 << 0);
	while (!(RCC->CFGR & (2 << 2)));
}
