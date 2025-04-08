#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#include "hal_config.h"

typedef struct {
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    volatile uint8_t *pin;
} GPIO_TypeDef;

typedef enum
{
  GPIO_PIN_RESET = 0,
  GPIO_PIN_SET
} GPIO_PinState;

typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT,
    GPIO_INPUT_PULLUP
}GPIO_Mode;

extern GPIO_TypeDef GPIOB_struct;
extern GPIO_TypeDef GPIOC_struct;
extern GPIO_TypeDef GPIOD_struct;

#define GPIOB (&GPIOB_struct)
#define GPIOC (&GPIOC_struct)
#define GPIOD (&GPIOD_struct)

#define GPIO_PIN_0  0
#define GPIO_PIN_1  1
#define GPIO_PIN_2  2
#define GPIO_PIN_3  3
#define GPIO_PIN_4  4
#define GPIO_PIN_5  5
#define GPIO_PIN_6  6
#define GPIO_PIN_7  7

void HAL_GPIO_SetMode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode);
void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t val);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);
void HAL_GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin);

#endif /*_HAL_GPIO_H_*/
