#include "atmega328p_hal.h"
#include <avr/interrupt.h>
#include "app.h"

void HAL_I2C_ScanHandler(uint8_t addr)
{
    printf(">> I2C addr : 0x%x\r\n", addr);
}

int main(void) {
    
    HAL_TIMER_Init();
    HAL_UART_Init();
    HAL_I2C_Init(false);
    HAL_SPI_Init();
    app_init();
    sei();

    while (1) {
        HAL_UART_Process();
        app_process();
    }
}
