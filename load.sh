#!/usr/bin/sh
avr-gcc -mmcu=atmega328p -Wall -Os -o counter.elf counter.c
avr-objcopy -j .text -j .data -O ihex counter.elf counter.hex
avrdude -p m328p -c arduino -P /dev/ttyACM0 -b 19200 -e -U flash:w:counter.hex
