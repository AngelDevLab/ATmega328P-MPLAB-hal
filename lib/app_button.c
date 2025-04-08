#include "app_button.h"

static app_button_t APP_BUTTON = {0};

static void app_button_click_event_callback(hal_button_num_t num, hal_button_event_t event)
{
    APP_BUTTON.event.flag = true;
    APP_BUTTON.event.num = num;
    APP_BUTTON.event.event = event;
}

static void app_button_event_process(hal_button_num_t num, app_button_event_process_t event, uint32_t time_ms, uint32_t count)
{
    switch (event)
    {
    case BUTTON_PROCESS_SHORT_CLICK:
    {
        if (count == 1)
        {
            app_button_event_handler(num, BUTTON_CLICK_1, 0);
        }
        else if (count == 2)
        {
            app_button_event_handler(num, BUTTON_CLICK_2, 0);
        }
        else if (count == 5)
        {
            app_button_event_handler(num, BUTTON_CLICK_5, 0);
        }
        else if (count == 7)
        {
            app_button_event_handler(num, BUTTON_CLICK_7, 0);
        }
        else if (count == 10)
        {
            app_button_event_handler(num, BUTTON_CLICK_10, 0);
        }

        // click 3 times check
        if (num == BUTTON_NUM0)
        {
            APP_BUTTON.button0_click3_event = false;

            if (count == 3)
            {
                APP_BUTTON.button0_click3_event = true;
                APP_BUTTON.button0_click3_event_timer = APP_BUTTON.time_ms_tick_get();
            }
        }

        if (HAL_BUTTON_NUM >= 2)
        {
            if (num == BUTTON_NUM1)
            {
                if (count == 1)
                {
                    if (APP_BUTTON.button0_click3_event)
                    {
                        APP_BUTTON.button0_click3_event = false;
                        app_button_event_handler((hal_button_num_t)0, BUTTON_BTN0_CLICK_3_AND_BTN1_CLICK_1, 0);
                    }
                }
            }
        }
    }
    break;
    case BUTTON_PROCESS_PRESSING:
    {
        if (APP_BUTTON.button0_click3_event)
        {
            APP_BUTTON.button0_click3_event_timer = APP_BUTTON.time_ms_tick_get();

            if (time_ms >= 3000)
            {
                APP_BUTTON.button0_click3_event = false;
                app_button_event_handler((hal_button_num_t)0, BUTTON_BTN0_CLICK_3_AND_BTN0_LONG_PRESS_3SEC, 0);
            }
        }

        app_button_event_handler(num, BUTTON_PRESSING, time_ms);
    }
    break;
    }
}

void app_button_init(uint32_t (*timeMsTickHandler)())
{
    APP_BUTTON.time_ms_tick_get = timeMsTickHandler;

    hal_button_config_t button_config = {
        .power_on_reset_num = APP_BUTTON_POWER_ON_RESET_NUMBER,
        .event_callback = &app_button_click_event_callback,
    };

    hal_button_config(&button_config);
    hal_button_init();
}

