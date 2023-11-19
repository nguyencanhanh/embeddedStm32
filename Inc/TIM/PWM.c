/*
 * PWM.c
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */
#include "PWM.h"

void TIMx_PWM_Init(TIM_TypeDef* TIMx, uint8_t chanel, uint16_t psc, uint16_t arr){
	if(TIMx == TIM1){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	}else{
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	}
	TIMx->PSC = psc;
	TIMx->ARR = arr;
	TIMx->CCER |= (1 << (chanel*4 - 4));
	if (chanel > 2){
		TIMx->CCMR2 |= (6 << (8 * chanel - 20));
	}else{
		TIMx->CCMR1 |= (6 << (8 * chanel - 4));
	}
	TIMx->CR1 |= (1 << 0);
	while (!(TIMx->SR & TIM_SR_UIF));
}
void TIMx_PWM_setDuty(TIM_TypeDef* TIMx, uint8_t chanel, uint16_t duty){
	if (chanel == 1){
		TIMx->CCR1 = duty;
	}else if (chanel == 2)
		TIMx->CCR2 = duty;
	else if (chanel == 3)
		TIMx->CCR3 = duty;
	else {
		TIMx->CCR4 = duty;
	}
}
