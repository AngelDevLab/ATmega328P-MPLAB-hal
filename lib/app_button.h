#ifndef _APP_BUTTON_H_
#define _APP_BUTTON_H_

#include "stdint.h"
#include "stdbool.h"
#include "hal_button.h"

#define APP_BUTTON_POWER_ON_RESET_NUMBER BUTTON_NUM0
#define APP_BUTTON_CLICK_MIN_TIME 20                      // if button click time is low this value ,not trigger
#define APP_BUTTON_LONG_PRESS_TIME 500                    // if button press time over this value,arrive long press event
#define APP_BUTTON_PRESSING_CALLBACK_TRIGGER_INTERVAL 100 // pressing callback trigger interval
#define APP_BUTTON_SHORT_CLICK_INTERVAL 300               // between click interval
#define APP_BUTTON_POWER_ON_RESET_TIMEOUT 3000            // over this time,call app_button_power_on_unreset_event_callback callback
#define APP_BUTTON_CLICK_3_EVENT_TIMEROUT 500             // this time need to over pressing trigger interval

typedef enum
{
    BUTTON_POWER_ON_RESET_PRESS,
    BUTTON_POWER_ON_PRESS_IN_TIMEOUT,
    BUTTON_POWER_ON_PRESS_TIMEOUT,
    BUTTON_LOW,
    BUTTON_CLICK_1,
    BUTTON_CLICK_2,
    BUTTON_CLICK_5,
    BUTTON_CLICK_7,
    BUTTON_CLICK_10,
    BUTTON_PRESSING,
    BUTTON_PRESSED_LONG,
    BUTTON_BTN0_CLICK_3_AND_BTN1_CLICK_1,
    BUTTON_BTN0_CLICK_3_AND_BTN0_LONG_PRESS_3SEC,
} app_button_event_t;

typedef enum
{
    BUTTON_PROCESS_PRESSING,
    BUTTON_PROCESS_SHORT_CLICK,
} app_button_event_process_t;

typedef struct
{
    bool press_flag;
    uint16_t step;
    uint8_t short_press_count;
    uint32_t short_press_time;
    uint32_t press_total_time;
    uint32_t press_trigger_timer;
} app_button_process_param_t;

typedef struct
{
    bool flag;
    hal_button_num_t num;
    hal_button_event_t event;
} app_button_event_parm_t;

typedef struct
{
    bool power_on_reset_flag;
    app_button_event_parm_t event;
    app_button_process_param_t process_parm[HAL_BUTTON_NUM];

    bool button0_click3_event;
    uint32_t button0_click3_event_timer;

    uint32_t (*time_ms_tick_get)();
} app_button_t;

void app_button_init(uint32_t (*timeMsTickHandler)());
void app_button_process(void);
__attribute__((weak)) void app_button_event_handler(hal_button_num_t num, app_button_event_t event, uint32_t time_ms);

#endif /*_APP_BUTTON_H_*/
