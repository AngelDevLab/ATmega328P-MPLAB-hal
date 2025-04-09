
# ATmega328P-MPLAB-hal

A basic **Hardware Abstraction Layer (HAL)** and example application

## Development Environment

- **MCU**：Arduino Uno board（ATmega328P）
- **IDE**：MPLAB X IDE v6.25
- **Compiler**：MPLAB XC8 Compiler
- **Peripheral Devices**：：ILI9341, MPU6050, Button

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

https://github.com/user-attachments/assets/80eb0d03-c4f9-46f9-b65a-c92284250dff

