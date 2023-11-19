/*
 * GPIO_Configure.h
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#ifndef GPIO_GPIO_CONFIGURE_H_
#define GPIO_GPIO_CONFIGURE_H_

#include "stm32f1xx.h"

void GPIO_configureRCC(char* GPIOx);
void GPIO_configure(GPIO_TypeDef* GPIOx, uint8_t* Pin, uint8_t* mode);
uint8_t ReadPin(GPIO_TypeDef* GPIOx, uint16_t Pin);

#endif /* GPIO_GPIO_CONFIGURE_H_ */
