/*
 * gps.h
 *
 *  Created on: Apr 1, 2026
 *      Author: OM
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "stm32f4xx_hal.h"

#define GPS_BUFFER_SIZE 128

typedef struct
{
    float latitude;
    float longitude;
} GPS_Data_t;

void GPS_Init(UART_HandleTypeDef *huart);
void GPS_Process(void);
uint8_t GPS_GetData(GPS_Data_t *data);

#endif /* INC_GPS_H_ */
