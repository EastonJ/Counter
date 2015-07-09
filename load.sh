#!/usr/bin/sh
avr-gcc -mmcu=atmega328p -std=c11 -Wall -Os -o alm_clk.elf alm_clk.c twi/i2cmaster.S
avr-objcopy -j .text -j .data -O ihex alm_clk.elf alm_clk.hex
avrdude -p m328p -c arduino -P /dev/ttyACM0 -b 19200 -e -U flash:w:alm_clk.hex
