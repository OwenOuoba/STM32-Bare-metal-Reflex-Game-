#include "ssd1306.h"

uint8_t SSD1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

void SSD1306_init(void)
{
  HAL_Delay(100);

  SSD1306_SendCommand(0xAE); // display off
  SSD1306_SendCommand(0xD5); SSD1306_SendCommand(0x80);
  SSD1306_SendCommand(0xA8); SSD1306_SendCommand(0x3F);
  SSD1306_SendCommand(0xD3); SSD1306_SendCommand(0x00);
  SSD1306_SendCommand(0x40);
  SSD1306_SendCommand(0x8D); SSD1306_SendCommand(0x14);
  SSD1306_SendCommand(0x20); SSD1306_SendCommand(0x02); // page mode
  SSD1306_SendCommand(0xA1);
  SSD1306_SendCommand(0xC8);
  SSD1306_SendCommand(0xDA); SSD1306_SendCommand(0x12);
  SSD1306_SendCommand(0x81); SSD1306_SendCommand(0xCF);
  SSD1306_SendCommand(0xD9); SSD1306_SendCommand(0xF1);
  SSD1306_SendCommand(0xDB); SSD1306_SendCommand(0x40);
  SSD1306_SendCommand(0xA4);
  SSD1306_SendCommand(0xA6);
  SSD1306_SendCommand(0xAF); // display on
}

void SSD1306_SendCommand(uint8_t cmd){
	uint8_t buf[2];
	buf[0] = 0x00;
	buf[1] = cmd;
	HAL_I2C_Master_Transmit(&hi2c1, 0x3C << 1, buf, 2, HAL_MAX_DELAY);
}
void SSD1306_SendData(uint8_t data){
	uint8_t buf[2];
	buf[0] = 0x40;
	buf[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, 0x3C << 1, buf, 2, HAL_MAX_DELAY);
}

void SSD1306_Set_Cursor(uint8_t page, uint8_t col){
	page = 0xB0 + page;
	SSD1306_SendCommand(page);
	SSD1306_SendCommand(0x00 + (col & 0x0F));
	SSD1306_SendCommand(0x10 + (col >> 4));
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    uint8_t index = x + (y/8) * 128;
    uint8_t bit   = y%8;

    if (color)
    	SSD1306_Buffer[index] |= (1U << bit);
    else
    	SSD1306_Buffer[index] &= ~(1U << bit);
}

void SSD1306_Update(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        SSD1306_SendCommand(0xB0 + page);  // sélectionne la page
        SSD1306_SendCommand(0x00);          // colonne 0 lower nibble
        SSD1306_SendCommand(0x10);          // colonne 0 upper nibble

        for (uint8_t col = 0; col < 128; col++)
        {
            SSD1306_SendData(SSD1306_Buffer[page * 128 + col]);
        }
    }
}
