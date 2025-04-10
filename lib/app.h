#ifndef _APP_H_
#define _APP_H_

#include "atmega328p_hal.h"
#include <avr/pgmspace.h>

typedef enum {
    GAME_IDLE,
    GAME_START,
    GAME_PLAYING,
    GAME_FAIL,   
    GAME_STOP,   
}game_status_t;

typedef struct game_object_t {
    uint16_t width;
    uint16_t height;
    int x;
    int y;
    int dx;
    int dy;

    void (*draw)(struct game_object_t *self);  // 函數指標，傳入自己
} game_object_t;

void app_init(void);
void app_process(void);

#endif /*_APP_H_*/
