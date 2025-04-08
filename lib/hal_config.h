#ifndef _HAL_CONFIG_H_
#define _HAL_CONFIG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define FW_VERSION              "V1.0"

#define F_CPU                   16000000UL

#define WRITE_REG(reg, value)   ((reg) = (value))
#define READ_REG(reg)           (reg)
#define SET_BIT(reg, bit)       ((reg) |= (1 << (bit)))
#define CLEAR_BIT(reg, bit)     ((reg) &= ~(1 << (bit)))
#define TOGGLE_BIT(reg, bit)    ((reg) ^= (1 << (bit)))
#define READ_BIT(reg, bit)      (((reg) & (1 << (bit))) != 0)

#endif /*_HAL_CONFIG_H_*/
