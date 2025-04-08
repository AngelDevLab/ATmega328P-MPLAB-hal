#include "hal_spi.h"
#include <avr/io.h>

void HAL_SPI_Init(void)
{
    SET_BIT(DDRB, DDB3); //MOSI (PB3) output
    SET_BIT(DDRB, DDB5); //SCK (PB5) output
    CS_INIT();
    CS_HIGH();
    
    CLEAR_BIT(DDRB, DDB4); //MISO (PB4) input
    SET_BIT(PORTB, PB4); //pull-up
    
#if SPI_DOUBLE_SPEED
    SET_BIT(SPSR, SPI2X);
#else
    CLEAR_BIT(SPSR, SPI2X);
#endif
    
#if SPI_CLOCK_SETTING == SPI_CLOCK_DIV4
    CLEAR_BIT(SPCR, SPR1);
    CLEAR_BIT(SPCR, SPR0);
#elif SPI_CLOCK_SETTING == SPI_CLOCK_DIV16
    CLEAR_BIT(SPCR, SPR1);
    SET_BIT(SPCR, SPR0);
#elif SPI_CLOCK_SETTING == SPI_CLOCK_DIV64
    SET_BIT(SPCR, SPR1);
    CLEAR_BIT(SPCR, SPR0);
#elif SPI_CLOCK_SETTING == SPI_CLOCK_DIV128
    SET_BIT(SPCR, SPR1);
    SET_BIT(SPCR, SPR0);
#endif
    
    SET_BIT(SPCR, MSTR); //MSTR = 1,SPI Master
    SET_BIT(SPCR, SPE); //SPI Enable
}

static uint8_t HAL_SPI_Transfer(uint8_t data)
{
    WRITE_REG(SPDR, data);
    while (!READ_BIT(SPSR, SPIF));
    return READ_REG(SPDR);
}

void HAL_SPI_Write(uint8_t data)
{
    CS_LOW();
    HAL_SPI_Transfer(data);
    CS_HIGH();
}

void HAL_SPI_Transmit(uint8_t *buffer, uint16_t len)
{
    CS_LOW();
    while (len--) {
        HAL_SPI_Transfer(*buffer++);
    }
    CS_HIGH();
}

uint8_t HAL_SPI_Read(void)
{
    return HAL_SPI_Transfer(0xFF);
}
