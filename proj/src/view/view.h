#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/video/graphics.h"
#include "controller/keyboard_mouse/mouse.h"
#include "model/model.h"
#include "model/sprite.h"
#include "game/game.h"

void (view_draw_new_frame)();
void (view_draw_initial_menu)();
void (view_draw_game_menu)();
void (view_draw_finish_menu)();
void (view_draw_mouse)();
void (view_swap_buffers)();
int (view_draw_sprite_xpm)(Sprite *sprite, int x, int y);
int (view_draw_sprite_button)(Sprite *sprite, int x, int y);
int (view_set_frame_buffers)(uint16_t mode);
int (phrase_writer)(char* word, int y_line);
int (wpm_writer)(int wpm);
int (accuracy_writer)(int acc);
int (is_lower)(char letter);
int (is_upper)(char letter);
int (is_number)(char letter);

#endif
