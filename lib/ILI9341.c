#include "ILI9341.h"

volatile uint16_t LCD_WIDTH	 = ILI9341_WIDTH;
volatile uint16_t LCD_HEIGHT = ILI9341_HEIGHT;

void ILI9341_WriteCommand(uint8_t cmd) {
    DC_LOW();
    HAL_SPI_Write(cmd);
}

void ILI9341_WriteData(uint8_t data) {
    DC_HIGH();
    HAL_SPI_Write(data);
}

void ILI9341_WriteBuffer(uint8_t *buffer, uint16_t len)
{
    DC_HIGH();
	HAL_SPI_Transmit(buffer, len);
}

void ILI9341_Reset(void) {
    RST_LOW();
    HAL_Delay(10);
    CS_LOW();
    HAL_Delay(10);
    RST_HIGH();
    CS_HIGH();
}

void ILI9341_Enable(void)
{
	RST_HIGH();
}

void ILI9341_Init(void) {
    DC_INIT();
    RST_INIT();
    
    ILI9341_Enable();
	ILI9341_Reset();

    //SOFTWARE RESET
	ILI9341_WriteCommand(0x01);
	HAL_Delay(10);

	//POWER CONTROL A
	ILI9341_WriteCommand(0xCB);
	ILI9341_WriteData(0x39);
	ILI9341_WriteData(0x2C);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x34);
	ILI9341_WriteData(0x02);

	//POWER CONTROL B
	ILI9341_WriteCommand(0xCF);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x30);

	//DRIVER TIMING CONTROL A
	ILI9341_WriteCommand(0xE8);
	ILI9341_WriteData(0x85);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x78);

	//DRIVER TIMING CONTROL B
	ILI9341_WriteCommand(0xEA);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x00);

	//POWER ON SEQUENCE CONTROL
	ILI9341_WriteCommand(0xED);
	ILI9341_WriteData(0x64);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x12);
	ILI9341_WriteData(0x81);

	//PUMP RATIO CONTROL
	ILI9341_WriteCommand(0xF7);
	ILI9341_WriteData(0x20);

	//POWER CONTROL,VRH[5:0]
	ILI9341_WriteCommand(0xC0);
	ILI9341_WriteData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	ILI9341_WriteCommand(0xC1);
	ILI9341_WriteData(0x10);

	//VCM CONTROL
	ILI9341_WriteCommand(0xC5);
	ILI9341_WriteData(0x3E);
	ILI9341_WriteData(0x28);

	//VCM CONTROL 2
	ILI9341_WriteCommand(0xC7);
	ILI9341_WriteData(0x86);

	//MEMORY ACCESS CONTROL
	ILI9341_WriteCommand(0x36);
	ILI9341_WriteData(0x48);

	//PIXEL FORMAT
	ILI9341_WriteCommand(0x3A);
	ILI9341_WriteData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	ILI9341_WriteCommand(0xB1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x18);

	//DISPLAY FUNCTION CONTROL
	ILI9341_WriteCommand(0xB6);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x82);
	ILI9341_WriteData(0x27);

	//3GAMMA FUNCTION DISABLE
	ILI9341_WriteCommand(0xF2);
	ILI9341_WriteData(0x00);

	//GAMMA CURVE SELECTED
	ILI9341_WriteCommand(0x26);
	ILI9341_WriteData(0x01);

	//POSITIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE0);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x2B);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x4E);
	ILI9341_WriteData(0xF1);
	ILI9341_WriteData(0x37);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x10);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x09);
	ILI9341_WriteData(0x00);

	//NEGATIVE GAMMA CORRECTION
	ILI9341_WriteCommand(0xE1);
	ILI9341_WriteData(0x00);
	ILI9341_WriteData(0x0E);
	ILI9341_WriteData(0x14);
	ILI9341_WriteData(0x03);
	ILI9341_WriteData(0x11);
	ILI9341_WriteData(0x07);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0xC1);
	ILI9341_WriteData(0x48);
	ILI9341_WriteData(0x08);
	ILI9341_WriteData(0x0F);
	ILI9341_WriteData(0x0C);
	ILI9341_WriteData(0x31);
	ILI9341_WriteData(0x36);
	ILI9341_WriteData(0x0F);

	//EXIT SLEEP
	ILI9341_WriteCommand(0x11);
	HAL_Delay(100);

	//TURN ON DISPLAY
	ILI9341_WriteCommand(0x29);
    
    //STARTING ROTATION
	ILI9341_SetRotation(SCREEN_VERTICAL_1);
}

