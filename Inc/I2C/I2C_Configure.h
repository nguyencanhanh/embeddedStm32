#ifndef INC_I2C_I2C_CONFIGURE_H_
#define INC_I2C_I2C_CONFIGURE_H_

#define COMMAND  0
#define DATA     1

#include "stm32f1xx.h"

void I2C_GPIO_Config(void);
void I2C1_Configure();
void I2C_WriteData(I2C_TypeDef *i2c, uint8_t slaveAddress, uint8_t *data, uint16_t dataSize);

#endif /* INC_I2C_I2C_CONFIGURE_H_ */
