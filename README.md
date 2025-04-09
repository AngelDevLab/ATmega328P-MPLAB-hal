# ATmega328P-MPLAB-hal

A basic **Hardware Abstraction Layer (HAL)** and example application

## Development Environment

- **MCU**：Arduino Uno board（ATmega328P）
- **IDE**：MPLAB X IDE v6.25
- **Compiler**：MPLAB XC8 Compiler
- **Peripheral Devices**：：ILI9341, MPU6050, Button

## Pin Define

- ILI9341
  | Pin | Arduino Pin | Note |
  |-------|-------|-------|
  | MISO | - | - |
  | LED | 3.3v | - |
  | SCK | 13 (PB5) | 5v->3.3 |
  | MOSI | 11 (PB3) | 5v->3.3 |
  | D/C | 7 (PD7) | 5v->3.3 |
  | RESET | 6 (PD6) | 5v->3.3 |
  | CS | 10 (PB2) | 5v->3.3 |
  | GND | GND | - |
  | VCC | 3.3v | - |

- MPU6050
  | Pin | Arduino Pin | Note |
  |-------|-------|-------|
  | VCC | 5v | - |
  | GND | GND | - |
  | SCL | A5 (PC5) | pull-up |
  | SDA | A4 (PC4) | pull-up |

- Button
  | Pin | Arduino Pin | Note |
  |-------|-------|-------|
  | Button 0 | 2 (PD2) | - |
  | Button 1 | 3 (PD3) | - |

## Get Started

- Download project
- Open **MPLAB X IDE v6.25**：File -> Open Project
- Build Project

## Flash Example Firmware

- Edit the `COMPORT` variable
- Double-click the `.bat` file to start flashing

```
@echo off

set COMPORT=COM9

avrdude -v -C avrdude.conf -c arduino -p atmega328p -P %COMPORT% -b 115200 -U flash:w:AVR_HAL_EXAMPLE.X.production.hex:i

pause
```

## Output

https://github.com/user-attachments/assets/20784d07-edfa-4a2e-9350-209cd57c453c
