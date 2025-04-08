#ifndef _APP_H_
#define _APP_H_

#include "atmega328p_hal.h"
#include <avr/pgmspace.h>

void app_update_mpu6050_data(int16_t *data);

void app_init(void);
void app_process(void);

#endif /*_APP_H_*/
