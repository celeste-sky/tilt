/******************************************************************************
 * main.c
 * Copyright 2011 Iain Peet
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#include <avr/io.h>

int main() {
    // Set D0, D1 as outputs
    DDRD = 0x3;
    PORTD = 0;

    uint32_t i;
    while (1) {
		PORTD = 0x1;
        for (i=0; i<50000; ++i) asm volatile ("nop");

		PORTD = 0x2;
        for (i=0; i<50000; ++i) asm volatile ("nop");
    }

    return 0;
}

