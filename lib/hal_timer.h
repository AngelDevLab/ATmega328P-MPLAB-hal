#ifndef _HAL_TIMER_H_
#define _HAL_TIMER_H_

#include "hal_config.h"

void HAL_TIMER_Init(void);

uint32_t HAL_GetTick(void);
void HAL_Delay(uint32_t delay);
void HAL_DelayUs(uint32_t us);

#endif /*_HAL_TIMER_H_*/
