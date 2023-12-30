#include <stdio.h>
#include <stdint.h>
#include "stm32f103.h"
#include "GPIO_Configure.h"
#include "TIM_Configure.h"
#include "UART_Configure.h"

uint32_t half_steps[] = {8 << 12, 12 << 12, 4 << 12, 6 << 12, 2 << 12, 3 << 12, 1 << 12, 9 << 12};
uint32_t half_steps1[] = {8 << 8, 12 << 8, 4 << 8, 6 << 8, 2 << 8, 3 << 8, 1 << 8, 9 << 8};
int i = 0, y = 0, count = 0;
char rxBuffer[18];

volatile uint8_t rxIndex = 0;
volatile uint8_t rxComplete = 0;

uint16_t oke;

int main(void)
{
	SystemInitAnh();
	RCC_Configure();
	GPIO_configureRCC("AB");
	TIM2_Configure(71, 0xFFFF);
	UART_Configure();

	BeginGPIO((GPIO_TypeDef*)GPIOB, 12, 1, 13, 1, 14, 1, 15, 1);
	BeginGPIO((GPIO_TypeDef*)GPIOB, 8, 1, 9, 1, 10, 1, 11, 1);
	int lastI = i, lastY = y;
	UART_SendData("o");
	while(1){
		if(rxComplete) {
			int num1, num2, num3, num4, num5, k1 = 0, k2 = 0;
			sscanf(rxBuffer, "%d %d %d %d %d", &num1, &num2, &num3, &num4, &num5);
			if(num1 == 0 && num4 == 0){
				delay_ms2(100);
			}
			JUM:
			if(num1 > 0){
				GPIOB->ODR = half_steps[i] | half_steps1[lastY];
				lastI = i;
				i = (i+num2)%8;
				k1++;
			}
			if(num3 > 0){
				GPIOB->ODR = half_steps1[y] | half_steps[lastI];
				lastY = y;
				y = (y+num4)%8;
				k2++;
			}
			if (i<0)  i = 7;
			if (y<0)  y = 7;
			if((num1 < 1) && (num3 < 1)){
				rxComplete = 0;
				UART_SendData("o");
			}else {
				if(k1 % 40 ==39) num1--;
				if(k2 % 40 ==39)  num3--;
				delay_us2(1500);
				goto JUM;
			}
		 }
	}
}



void USART1_IRQHandler() {
    if (USART1->SR & USART_SR_RXNE) {
        char receivedChar = USART1->DR;
        if (receivedChar == 'x') {
        	rxBuffer[rxIndex] = '\0';
        	rxIndex = 0;
            rxComplete = 1;
            count++;
        }
        else {
            rxBuffer[rxIndex++] = receivedChar;
        }
    }
}


