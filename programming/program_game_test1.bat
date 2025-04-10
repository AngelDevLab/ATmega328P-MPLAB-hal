@echo off

set COMPORT=COM9

avrdude -v -C avrdude.conf -c arduino -p atmega328p -P %COMPORT% -b 115200 -U flash:w:_game_test1.hex:i

pause