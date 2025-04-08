#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_

#include "hal_config.h"
#include <avr/io.h>

#define CS_INIT()           SET_BIT(DDRB, DDB2)
#define CS_HIGH()           SET_BIT(PORTB, PB2)
#define CS_LOW()            CLEAR_BIT(PORTB, PB2)

#define SPI_CLOCK_DIV4      0
#define SPI_CLOCK_DIV16     1
#define SPI_CLOCK_DIV64     2
#define SPI_CLOCK_DIV128    3

#define SPI_DOUBLE_SPEED    1 //0=Not double speed, 1=Double speed
#define SPI_CLOCK_SETTING   SPI_CLOCK_DIV4

void HAL_SPI_Init(void);
void HAL_SPI_Write(uint8_t data);
void HAL_SPI_Transmit(uint8_t *buffer, uint16_t len);
uint8_t HAL_SPI_Read(void);

#endif /*_HAL_SPI_H_*/
