/******************************************************************************
 * lcd.h
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

#ifndef LCD_H_
#define LCD_H_

// Clear the LCD
void lcd_clr();

// Set the backlight duty cycle, [0-100]%
void lcd_bl_duty(uint8_t duty);

// Set/clear a given pixel
void lcd_pix(uint8_t x, uint8_t y, uint8_t is_set);

// Set/clear all pixels along a line
void lcd_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t is_set);

// Set/clear lines of a rectangle
void lcd_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t is_set);

// Draw a circle
void lcd_circ(uint8_t x, uint8_t y, uint8_t r, uint8_t is_set);

// Clear the entire area of a rectangle
void lcd_clr_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

// Set the upper left coord for text drawing
void lcd_coord(uint8_t x, uint8_t y);

#endif //LCD_H_
