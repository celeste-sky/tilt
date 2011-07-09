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

#include "usart.h"

int main() {
    // Change system clock from default 1Mhz to maximum of 8
    CLKPR = (1<<CLKPCE);  // Unlock clock prescale changes
    CLKPR = 0; // Div = 1 -> Run at internal osc speed of 8Mhz

    // Set D0 as output for blinking
    DDRD = 0x1;
    PORTD = 0;

    // Delay a bit, to avoid resetting the LCD to b115200
    uint32_t i;
    for (i=0; i<1000000; ++i) asm volatile ("nop");

    init_usart0(BAUD_115200);

    /* clear screen */
    usart0_tx('|');
    usart0_tx('\0');

    while (1) {
        usart_write("Hello! ", 7);
		PORTD = 0x1;
        for (i=0; i<400000; ++i) asm volatile ("nop");

		PORTD = 0x0;
        for (i=0; i<400000; ++i) asm volatile ("nop");
    }

    return 0;
}

