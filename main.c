#include "atmega328p_hal.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "decoder.h"
#include "MPU6050.h"
#include "ILI9341.h"
#include "app.h"
#include "app_button.h"

void app_button_event_handler(hal_button_num_t num, app_button_event_t event, uint32_t time_ms)
{
    printf(">> button even(%d) [%d], %ld\r\n", num, event, time_ms);
}

void decoder_callback(const char* cmd, const char* arg1, const char* arg2)
{
    if (strcmp(cmd, "@UART") == 0) {
        printf("@UART,ok\r\n");
    }
}

void HAL_UART_CommandHandler(const char* cmd)
{
    decoder_input(cmd);
}

void HAL_I2C_ScanHandler(uint8_t addr)
{
    printf(">> I2C addr : 0x%x\r\n", addr);
}

void MPU6050_DataCallback(int16_t *data)
{
    app_update_mpu6050_data(data);
}

int main(void) {
    
    HAL_TIMER_Init();
    HAL_UART_Init();
    HAL_I2C_Init(false);
    HAL_SPI_Init();
    
    MPU6050_Init(&HAL_GetTick);
    app_button_init(&HAL_GetTick);
    
    HAL_SPI_Init();
    ILI9341_Init();
    ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
    ILI9341_FillScreen(WHITE);
    
    app_init();
    
    sei();

    while (1) {
        HAL_UART_Process();
        MPU6050_Process();
        app_button_process();
        
        app_process();
    }
}
