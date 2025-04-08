#include "hal_i2c.h"
#include <avr/io.h>
#include <util/delay.h>

static uint8_t HAL_I2C_Start(uint8_t address) {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));

    TWDR = address;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));

    return (TWSR & 0xF8) == 0x18;  // SLA+W ACK
}

static void HAL_I2C_Stop(void) {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

static uint8_t HAL_I2C_Write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    return (TWSR & 0xF8) == 0x28;  // DATA ACK
}

static uint8_t HAL_I2C_ReadAck(void) {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

static uint8_t HAL_I2C_ReadNack(void) {
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    return TWDR;
}

void HAL_I2C_Init(bool scan_enable) {
    //Prescaler = 1
    CLEAR_BIT(TWSR, TWPS1);
    CLEAR_BIT(TWSR, TWPS0);
    WRITE_REG(TWBR, 72);        //freq = F_CPU / (16 + 2 * TWBR * Prescaler) = 100k            
    SET_BIT(TWCR, TWEN);        // TWI Enable       
    
    if (scan_enable)
        for (uint8_t addr = 0; addr < 127; addr++) {
            if (HAL_I2C_Start(addr << 1)) {
                HAL_I2C_ScanHandler(addr);
                HAL_I2C_Stop();
            }
            _delay_ms(10);
        }
}

void HAL_I2C_WriteReg(uint8_t addr, uint8_t reg, uint8_t data){
    HAL_I2C_Start(addr << 1);
    HAL_I2C_Write(reg);
    HAL_I2C_Write(data);
    HAL_I2C_Stop();
}

uint8_t HAL_I2C_ReadReg(uint8_t addr, uint8_t reg) {
    uint8_t data;
    HAL_I2C_Start(addr << 1);
    HAL_I2C_Write(reg);
    HAL_I2C_Start((addr << 1) | 0x01);
    data = HAL_I2C_ReadNack();
    HAL_I2C_Stop();
    return data;
}

__attribute__((weak)) void HAL_I2C_ScanHandler(uint8_t addr)
{
    
}