void ILI9341_SetRotation(uint8_t rotation) {
	ILI9341_WriteCommand(0x36);
	HAL_Delay(1);

	switch(rotation)
	{
	case SCREEN_VERTICAL_1:
		ILI9341_WriteData(0x40|0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_1:
		ILI9341_WriteData(0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	case SCREEN_VERTICAL_2:
		ILI9341_WriteData(0x80|0x08);
		LCD_WIDTH  = 240;
		LCD_HEIGHT = 320;
		break;
	case SCREEN_HORIZONTAL_2:
		ILI9341_WriteData(0x40|0x80|0x20|0x08);
		LCD_WIDTH  = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		break;
	}
}

void ILI9341_SetAddress(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint8_t buffer[4];
	buffer[0] = x1 >> 8;
	buffer[1] = x1;
	buffer[2] = x2 >> 8;
	buffer[3] = x2;

	ILI9341_WriteCommand(0x2A);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	buffer[0] = y1 >> 8;
	buffer[1] = y1;
	buffer[2] = y2 >> 8;
	buffer[3] = y2;

	ILI9341_WriteCommand(0x2B);
	ILI9341_WriteBuffer(buffer, sizeof(buffer));

	ILI9341_WriteCommand(0x2C);
}



void ILI9341_FillScreen(uint16_t color)
{
    ILI9341_SetAddress(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT);
    
    uint8_t hi = color >> 8;
    uint8_t lo = color & 0xFF;
    uint8_t burst[ILI9341_BURST_PIXELS * 2];

    for (int i = 0; i < sizeof(burst); i += 2) {
        burst[i]     = hi;
        burst[i + 1] = lo;
    }

    uint32_t total_pixels = 240UL * 320UL;
    uint32_t full_blocks = total_pixels / ILI9341_BURST_PIXELS;
    uint32_t remaining   = total_pixels % ILI9341_BURST_PIXELS;

    for (uint32_t i = 0; i < full_blocks; i++) {
        ILI9341_WriteBuffer(burst, sizeof(burst));
    }

    if (remaining > 0) {
        uint8_t rem_buf[remaining * 2];
        for (uint16_t i = 0; i < remaining * 2; i += 2) {
            rem_buf[i]     = hi;
            rem_buf[i + 1] = lo;
        }
        ILI9341_WriteBuffer(rem_buf, remaining * 2);
    }
}

void ILI9341_DrawImage_At_Scaled_Fast(const uint8_t* image,
                                      uint16_t img_width,
                                      uint16_t img_height,
                                      uint16_t x_pos,
                                      uint16_t y_pos,
                                      uint8_t scale)
{
    if (scale == 0) return;

    uint16_t scaled_width = img_width * scale;
    uint16_t scaled_height = img_height * scale;

    if (x_pos + scaled_width > 320 || y_pos + scaled_height > 240)
        return;

    static uint8_t line_buffer[640];

    for (uint16_t y = 0; y < img_height; y++)
    {
        for (uint16_t x = 0; x < img_width; x++)
        {
            uint32_t index = (y * img_width + x) * 2;
//            uint8_t high = image[index];
//            uint8_t low  = image[index + 1];
            uint8_t high = pgm_read_byte(&image[index]);
            uint8_t low  = pgm_read_byte(&image[index + 1]);

            for (uint8_t dx = 0; dx < scale; dx++)
            {
                uint16_t buf_offset = (x * scale + dx) * 2;
                line_buffer[buf_offset]     = high;
                line_buffer[buf_offset + 1] = low;
            }
        }

        for (uint8_t dy = 0; dy < scale; dy++)
        {
            uint16_t draw_y = y_pos + y * scale + dy;
            ILI9341_SetAddress(x_pos, draw_y, x_pos + scaled_width - 1, draw_y);
            ILI9341_WriteBuffer(line_buffer, scaled_width * 2);
			HAL_DelayUs(10);
        }
    }
}
