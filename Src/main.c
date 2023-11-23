#include <stdio.h>
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
Queue *myQueue;

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void task5_handler(void);
void idle_task(void);

void init_task_stack(void(*idleTask)(void));

typedef struct {
    int intValue;
} MyData;

uint8_t count = 1;
MyData receivedData, sent;
uint8_t recive;
int togl;


int main(void)
{
	GPIO_configureRCC("B");
	BeginGPIO((GPIO_TypeDef*)GPIOB, 12, 1, 11, 1);

	createTask(task1_handler, 2);
	createTask(task2_handler, 4);
	createTask(task3_handler, 1);
	createTask(task4_handler, 5);
	createTask(task5_handler, 3);

	rtosInit(idle_task);
	 while (1)
	  {
	  }
}

void idle_task(void){
	while(1);
}

void task1_handler(void){
	while(1){
		togl++;
		task_delay(1000);
		printf("oke");
	}
}

void task2_handler(void){
	myQueue = QueueCreate(5);
	MyData myData;
	myData.intValue = 0;
	while(1){
		if(count % 20 == 10)
			suspenTask(task1_handler);
		if(count % 20 == 0)
			resumeTask(task1_handler);
		count++;
		myData.intValue+=2;
		sent = myData;
		QueueSend(myQueue, &count, sizeof(uint8_t));
		QueueSend(myQueue, &myData, sizeof(MyData));
		task_delay(1000);
	}
}

void task3_handler(void){
	while(1){
		printf("oke");
	}
}

void task4_handler(void){
	while(1){
		GPIOB_ON(11);
		task_delay(1);
		GPIOB_OFF(11);
		task_delay(10000);
		printf("oke");
	}
}

void task5_handler(void){
	while(1){
		QueueReceive(myQueue, &recive);
		QueueReceive(myQueue, &receivedData);
	}
}


