/*
 * gps.c
 *
 *  Created on: Apr 1, 2026
 *      Author: OM
 */

#include "gps.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static UART_HandleTypeDef *gps_uart;

static uint8_t rx_char;
static char gps_buffer[GPS_BUFFER_SIZE];
static uint8_t gps_rx_index = 0;

static GPS_Data_t gps_data;
static uint8_t data_ready = 0;

/* ---------------- UART INIT ---------------- */
void GPS_Init(UART_HandleTypeDef *huart)
{
    gps_uart = huart;
    HAL_UART_Receive_IT(gps_uart, &rx_char, 1);
}

/* ---------------- INTERRUPT CALLBACK ---------------- */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == gps_uart)
    {
        if (rx_char == '\n')   // End of NMEA sentence
        {
            gps_buffer[gps_rx_index] = '\0';
            gps_rx_index = 0;

            GPS_Process();
        }
        else
        {
            if (gps_rx_index < GPS_BUFFER_SIZE - 1)
                gps_buffer[gps_rx_index++] = rx_char;
        }

        HAL_UART_Receive_IT(gps_uart, &rx_char, 1);
    }
}

/* Convert ddmm.mmmm → decimal */
float convert_to_decimal(float raw)
{
    int degrees = (int)(raw / 100);
    float minutes = raw - (degrees * 100);
    return degrees + (minutes / 60.0);
}

void GPS_Process(void)
{
    // Check if this is GPGGA sentence
    if (strncmp(gps_buffer, "$GPGGA", 6) != 0)
        return;

    char *token;
    int field = 0;

    float lat = 0, lon = 0;
    char lat_dir = 'N', lon_dir = 'E';
    int fix = 0;

    token = strtok(gps_buffer, ",");

    while (token != NULL)
    {
        field++;

        switch (field)
        {
            case 3: lat = atof(token); break;
            case 4: lat_dir = token[0]; break;
            case 5: lon = atof(token); break;
            case 6: lon_dir = token[0]; break;
            case 7: fix = atoi(token); break;
        }

        token = strtok(NULL, ",");
    }

    // If no fix → ignore
    if (fix == 0)
        return;

    // Convert format
    gps_data.latitude = convert_to_decimal(lat);
    gps_data.longitude = convert_to_decimal(lon);

    // Apply direction
    if (lat_dir == 'S') gps_data.latitude *= -1;
    if (lon_dir == 'W') gps_data.longitude *= -1;

    data_ready = 1;

}

uint8_t GPS_GetData(GPS_Data_t *data)
{
    if (data_ready)
    {
        *data = gps_data;
        data_ready = 0;
        return 1;
    }
    return 0;

}

/*
void GPS_Process(void)
{
    if (!(gps_buffer[0] == '$' &&
          gps_buffer[1] == 'G' &&
          gps_buffer[2] == 'P' &&
          gps_buffer[3] == 'G' &&
          gps_buffer[4] == 'G' &&
          gps_buffer[5] == 'A'))
        return;

    char *ptr = gps_buffer;
    int field = 0;

    float lat = 0, lon = 0;
    char lat_dir = 'N', lon_dir = 'E';
    int fix = 0;

    while (*ptr)
    {
        if (*ptr == ',')
        {
            field++;
            ptr++;

            // -------- SIMPLE PARSING --------
            if (field == 2)   // latitude
            {
                lat = 0;
                while (*ptr >= '0' && *ptr <= '9')
                {
                    lat = lat * 10 + (*ptr - '0');
                    ptr++;
                }

                if (*ptr == '.')
                {
                    float frac = 0, div = 1;
                    ptr++;

                    while (*ptr >= '0' && *ptr <= '9')
                    {
                        frac = frac * 10 + (*ptr - '0');
                        div *= 10;
                        ptr++;
                    }
                    lat += frac / div;
                }
            }

            else if (field == 3)   // N/S
            {
                lat_dir = *ptr;
            }

            else if (field == 4)   // longitude
            {
                lon = 0;
                while (*ptr >= '0' && *ptr <= '9')
                {
                    lon = lon * 10 + (*ptr - '0');
                    ptr++;
                }

                if (*ptr == '.')
                {
                    float frac = 0, div = 1;
                    ptr++;

                    while (*ptr >= '0' && *ptr <= '9')
                    {
                        frac = frac * 10 + (*ptr - '0');
                        div *= 10;
                        ptr++;
                    }
                    lon += frac / div;
                }
            }

            else if (field == 5)   // E/W
            {
                lon_dir = *ptr;
            }

            else if (field == 6)   // fix
            {
                fix = 0;
                while (*ptr >= '0' && *ptr <= '9')
                {
                    fix = fix * 10 + (*ptr - '0');
                    ptr++;
                }
            }
        }
        else
        {
            ptr++;
        }
    }

    // -------- VALID FIX --------
    if (fix == 0)
        return;

    // -------- CONVERT --------
    gps_data.latitude = convert_to_decimal(lat);
    gps_data.longitude = convert_to_decimal(lon);

    if (lat_dir == 'S') gps_data.latitude *= -1;
    if (lon_dir == 'W') gps_data.longitude *= -1;

    data_ready = 1;
}
*/
