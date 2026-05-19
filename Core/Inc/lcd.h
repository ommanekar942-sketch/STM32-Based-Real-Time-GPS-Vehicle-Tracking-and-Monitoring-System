/*
 * lcd.h
 *
 *  Created on: Apr 1, 2026
 *      Author: OM
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f4xx_hal.h"

void LCD_Init(void);
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);
void LCD_Print(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);


#endif /* INC_LCD_H_ */
