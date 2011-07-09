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
#include <avr/interrupt.h>

#include "usart.h"
#include "lcd.h"
#include "timer.h"

int main() {
    // Change system clock from default 1Mhz to maximum of 8
    CLKPR = (1<<CLKPCE);  // Unlock clock prescale changes
    CLKPR = 0; // Div = 1 -> Run at internal osc speed of 8Mhz

    sei(); // enable interrupts, for timer.

    // Start system timer
    init_timer();

    // Delay a bit, to avoid resetting the LCD to b115200
    uint32_t i;
    for (i=0; i<1000000; ++i) asm volatile ("nop");

    init_usart0(BAUD_115200);

    /* Set up lcd */
    lcd_clr();
    lcd_bl_duty(0);

    lcd_coord(46, 12);
    usart_write("Hello!", 6);

    DDRD = 0x1; // enable output on D0

    uint8_t x = 0;
    while (1) {
        if (time_ms() & 0x400 ) {
            PORTD = 0x1;
        } else {
            PORTD = 0;
        }

        x++;
        x = x & 0x7f; // = %128
        lcd_circ(x, 32, 4, 1);
        lcd_line(x-4, 28, x-4, 36, 0);

        for (i=0; i<25000; ++i) asm volatile ("nop");
    }

    return 0;
}

