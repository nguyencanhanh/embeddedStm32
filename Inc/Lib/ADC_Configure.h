/*
 * ADC_Configure.h
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#ifndef ADC_ADC_CONFIGURE_H_
#define ADC_ADC_CONFIGURE_H_

#include "stdint.h"

void ADC1_Configure(uint8_t* chanel, uint8_t cycle, uint8_t lenght);
void Read_ADC1 (uint16_t* adc_value, uint8_t lenght);

#endif /* ADC_ADC_CONFIGURE_H_ */
