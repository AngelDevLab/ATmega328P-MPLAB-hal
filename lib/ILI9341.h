#ifndef _ILI9341_H_
#define _ILI9341_H_

#include "atmega328p_hal.h"
#include <avr/io.h>
#include <avr/pgmspace.h>

#define DC_INIT()               SET_BIT(DDRD, DDD7)
#define DC_HIGH()               SET_BIT(PORTD, PD7)
#define DC_LOW()                CLEAR_BIT(PORTD, PD7)

#define RST_INIT()              SET_BIT(DDRD, DDD6)
#define RST_HIGH()              SET_BIT(PORTD, PD6)
#define RST_LOW()               CLEAR_BIT(PORTD, PD6)

#define ILI9341_WIDTH           320
#define ILI9341_HEIGHT          240
#define ILI9341_BURST_PIXELS  	400

#define BLACK      				0x0000
#define NAVY        			0x000F
#define DARKGREEN   			0x03E0
#define DARKCYAN    			0x03EF
#define MAROON      			0x7800
#define PURPLE      			0x780F
#define OLIVE       			0x7BE0
#define LIGHTGREY   			0xC618
#define DARKGREY    			0x7BEF
#define BLUE        			0x001F
#define GREEN       			0x07E0
#define CYAN        			0x07FF
#define RED         			0xF800
#define MAGENTA     			0xF81F
#define YELLOW      			0xFFE0
#define WHITE       			0xFFFF
#define ORANGE      			0xFD20
#define GREENYELLOW 			0xAFE5
#define PINK        			0xF81F

#define SCREEN_VERTICAL_1		0
#define SCREEN_HORIZONTAL_1		1
#define SCREEN_VERTICAL_2		2
#define SCREEN_HORIZONTAL_2		3

void ILI9341_WriteCommand(uint8_t cmd);
void ILI9341_WriteData(uint8_t data);
void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len);
void ILI9341_Reset(void);
void ILI9341_Enable(void);
void ILI9341_Init(void);
void ILI9341_SetRotation(uint8_t rotation);
void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void ILI9341_DrawFilledRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_DrawImage_At_Scaled_Fast(const uint8_t* image,
                                      uint16_t img_width,
                                      uint16_t img_height,
                                      uint16_t x_pos,
                                      uint16_t y_pos,
                                      uint8_t scale);


#endif /* _ILI9341_H_ */