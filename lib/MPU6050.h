#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "atmega328p_hal.h"

#define MPU6050_RAW_TEMP_TO_C(raw)      ((raw) / 340.0 + 36.53)

#define MPU6050_ADDR                    0x68

#define MPU6050_REG_PWR_MGMT            0x6B
#define MPU6050_REG_ACCEL_X             0x3B
#define MPU6050_REG_ACCEL_Y             0x3D
#define MPU6050_REG_ACCEL_Z             0x3F
#define MPU6050_REG_TEMP                0x41
#define MPU6050_REG_GYRO_X              0x43
#define MPU6050_REG_GYRO_Y              0x45
#define MPU6050_REG_GYRO_Z              0x47

typedef enum {
    MPU6050_ACCEL_X,
    MPU6050_ACCEL_Y,
    MPU6050_ACCEL_Z, 
    MPU6050_GYRO_X,   
    MPU6050_GYRO_Y,   
    MPU6050_GYRO_Z,   
    MPU6050_TEMP,       
    MPU6050_DATA_SIZE,        
}MPU6050_Data;

void MPU6050_Init(uint32_t (*timeMsTickHandler)());
void MPU6050_Process(void);
void MPU6050_SetUpdateInterval(uint32_t data);
__attribute__((weak)) void MPU6050_DataCallback(int16_t *data);

#endif /* _MPU6050_H_ */
