/*
 * GPIO_Configure.c
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */
#include "GPIO_configure.h"

void GPIO_configureRCC(char* GPIOx){
	while(*GPIOx){
		if(*GPIOx == 'C') RCC->APB2ENR |= (1 << 4);
		if(*GPIOx == 'B') RCC->APB2ENR |= (1 << 3);
		if(*GPIOx == 'A') RCC->APB2ENR |= (1 << 2);
		GPIOx++;
	}
}
void GPIO_configure(GPIO_TypeDef*GPIOx, uint8_t* Pin, uint8_t* mode){
	while(*Pin){
		if(*Pin > 7){
			GPIOx->CRH &= ~(15<<(*Pin * 4 - 32));
			GPIOx->CRH |= *mode << (*Pin * 4 - 32);
		}else{
			GPIOx->CRL &= ~(15<<(*Pin * 4));
			GPIOx->CRL |= *mode << (*Pin * 4);
		}
		Pin++;
		mode++;
	}
}
uint8_t ReadPin(GPIO_TypeDef* GPIOx, uint16_t Pin){
	 if ((GPIOx->IDR & (1 << Pin)) != 0){
	    return 1;
	  }
	  else
		return 0;
}

