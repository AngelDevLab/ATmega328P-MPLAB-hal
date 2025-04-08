#include "hal_button.h"

#include <avr/interrupt.h>
#include <avr/io.h>

hal_button_t HAL_BUTTON = {
    .config =
        {
            .power_on_reset_num = BUTTON_NUM0,
            .event_callback = NULL,
        },

    .inited = {0},
    .power_on_is_press = false,
};

static void HAL_BUTTON_INIT(hal_button_num_t num) {
    switch (num) {
        case BUTTON_NUM0:
            HAL_GPIO_SetMode(GPIOD, GPIO_PIN_2, GPIO_INPUT_PULLUP);
            SET_BIT(EIMSK, INT0);
            SET_BIT(EICRA, ISC00);
            break;
        case BUTTON_NUM1:
            HAL_GPIO_SetMode(GPIOD, GPIO_PIN_3, GPIO_INPUT_PULLUP);
            SET_BIT(EIMSK, INT1);
            SET_BIT(EICRA, ISC10);
            break;
        default:
            break;
    }

    HAL_BUTTON.inited[num] = true;
}

static bool HAL_BUTTON_GPIO_TRIGGER_STATE_GET(hal_button_num_t num) {
    switch (num) {
        case BUTTON_NUM0:
            return !(PIND & (1 << PD2)); // active low
        case BUTTON_NUM1:
            return !(PIND & (1 << PD3));
        default:
            return false;
    }
}


ISR(INT0_vect) {
    if (HAL_BUTTON.config.event_callback) {
        if (HAL_BUTTON_GPIO_TRIGGER_STATE_GET(BUTTON_NUM0)) {
            HAL_BUTTON.config.event_callback(BUTTON_NUM0, BUTTON_EVENT_PRESS);
        } else {
            HAL_BUTTON.config.event_callback(BUTTON_NUM0, BUTTON_EVENT_RELEASE);
        }
    }
}

ISR(INT1_vect) {
    if (HAL_BUTTON.config.event_callback) {
        if (HAL_BUTTON_GPIO_TRIGGER_STATE_GET(BUTTON_NUM1)) {
            HAL_BUTTON.config.event_callback(BUTTON_NUM1, BUTTON_EVENT_PRESS);
        } else {
            HAL_BUTTON.config.event_callback(BUTTON_NUM1, BUTTON_EVENT_RELEASE);
        }
    }
}

void hal_button_config(hal_button_config_t *config)
{
    memcpy(&HAL_BUTTON.config, config, sizeof(hal_button_config_t));
}

void hal_button_init(void) {
    for (int num = 0; num < HAL_BUTTON_NUM; num++) {
        HAL_BUTTON_INIT((hal_button_num_t)num);
    }

    if (HAL_BUTTON_GPIO_TRIGGER_STATE_GET(HAL_BUTTON.config.power_on_reset_num)) {
        HAL_BUTTON.power_on_is_press = true;
        if (HAL_BUTTON.config.event_callback) {
            HAL_BUTTON.config.event_callback(HAL_BUTTON.config.power_on_reset_num, BUTTON_POWER_ON_CLICK);
        }
    }

    sei();
}
