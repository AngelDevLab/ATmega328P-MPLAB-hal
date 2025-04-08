#ifndef _HAL_BUTTON_H_
#define _HAL_BUTTON_H_

#include "stdint.h"
#include "stdbool.h"
#include "string.h"

#include "hal_gpio.h"

#define HAL_BUTTON_LIST                            \
    X(BUTTON_NUM0, BUTTON_1, GPIOD, GPIO_PIN_2, 1) \
    X(BUTTON_NUM1, BUTTON_2, GPIOD, GPIO_PIN_3, 1)

#define X(a, b, c, d, e) a,
typedef enum
{
    HAL_BUTTON_LIST HAL_BUTTON_NUM,
} hal_button_num_t;
#undef X

#define X(a, b, c, d, e) b,
typedef enum
{
    HAL_BUTTON_LIST
} hal_button_name_t;
#undef X

#define X(a, b, c, d, e) c,
static GPIO_TypeDef *const HAL_BUTTON_PORT[] = {HAL_BUTTON_LIST};
#undef X

#define X(a, b, c, d, e) d,
static const uint64_t HAL_BUTTON_PIN[] = {HAL_BUTTON_LIST};
#undef X

#define X(a, b, c, d, e) e,
static const bool HAL_BUTTON_ENABLE[] = {HAL_BUTTON_LIST};
#undef X

typedef enum
{
    BUTTON_EVENT_PRESS,
    BUTTON_EVENT_RELEASE,
    BUTTON_POWER_ON_CLICK,
} hal_button_event_t;

typedef struct
{
    hal_button_num_t power_on_reset_num;
    void (*event_callback)(hal_button_num_t, hal_button_event_t);
} hal_button_config_t;

typedef struct
{
    hal_button_config_t config;
    bool inited[HAL_BUTTON_NUM];
    bool power_on_is_press;
} hal_button_t;

void hal_button_config(hal_button_config_t *config);
void hal_button_init(void);

#endif /*_HAL_BUTTON_H_*/
