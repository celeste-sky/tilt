/******************************************************************************
 * lcd.c
 * Copyright 2011 Iain Peet
 *
 * Provides functions for manipulating a 128x64 serial grpahic LCD on usart0
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

#include <stdint.h>

#include "lcd.h"
#include "usart.h"

void lcd_clr() {
    usart0_tx('|');
    usart0_tx('\0');
}

void lcd_bl_duty(uint8_t duty) {
    usart0_tx('|');
    usart0_tx(0x2);
    usart0_tx(duty);
}

void lcd_pix(uint8_t x, uint8_t y, uint8_t is_set) {
    usart0_tx('|');
    usart0_tx(0x10);
    usart0_tx(x);
    usart0_tx(y);
    usart0_tx(is_set);
}

void lcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t is_set) {
    usart0_tx('|');
    usart0_tx(0xc);
    usart0_tx(x1);
    usart0_tx(y1);
    usart0_tx(x2);
    usart0_tx(y2);
    usart0_tx(is_set);
}

void lcd_circ(uint8_t x, uint8_t y, uint8_t r, uint8_t is_set) {
    usart0_tx('|');
    usart0_tx(0x3);
    usart0_tx(x);
    usart0_tx(y);
    usart0_tx(r);
    usart0_tx(is_set);
}

void lcd_clr_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    usart0_tx('|');
    usart0_tx(0x5);
    usart0_tx(x1);
    usart0_tx(y1);
    usart0_tx(x2);
    usart0_tx(y2);
}

void lcd_coord(uint8_t x, uint8_t y) {
    usart0_tx('|');
    usart0_tx(0x18);
    usart0_tx(x);
    usart0_tx('|');
    usart0_tx(0x19);
    usart0_tx(y);
}
