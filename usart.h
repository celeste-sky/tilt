/******************************************************************************
 * usart.h
 * Copyright 2011 Iain Peet
 *
 * Provides functions for controlling the USART peripheral
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

#ifndef USART_H_
#define USART_H_

#include <stdint.h>
#include <avr/io.h>

/* Baud rate generator prescales with 8Mhz system clock.
 * These are approximately equal to the baud periods, but not quite; 
 * They are twiddled for the inaccuracy in the sytem clock */
#define BAUD_9600 108


/* Initialize the USART 
 * @param baud The baud prescale appropriate for the desired baudrate. */
void init_usart0(uint8_t baud_prescale);

/* Send a byte.  Block if a transmit is in progress */
void usart0_tx(uint8_t byte);

/* Return nonzero if transmit buffer is empty */
unsigned usart0_tx_ready();

/* Generate a signal with the baud resulting from the given prescale.
 * Useful for calibrating with scope */
void usart0_cal(uint8_t baud_prescale);

/* Write the contents of a buffer to the usart.
 * This blocks until the last byte is in the TX buffer */
void usart_write(uint8_t *buf, uint16_t len);

#endif //USART_H_
