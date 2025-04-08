#include "hal_timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define PRESCALER               64
#define TIMER0_TARGET_HZ        1000 //1ms
#define OCR0A_VALUE             ((F_CPU / PRESCALER / TIMER0_TARGET_HZ) - 1)

volatile uint32_t system_tick = 0;

ISR(TIMER0_COMPA_vect) {
    system_tick++;
}

void HAL_TIMER_Init(void)
{
    // Set CTC mode
    CLEAR_BIT(TCCR0B, WGM02);
    SET_BIT(TCCR0A, WGM01);
    SET_BIT(TCCR0A, WGM00);
    
    // Set Prescaler 64
    CLEAR_BIT(TCCR0B, CS02);
    SET_BIT(TCCR0B, CS01);
    SET_BIT(TCCR0B, CS00);
    
    //Output Compare Register
    OCR0A = OCR0A_VALUE;

    // Timer Output Compare Match A Interrupt Enable
    SET_BIT(TIMSK0, OCIE0A);
}

uint32_t HAL_GetTick(void) {
    uint32_t tick;

    cli();
    tick = system_tick;
    sei();
    return tick;
}

void HAL_Delay(uint32_t delay)
{
    while (delay--) {
        _delay_ms(1);
    }
}

void HAL_DelayUs(uint32_t us)
{
    while (us--) {
        _delay_us(1);
    }
}
