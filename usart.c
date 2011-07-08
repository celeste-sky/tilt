/******************************************************************************
 * usart.c
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

#include "usart.h"

void init_usart0(uint8_t baud_prescale) {
    UBRR0H = 0;
    UBRR0L = baud_prescale; 
    UCSR0A = (1<<U2X0); // double speed for double xmit baud accuracy
    UCSR0B = (1<<TXEN0); // Enable transmitter
    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); // 8 bit, 1 stop bit, no parity
}

void usart0_tx(uint8_t byte) {
    // Wait for empty tx buf        
    while (!(UCSR0A & (1<<UDRE0))); 
    // Write to tx buf
    UDR0 = byte;
}

unsigned usart0_tx_ready() {
    return UCSR0A & (1<<UDRE0);
}

void usart0_cal(uint8_t baud_prescale) {
    init_usart0(baud_prescale);
    while (1) {
        // Continually ransmitting 0x55 with 8N1 produces a square wave
        usart0_tx(0x55);
    }
}

void usart_write(uint8_t *buf, uint16_t len) {
    uint16_t i;
    for (i=0; i<len; ++i) {
        usart0_tx(buf[i]);    
    }
}

