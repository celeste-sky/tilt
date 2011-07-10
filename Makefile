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
SRCS:= gamestate.c \
       lcd.c \
       main.c \
       timer.c \
	   usart.c

# Hex program which is the final output
OUTPUT:= tilt.hex

# Folder in which to put generated files
GEN:=gen

# Object compilation rule
OBJS:=$(patsubst %.c,$(GEN)/%.o,$(SRCS))
$(OBJS): $$(patsubst $(GEN)/%.o,%.c,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# .c dependency generation
DEPS:=$(patsubst %.c,$(GEN)/%.d,$(SRCS))
$(DEPS): $$(patsubst $(GEN)/%.d,%.c,$$@)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CC) $(CFLAGS) $(INCLUDES) -MM -MT $(<:%.c=$(GEN)/%.o) -MF $@ $<
deps: $(DEPS)
include $(DEPS)

# Elf compilation rule
ELF:=$(GEN)/$(OUTPUT:.hex=.elf)
$(ELF): $(OBJS)
	@if test ! -e $(dir $@); then mkdir -p $(dir $@); fi
	$(CC) $(LDFLAGS) -o $@ $^

$(OUTPUT): $(ELF)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

all: $(OUTPUT)

# Program the widget!
write: $(OUTPUT)
	sudo avrdude -c $(PROGRAMMER) -p $(AVRDUDE_PART) -U flash:w:$(OUTPUT)

clean:
	rm -rf $(GEN)
	rm -f $(OUTPUT)

debugvar:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "DEPS: $(DEPS)"
	@echo "ELF: $(ELF)"

