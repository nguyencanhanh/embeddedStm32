#include <stdint.h>
#include "stm32f103.h"
#include "GPIO_Configure.h"
#include "TIM_Configure.h"
#include "UART_Configure.h"
#include "DMA_Configure.h"
#include "ADC_Configure.h"
#include "I2C_Configure.h"
#include "LiquidCrystal_I2C.h"
#include "rtos.h"

int __io_putchar(int ch) {
    UART_SendData((char*)&ch);
    return ch;
}

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void idleTask(void);


uint8_t GPIOB_Pin[] = {10,11,12};
uint8_t GPIOB_mode[] = {1,1,1};


int main(void)
{
	SystemInitAnh();
	RCC_Configure();

	createTask(task1_handler);
	createTask(task2_handler);
	createTask(task3_handler);
	createTask(task4_handler);

	GPIO_configureRCC("B");
	GPIO_configure((GPIO_TypeDef*)GPIOB, (uint8_t*)GPIOB_Pin ,(uint8_t*)GPIOB_mode);

	RTOS_INIT(idleTask);

	while (1){
	}
}

void idleTask(void){
	while(1);
}

void task1_handler(void){
	while(1){
		printf("oke");
	}
}
void task2_handler(void){
	while(1){
		GPIOB_TOGGLE(10);
		task_delay(4000);
		printf("oke");
	}
}
void task3_handler(void){
	while(1){
		GPIOB_OFF(11);
		task_delay(4000);
		GPIOB_ON(11);
		task_delay(10);
		printf("oke");
	}
}
void task4_handler(void){
	while(1){
		GPIOB_TOGGLE(12);
		task_delay(500);
		printf("oke");
	}
}
