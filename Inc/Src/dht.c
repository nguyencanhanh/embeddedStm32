//#include "dht.h"
//#include "rtos.h"
//
//void DHT_Init(DHT* dht, GPIO_TypeDef*GPIOx, uint8_t Pin){
//  if(Pin > 7){
//		GPIOx->CRH &= ~(15<<(Pin * 4 - 32));
//		GPIOx->CRH |= 7 << (Pin * 4 - 32);
//	}else{
//		GPIOx->CRL &= ~(15<<(Pin * 4));
//		GPIOx->CRL |= 7 << (Pin * 4);
//	}
//  dht->pin = Pin;
//
//}
//
//void DHT22_Start(DHT* dht){
//	GPIOB->BSRR |= (1 << (dht->pin + 16));
//#ifdef RTOS_RTOS_H_
//	task_delay(20);
//#elif DHT_TIM1
//	delay_ms1(20);
//#else
//	delay_ms2(20);
//#endif
//	GPIOB->BSRR |= (1 << dht->pin);
//#ifdef DHT_TIM1
//	TIM1->CNT = 0;
//	while(TIM1->CNT < 55){
//		if(!(GPIOB->IDR & (1<<dht->pin)))
//			break;
//	}
//#else
//	TIM2->CNT = 0;
//	while(TIM2->CNT < 55){
//		if(!(GPIOB->IDR & (1<<dht->pin)))
//			break;
//	}
//#endif
//}
//
//uint8_t DHT22_checkResponse(DHT* dht){
//	uint8_t res = 0;
//#ifdef DHT_TIM1
//	TIM1->CNT = 0;
//	while(TIM1->CNT < 90){
//		if((GPIOB->IDR & (1<<dht->pin)) && (TIM1->CNT > 70)){
//			res++;
//			break;
//		}
//	}
//
//	TIM1->CNT = 0;
//	while(TIM1->CNT <95){
//		if(!(GPIOB->IDR & (1<<dht->pin)) && (TIM1->CNT > 70)){
//			res++;
//			break;
//		}
//	}
//#else
//	TIM2->CNT = 0;
//	while(TIM2->CNT < 90){
//		if((GPIOB->IDR & (1<<dht->pin)) && (TIM2->CNT > 70)){
//			res++;
//			break;
//		}
//	}
//
//	TIM2->CNT = 0;
//	while(TIM2->CNT <95){
//		if(!(GPIOB->IDR & (1 << dht->pin)) && (TIM2->CNT > 70)){
//			res++;
//			break;
//		}
//	}
//#endif
//	return res;
//}
//
//void DHT22_readData(DHT* dht){
//	uint8_t data[5];
//	DHT22_Start(dht);
//#ifdef RTOS_RTOS_H_
//	DISABLE_IRQ();
//#endif
//	uint8_t check = DHT22_checkResponse(dht);
//#ifdef DHT_TIM1
//	if(check == 2){
//		for(int i = 0; i < 4; i++){
//			for(int j = 7; j >= 0; j--){
//				TIM1->CNT = 0;
//		while(TIM1->CNT < 60){
//		  if((GPIOB->IDR & (1<<dht->pin)) && (TIM1->CNT > 40)){
//			break;
//		  }
//		}
//		TIM1->CNT = 0;
//		while(TIM1->CNT < 80){
//		  if(!(GPIOB->IDR & (1<<dht->pin))){
//			break;
//		  }
//		}
//		if(TIM1->CNT > 50){
//		  data[i] |= (1<<j);
//		}
//		else
//		  data[i] &= ~(1<<j);
//			}
//		}
//	}
//#else
//	if(check == 2){
//		for(int i = 0; i < 4; i++){
//			for(int j = 7; j >= 0; j--){
//				TIM2->CNT = 0;
//		while(TIM2->CNT < 60){
//		  if((GPIOB->IDR & (1<<dht->pin)) && (TIM2->CNT > 40)){
//			break;
//		  }
//		}
//		TIM2->CNT = 0;
//		while(TIM2->CNT < 80){
//		  if(!(GPIOB->IDR & (1<<dht->pin))){
//			break;
//		  }
//		}
//		if(TIM2->CNT > 50){
//		  data[i] |= (1<<j);
//		}
//		else
//		  data[i] &= ~(1<<j);
//			}
//		}
//	}
//#endif
//	dht->temperature = ((float)(data[2]&0x7F)*256 + (float)data[3])/10.0;
//	dht->humility = ((float)data[0]*256 + (float)data[1])/10.0;
//#ifdef RTOS_RTOS_H_
//	ENABLE_IRQ();
//#endif
//}
