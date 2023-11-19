#ifndef DMA_DMA_CONFIGURE_H_
#define DMA_DMA_CONFIGURE_H_

#include "stdint.h"

void DMA_ConfigureADC(uint32_t *buffer, uint8_t numberOfChannels);
void DMA_ConfigureUART(void);
void sendUART1DMA(uint8_t *data);

#endif /* DMA_DMA_CONFIGURE_H_ */
