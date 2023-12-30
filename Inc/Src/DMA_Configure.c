#include <DMA_Configure.h>
#include "stm32f1xx.h"

void DMA_ConfigureADC(uint32_t *buffer, uint8_t numberOfChannels) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
    DMA1_Channel1->CMAR = (uint32_t)(buffer);
    DMA1_Channel1->CNDTR = numberOfChannels;
    DMA1_Channel1->CCR |= DMA_CCR_PSIZE_0 | DMA_CCR_MSIZE_0 | DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_EN;
    ADC1->CR2 |= ADC_CR2_DMA;
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}
void DMA_ReciveUART(uint32_t* dma_rx_buffer, uint8_t  DMA_BUFFER_SIZE){
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel5->CCR = 0;
	DMA1_Channel5->CCR = DMA_CCR_MINC | DMA_CCR_TCIE;
	DMA1_Channel5->CPAR = (uint32_t) &USART1->DR;
	DMA1_Channel5->CMAR = (uint32_t) dma_rx_buffer;
	DMA1_Channel5->CNDTR = DMA_BUFFER_SIZE;

	DMA1_Channel5->CCR |= DMA_CCR_EN;
}
void sendUART1DMA(uint8_t *data) {
	DMA1_Channel4->CMAR = (uint32_t)data;
	DMA1_Channel5->CNDTR = sizeof(data);
    DMA1_Channel4->CCR |= DMA_CCR_EN;
    while (!(DMA1->ISR & DMA_ISR_TCIF4));
}