void app_button_process(void)
{
    if (APP_BUTTON.event.flag)
    {
        APP_BUTTON.event.flag = false;

        switch (APP_BUTTON.event.event)
        {
        case BUTTON_POWER_ON_CLICK:
            APP_BUTTON.power_on_reset_flag = true;
            app_button_event_handler(APP_BUTTON_POWER_ON_RESET_NUMBER, BUTTON_POWER_ON_RESET_PRESS, 0);
            break;
        case BUTTON_EVENT_PRESS:
            if (!APP_BUTTON.process_parm[APP_BUTTON.event.num].press_flag)
            {
                app_button_event_handler(APP_BUTTON.event.num, BUTTON_LOW, 0);
            }
            APP_BUTTON.process_parm[APP_BUTTON.event.num].press_flag = true;
            APP_BUTTON.process_parm[APP_BUTTON.event.num].press_total_time = APP_BUTTON.time_ms_tick_get();
            break;
        case BUTTON_EVENT_RELEASE:
            APP_BUTTON.process_parm[APP_BUTTON.event.num].press_flag = false;

            if (APP_BUTTON.power_on_reset_flag)
            {
                APP_BUTTON.power_on_reset_flag = false;

                if (APP_BUTTON.time_ms_tick_get() <= APP_BUTTON_POWER_ON_RESET_TIMEOUT)
                {
                    app_button_event_handler(APP_BUTTON_POWER_ON_RESET_NUMBER, BUTTON_POWER_ON_PRESS_IN_TIMEOUT, 0);
                }
                else
                {
                    app_button_event_handler(APP_BUTTON_POWER_ON_RESET_NUMBER, BUTTON_POWER_ON_PRESS_TIMEOUT, 0);
                }
            }
            break;
        }
    }

    if (APP_BUTTON.power_on_reset_flag)
    {
        if (APP_BUTTON.time_ms_tick_get() > APP_BUTTON_POWER_ON_RESET_TIMEOUT)
        {
            APP_BUTTON.power_on_reset_flag = false;
            app_button_event_handler(APP_BUTTON_POWER_ON_RESET_NUMBER, BUTTON_POWER_ON_PRESS_TIMEOUT, 0);
        }
    }

    for (hal_button_num_t num = BUTTON_NUM0; num < HAL_BUTTON_NUM; num++)
    {
        switch (APP_BUTTON.process_parm[num].step)
        {
        case 0:
            if (APP_BUTTON.process_parm[num].press_flag)
            {
                if (APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_total_time >= APP_BUTTON_CLICK_MIN_TIME)
                {
                    APP_BUTTON.process_parm[num].step = 100;
                }
            }
            break;
        case 100:
            if (APP_BUTTON.process_parm[num].press_flag)
            {
                if (APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_total_time > APP_BUTTON_LONG_PRESS_TIME)
                {
                    APP_BUTTON.process_parm[num].press_trigger_timer = APP_BUTTON.time_ms_tick_get();
                    app_button_event_process(num, BUTTON_PROCESS_PRESSING, APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_total_time, 0);
                    APP_BUTTON.process_parm[num].step = 200;
                }
            }
            break;
        case 200:
            if (APP_BUTTON.process_parm[num].press_flag)
            {
                if (APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_trigger_timer > APP_BUTTON_PRESSING_CALLBACK_TRIGGER_INTERVAL)
                {
                    APP_BUTTON.process_parm[num].press_trigger_timer = APP_BUTTON.time_ms_tick_get();
                    app_button_event_process(num, BUTTON_PROCESS_PRESSING, APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_total_time, 0);
                }
            }
            break;
        }

        if (!APP_BUTTON.process_parm[num].press_flag)
        {
            if (APP_BUTTON.process_parm[num].step == 100)
            {
                APP_BUTTON.process_parm[num].short_press_time = APP_BUTTON.time_ms_tick_get();
                APP_BUTTON.process_parm[num].short_press_count++;
                APP_BUTTON.process_parm[num].step = 0;
            }
            else if (APP_BUTTON.process_parm[num].step == 200)
            {
                app_button_event_handler(num, BUTTON_PRESSED_LONG, APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].press_total_time);
                APP_BUTTON.process_parm[num].step = 0;
            }
        }

        if (APP_BUTTON.process_parm[num].short_press_count > 0)
        {
            if (APP_BUTTON.time_ms_tick_get() - APP_BUTTON.process_parm[num].short_press_time >= APP_BUTTON_SHORT_CLICK_INTERVAL)
            {
                app_button_event_process(num, BUTTON_PROCESS_SHORT_CLICK, 0, APP_BUTTON.process_parm[num].short_press_count);
                APP_BUTTON.process_parm[num].short_press_count = 0;
            }
        }
    }

    // click 3 event timeout
    if (APP_BUTTON.button0_click3_event)
    {
        if (APP_BUTTON.time_ms_tick_get() - APP_BUTTON.button0_click3_event_timer >= APP_BUTTON_CLICK_3_EVENT_TIMEROUT)
        {
            APP_BUTTON.button0_click3_event = false;
        }
    }
}

__attribute__((weak)) void app_button_event_handler(hal_button_num_t num, app_button_event_t event, uint32_t time_ms)
{
    
}
