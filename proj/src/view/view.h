#ifndef _LCOM_MENU_H_
#define _LCOM_MENU_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/video/graphics.h"
#include "controller/keyboard_mouse/mouse.h"
#include "model/model.h"
#include "model/sprite.h"
#include "model/xpm/typo_button_test.xpm"

void draw_new_frame();
void draw_initial_menu();
void draw_game_menu();
void draw_finish_menu();
void draw_mouse();
void swap_buffers();
int draw_sprite_xpm(Sprite *sprite, int x, int y);
int draw_sprite_button(Sprite *sprite, int x, int y);
int set_frame_buffers(uint16_t mode);

#endif
