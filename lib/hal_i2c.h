#ifndef _HAL_I2C_H_
#define _HAL_I2C_H_

#include "hal_config.h"

void HAL_I2C_Init(bool scan_enable);
void HAL_I2C_WriteReg(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t HAL_I2C_ReadReg(uint8_t addr, uint8_t reg);

__attribute__((weak)) void HAL_I2C_ScanHandler(uint8_t addr);

#endif /*_HAL_I2C_H_*/