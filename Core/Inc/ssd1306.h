#ifndef SSD1306_H
#define SSD1306_H

#include "main.h"

#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 64

extern uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];  // 1024 bytes
extern I2C_HandleTypeDef hi2c1;

void SSD1306_init(void);
void SSD1306_SendCommand(uint8_t cmd);
void SSD1306_SendData(uint8_t data);
void SSD1306_Set_Cursor(uint8_t page, uint8_t col);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void SSD1306_Update(void);

#endif
