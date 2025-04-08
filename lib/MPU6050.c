#include "MPU6050.h"

uint32_t (*time_ms_tick_get)();
static uint32_t update_interval_ms = 10;
static uint32_t last_tick = 0;
static int16_t data_buf[MPU6050_DATA_SIZE];

static int16_t MPU6050_ReadWord(uint8_t reg_high) {
    uint8_t high = HAL_I2C_ReadReg(MPU6050_ADDR, reg_high);
    uint8_t low  = HAL_I2C_ReadReg(MPU6050_ADDR, reg_high + 1);
    return (int16_t)((high << 8) | low);
}

void MPU6050_Init(uint32_t (*timeMsTickHandler)()) {
    time_ms_tick_get = timeMsTickHandler;
    HAL_I2C_WriteReg(MPU6050_ADDR, MPU6050_REG_PWR_MGMT, 0x00);
}

void MPU6050_Process(void)
{
    if ((time_ms_tick_get() - last_tick) >= update_interval_ms) {
        last_tick = time_ms_tick_get();

        data_buf[MPU6050_ACCEL_X] = MPU6050_ReadWord(MPU6050_REG_ACCEL_X);
        data_buf[MPU6050_ACCEL_Y] = MPU6050_ReadWord(MPU6050_REG_ACCEL_Y);
        data_buf[MPU6050_ACCEL_Z] = MPU6050_ReadWord(MPU6050_REG_ACCEL_Z);
        data_buf[MPU6050_GYRO_X]  = MPU6050_ReadWord(MPU6050_REG_GYRO_X);
        data_buf[MPU6050_GYRO_Y]  = MPU6050_ReadWord(MPU6050_REG_GYRO_Y);
        data_buf[MPU6050_GYRO_Z]  = MPU6050_ReadWord(MPU6050_REG_GYRO_Z);
        data_buf[MPU6050_TEMP]    = MPU6050_ReadWord(MPU6050_REG_TEMP);

        MPU6050_DataCallback(data_buf);
    }
}

void MPU6050_SetUpdateInterval(uint32_t data)
{
    update_interval_ms = data;
}

__attribute__((weak)) void MPU6050_DataCallback(int16_t *data)
{
    
}
