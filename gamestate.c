/******************************************************************************
 * gamestate.c
 * Copyright 2011 Iain Peet
 *
 * The actual game logic.  Draws the ball, implements physics, etc.
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

#include "gamestate.h"
#include "lcd.h"
#include "timer.h"

#define WORLD_WIDTH 128 
#define WORLD_HEIGHT 56

struct game_state {
    int16_t x_pos;
    int16_t y_pos;
    int8_t x_vel;
    int8_t y_vel;
} _cur_state = {10, 10, 2, 2};

void _do_physics(struct game_state *new_state);
void _do_redraw(struct game_state *new_state);

void update_game() {
    struct game_state new_state;
    
    _do_physics(&new_state);
    _do_redraw(&new_state);

    _cur_state = new_state;
}

void _do_physics(struct game_state *new_state) {
    new_state->x_pos = _cur_state.x_pos + _cur_state.x_vel;
    new_state->x_vel = _cur_state.x_vel;
    // If we hit the edge, bounce
    if (new_state->x_pos >= WORLD_WIDTH - 1) {
        new_state->x_vel = -new_state->x_vel;
        new_state->x_pos = 2*(WORLD_WIDTH - 2) - new_state->x_pos;
    }
    if (new_state->x_pos < 1) {
        new_state->x_vel = -new_state->x_vel;
        new_state->x_pos = 1 -new_state->x_pos;
    }

    new_state->y_pos = _cur_state.y_pos + _cur_state.y_vel;
    new_state->y_vel = _cur_state.y_vel;
    if (new_state->y_pos >= WORLD_HEIGHT - 1) {
        new_state->y_vel = -new_state->y_vel;
        new_state->y_pos = 2*(WORLD_HEIGHT - 2) - new_state->y_pos;
    }
    if (new_state->y_pos < 1) {
        new_state->y_vel = -new_state->y_vel;
        new_state->y_pos = 1 -new_state->y_pos;
    }
}

void _do_redraw(struct game_state *new_state) {
    lcd_clr_rect(_cur_state.x_pos-1, _cur_state.y_pos-1,
                 _cur_state.x_pos+1,_cur_state.y_pos+1); 
    lcd_rect(new_state->x_pos-1, new_state->y_pos-1,
             new_state->x_pos+1, new_state->y_pos+1, 1); 
}

