/*
 * lcd.c
 *
 *  Created on: Apr 1, 2026
 *      Author: OM
 */

#include "lcd.h"

/* Change pins as per your connection */
#define RS_PIN GPIO_PIN_0
#define EN_PIN GPIO_PIN_1
#define D4_PIN GPIO_PIN_12
#define D5_PIN GPIO_PIN_13
#define D6_PIN GPIO_PIN_14
#define D7_PIN GPIO_PIN_15

#define LCD_PORT GPIOB

void LCD_EnablePulse()
{
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(LCD_PORT, EN_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void LCD_Send4Bits(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_PORT, D4_PIN, (data >> 0) & 1);
    HAL_GPIO_WritePin(LCD_PORT, D5_PIN, (data >> 1) & 1);
    HAL_GPIO_WritePin(LCD_PORT, D6_PIN, (data >> 2) & 1);
    HAL_GPIO_WritePin(LCD_PORT, D7_PIN, (data >> 3) & 1);

    LCD_EnablePulse();
}

void LCD_SendCommand(uint8_t cmd)
{
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_RESET);

    LCD_Send4Bits(cmd >> 4);
    LCD_Send4Bits(cmd & 0x0F);

    HAL_Delay(2);
}

void LCD_SendData(uint8_t data)
{
    HAL_GPIO_WritePin(LCD_PORT, RS_PIN, GPIO_PIN_SET);

    LCD_Send4Bits(data >> 4);
    LCD_Send4Bits(data & 0x0F);

    HAL_Delay(2);
}

void LCD_Init(void)
{
	 HAL_Delay(50);   // 🔥 power stabilization

	    LCD_SendCommand(0x33);
	    HAL_Delay(5);

	    LCD_SendCommand(0x32);
	    HAL_Delay(5);

	    LCD_SendCommand(0x28);
	    HAL_Delay(1);

	    LCD_SendCommand(0x0C);
	    HAL_Delay(1);

	    LCD_SendCommand(0x06);
	    HAL_Delay(1);

	    LCD_SendCommand(0x01);
	    HAL_Delay(5);

	    /*
    HAL_Delay(50);

    LCD_Send4Bits(0x03);
    HAL_Delay(5);
    LCD_Send4Bits(0x02);

    LCD_SendCommand(0x28); // 4-bit, 2-line
    LCD_SendCommand(0x0C); // display ON
    LCD_SendCommand(0x06); // entry mode
    LCD_SendCommand(0x01); // clear
    */
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    if (row == 0)
        address = 0x80 + col;   // Line 1
    else
        address = 0xC0 + col;   // Line 2

    LCD_SendCommand(address);
}

void LCD_Print(char *str)
{
    while (*str)
    {
        LCD_SendData(*str++);
    }
}
