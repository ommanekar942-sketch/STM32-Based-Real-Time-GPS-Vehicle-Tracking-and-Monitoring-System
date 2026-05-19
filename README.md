# STM32-Based GPS Vehicle Tracking and Monitoring System

> Real-time GPS vehicle tracking system using STM32F407, NEO-6M GPS module, ESP8266 WiFi module, LCD display, UART communication, and Google Maps integration.

---

# Project Overview

This project implements a real-time GPS vehicle tracking and monitoring system using the STM32F407 Discovery board.

The STM32 receives GPS coordinates from the GPS module through UART communication, processes NMEA data packets, displays live coordinates on a 16x2 LCD, and transmits location data to an ESP8266 WiFi module.

The ESP8266 hosts a web server that displays:
- Latitude
- Longitude
- Google Maps location link

This project demonstrates practical embedded systems and IoT concepts including:
- UART communication
- GPS NMEA parsing
- Interrupt-based data reception
- LCD interfacing
- ESP8266 communication
- Web server implementation
- Real-time location monitoring

---

# Features

- Real-time GPS coordinate tracking
- UART-based GPS communication
- NMEA sentence parsing
- Latitude and longitude extraction
- 16x2 LCD display interfacing
- ESP8266 WiFi communication
- Web-based monitoring dashboard
- Google Maps integration
- Interrupt-driven UART reception
- STM32 HAL-based firmware

---

# Hardware Components

| Component | Description |
|---|---|
| STM32F407 Discovery Board | Main microcontroller |
| NEO-6M GPS Module | GPS receiver |
| ESP8266 WiFi Module | Wireless communication |
| 16x2 LCD Display | Coordinate display |
| Jumper Wires | Hardware connections |
| USB Cable | STM32 power and programming |

---

# System Architecture

```text
GPS Module
     ↓
 STM32F407
     ↓
16x2 LCD Display
     ↓
 ESP8266 WiFi Module
     ↓
 Web Dashboard
     ↓
 Google Maps
```

---

# Exact Hardware Connections

# 1. GPS Module to STM32

| GPS Module Pin | STM32 Pin | Peripheral |
|---|---|---|
| TX | USART2 RX | GPS Data Input |
| RX | USART2 TX | Optional |
| VCC | 5V | Power Supply |
| GND | GND | Common Ground |

### UART Configuration

| Peripheral | Baud Rate |
|---|---|
| USART2 | 9600 |

### Description

STM32 receives NMEA GPS data from the GPS module through USART2 using interrupt-based UART reception.

---

# 2. STM32 to ESP8266

| STM32 Pin | ESP8266 Pin | Function |
|---|---|---|
| USART3 TX | RX | GPS Data Transmission |
| USART3 RX | TX | Optional |
| GND | GND | Common Ground |

### UART Configuration

| Peripheral | Baud Rate |
|---|---|
| USART3 | 9600 |

### Description

STM32 transmits processed GPS coordinates to the ESP8266 WiFi module using UART communication.

ESP8266 hosts a web server for real-time monitoring.

---

# 3. LCD Connections (4-bit Mode)

| LCD Pin | STM32 Pin | Function |
|---|---|---|
| RS | PB0 | Register Select |
| EN | PB1 | Enable |
| D4 | PB12 | Data Bit 4 |
| D5 | PB13 | Data Bit 5 |
| D6 | PB14 | Data Bit 6 |
| D7 | PB15 | Data Bit 7 |
| VSS | GND | Ground |
| VDD | 5V | Power |
| RW | GND | Write Mode |

### Description

The LCD operates in 4-bit mode for displaying:
- Latitude
- Longitude

---

# 4. Power Connections

| Device | Supply |
|---|---|
| STM32F407 Discovery | USB Power |
| GPS Module | 5V |
| LCD Display | 5V |
| ESP8266 | 3.3V |
| All GND Pins | Common Ground |

---

# Important Notes

- All grounds must be connected together.
- ESP8266 operates at 3.3V logic level.
- GPS coordinates are extracted from `$GPGGA` NMEA sentences.
- UART interrupt mode is used for real-time data reception.
- LCD operates in 4-bit communication mode.

---

# STM32 Peripheral Configuration

| Peripheral | Purpose |
|---|---|
| USART2 | GPS Communication |
| USART3 | ESP8266 Communication |
| GPIO | LCD Interface |
| UART Interrupts | GPS Data Reception |

---

# Software Used

- STM32CubeIDE
- STM32CubeMX
- Embedded C
- STM32 HAL Drivers
- Arduino IDE (ESP8266)

---

# Working Principle

1. GPS module continuously transmits NMEA sentences.
2. STM32 receives GPS data using USART2 interrupt mode.
3. STM32 parses `$GPGGA` sentences.
4. Latitude and longitude are extracted and converted to decimal format.
5. Coordinates are displayed on the 16x2 LCD.
6. STM32 transmits coordinates to ESP8266 using USART3.
7. ESP8266 hosts a web server displaying live GPS data.
8. Google Maps link provides real-time location visualization.

---

# GPS Data Processing

The STM32 firmware:
- receives raw NMEA strings
- identifies `$GPGGA` packets
- extracts:
  - latitude
  - longitude
  - GPS fix status
- converts coordinates from:
  ```text
  ddmm.mmmm
  ```
  to:
  ```text
  decimal degrees
  ```

---

# ESP8266 Web Dashboard

The ESP8266 web server displays:
- Latitude
- Longitude
- Google Maps location button

The webpage automatically refreshes every 2 seconds.

---

# Project Structure

```bash
Core/
├── Inc/
│   ├── gps.h
│   └── lcd.h
│
├── Src/
│   ├── gps.c
│   ├── lcd.c
│   └── main.c
│
Drivers/

ESP8266_Code/

STM32_GPS_Tracking.ioc

README.md
```

---

# Applications

- Vehicle tracking systems
- Fleet monitoring
- Asset tracking
- IoT-based navigation systems
- Real-time location monitoring
- Embedded telemetry systems

---

# Learning Outcomes

Through this project, I learned:

- STM32 UART communication
- Interrupt-based UART reception
- GPS NMEA sentence parsing
- LCD interfacing in 4-bit mode
- ESP8266 communication
- Web server implementation
- Real-time embedded systems development
- Embedded C programming
- STM32 HAL driver usage

---

# Future Improvements

- Google Maps live tracking
- SD card data logging
- GSM-based remote tracking
- Mobile application integration
- FreeRTOS implementation
- OLED display support
- Geofencing alerts
- Cloud database integration

---

