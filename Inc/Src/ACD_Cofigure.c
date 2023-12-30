/*
 * ACD_Cofigure.c
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */
#include "ADC_Configure.h"
#include "stm32f1xx.h"

void ADC1_Configure(uint8_t* chanel, uint8_t cycle, uint8_t lenght){
	uint8_t count = 0;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->SQR1 |= ((lenght-1) << 20);
	for(int i = 0; i < lenght; i++){
		ADC1->SQR3 |= (chanel[i] << count);
		ADC1->SMPR2 |= (cycle << (chanel[i]*3));
		count+=5;
	}
	ADC1->CR2 |= (1 << 2);
	while((ADC1->CR2 & (1 << 2)) != 0);
	ADC1->CR2 |= (1 << 0);
	ADC1->CR2 |= (1 << 22);
}
void Read_ADC1 (uint16_t* adc_value, uint8_t lenght){
	for(int i = 0; i < lenght; i++){
		while (!(ADC1->SR & ADC_SR_EOC));
		adc_value[i] = ADC1->DR;
	}
}
