@echo off

set COMPORT=COM9

avrdude -v -C avrdude.conf -c arduino -p atmega328p -P %COMPORT% -b 115200 -U flash:w:AVR_HAL_EXAMPLE.X.production.hex:i

pause