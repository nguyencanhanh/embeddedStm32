/*
 * UART_Configure.h
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#ifndef UART_UART_CONFIGURE_H_
#define UART_UART_CONFIGURE_H_

#include "stdint.h"

#define MAX_BUFFER_SIZE 255

void UART_Configure(void);
void UART_SendData(char* str);
void UART_ReciveData(uint8_t *buffer, int length);

#endif /* UART_UART_CONFIGURE_H_ */
