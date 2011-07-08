#  Makefile
#  Copyright 2011 Iain Peet
# 
#  This program is distributed under the of the GNU Lesser Public License. 
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>
.DEFAULT_GOAL=all
.SECONDEXPANSION:

# Overridable params
MCU?=atmega328p
PROGRAMMER?=usbtiny
AVRDUDE_PART?=m328p

# Compiler config
CC:=avr-gcc
CFLAGS:= -mmcu=$(MCU) -Os -Wall -Wextra
INCLUDES:=-I/usr/lib/avr/include
LDFLAGS:= $(CFLAGS)
OBJCOPY:=avr-objcopy

# List of sources to compile into hex
SRCS:= main.c

# Hex program which is the final output
OUTPUT:= tilt.hex

# Generate list of objects to compile from list of sources
OBJS:=$(patsubst %.c,%.o,$(SRCS))

# The name of the elf we will need to link
ELF:= $(OUTPUT:.hex=.elf)

# Object compilation rule
$(OBJS): $$(patsubst %.o,%.c,$$@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Elf compilation rule
$(ELF): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OUTPUT): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

all: $(OUTPUT)

# Program the widget!
write: $(OUTPUT)
	sudo avrdude -c $(PROGRAMMER) -p $(AVRDUDE_PART) -U flash:w:$(OUTPUT)

clean:
	rm -f $(OBJS)
	rm -f $(OUTPUT) $(ELF)

debugvar:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "ELF: $(ELF)"

