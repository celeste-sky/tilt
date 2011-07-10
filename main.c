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

#include "gamestate.h"
#include "lcd.h"
#include "timer.h"
#include "usart.h"

int main() {
    // Change system clock from default 1Mhz to maximum of 8
    CLKPR = (1<<CLKPCE);  // Unlock clock prescale changes
    CLKPR = 0; // Div = 1 -> Run at internal osc speed of 8Mhz

    sei(); // enable interrupts, for timer.

    // Start system timer
    init_timer();

    // Delay a bit, to avoid resetting the LCD to b115200
    while (time_ms() < 2000);

    init_usart0(BAUD_19200);

    /* Set up lcd */
    lcd_clr();
    lcd_bl_duty(0);

    usart_write("Hello!", 6);

    DDRD = 0x1; // enable output on D0

    uint32_t last_update = 0;
    while (1) {
        /* blink! */
        if (time_ms() & 0x400 ) {
            PORTD = 0x1;
        } else {
            PORTD = 0;
        }

        if (time_ms() - last_update < 100) continue;
        last_update = time_ms();

        update_game();
    }

    return 0;
}

