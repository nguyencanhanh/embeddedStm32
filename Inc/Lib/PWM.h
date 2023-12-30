/*
 * PWM.h
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#ifndef TIM_PWM_H_
#define TIM_PWM_H_

#include <stm32f1xx.h>

void TIMx_PWM_Init(TIM_TypeDef* TIMx, uint8_t chanel, uint16_t psc, uint16_t arr);
void TIMx_PWM_setDuty(TIM_TypeDef* TIMx, uint8_t chanel, uint16_t duty);

#endif /* TIM_PWM_H_ */
