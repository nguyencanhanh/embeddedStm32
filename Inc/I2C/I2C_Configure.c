#include"I2C_Configure.h"
#include "stm32f1xx.h"
void I2C_GPIO_Config(void) {
    // Bật clock cho GPIOB
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    GPIOB->CRL |= 0xFF000000;
}
void I2C1_Configure(void){
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
		I2C1->CR1 |= I2C_CR1_SWRST;
		I2C1->CR1 &= ~I2C_CR1_SWRST;
	    I2C1->OAR1 |=(1<<14);
	    I2C1->CR2 |= 36; // Đặt tần số là 36 MHz
	    I2C1->CCR = 180; // Cài đặt CCR cho tốc độ 100kHz
	    I2C1->TRISE = 37; // Cài đặt TRISE cho tốc độ 100kHz
	    I2C1->CR1 |= I2C_CR1_PE; // Bật I2C
}
void I2C_WriteData(I2C_TypeDef *i2c, uint8_t slaveAddress, uint8_t *data, uint16_t dataSize) {
    while (i2c->SR2 & I2C_SR2_BUSY);
    // Bắt đầu quá trình truyền
    i2c->CR1 |= I2C_CR1_START;
    // Chờ cho tới khi quá trình truyền bắt đầu
    while (!(i2c->SR1 & I2C_SR1_SB));
    // Gửi địa chỉ slave và chế độ ghi
    i2c->DR = (slaveAddress << 1) & 0xFE;
    while (!(i2c->SR1 & (1<<1)));
    volatile uint32_t temp = i2c->SR1;
    temp = i2c->SR2;
    (void)temp;
    // Gửi dữ liệu
    for (uint16_t i = 0; i < dataSize; ++i) {
    	i2c->DR = data[i];
        while (!(i2c->SR1 & I2C_SR1_TXE));
    }
    // Chờ cho tới khi byte transfer hoàn thành (BTF)
    while (!(i2c->SR1 & I2C_SR1_BTF));
    // Kết thúc truyền
    i2c->CR1 |= I2C_CR1_STOP;
}





