#ifndef DHT_DHT_H_
#define DHT_DHT_H_

#include "stm32f1xx.h"
#include "TIM_Configure.h"

typedef struct{
	uint8_t pin;
	float temperature;
	float humility;
}DHT;

void DHT_Init(DHT* dht, GPIO_TypeDef*GPIOx, uint8_t Pin);
void DHT22_readData(DHT* dht);

#endif /* DHT_DHT_H_ */
