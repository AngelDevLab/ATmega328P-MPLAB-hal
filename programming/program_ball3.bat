@echo off

set COMPORT=COM9

avrdude -v -C avrdude.conf -c arduino -p atmega328p -P %COMPORT% -b 115200 -U flash:w:_ball3.hex:i

pause