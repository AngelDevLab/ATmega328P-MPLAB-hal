#include "hal_gpio.h"
#include <avr/io.h>

GPIO_TypeDef GPIOB_struct = { &DDRB, &PORTB, &PINB };
GPIO_TypeDef GPIOC_struct = { &DDRC, &PORTC, &PINC };
GPIO_TypeDef GPIOD_struct = { &DDRD, &PORTD, &PIND };

void HAL_GPIO_SetMode(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode mode) {
    switch (mode) {
        case GPIO_INPUT:
            CLEAR_BIT(*(port->ddr), pin);
            CLEAR_BIT(*(port->port), pin);
            break;

        case GPIO_OUTPUT:
            SET_BIT(*(port->ddr), pin);
            break;

        case GPIO_INPUT_PULLUP:
            CLEAR_BIT(*(port->ddr), pin);
            SET_BIT(*(port->port), pin);
            break;
    }
}

void HAL_GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t val) {
    if (val)
        SET_BIT(*(port->port), pin);
    else
        CLEAR_BIT(*(port->port), pin);
}

GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin) {
    return (READ_BIT(*(port->pin), pin)) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void HAL_GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin) {
    TOGGLE_BIT(*(port->port), pin);
}
