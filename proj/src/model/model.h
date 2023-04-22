#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/keyboard_mouse/KBC.h"
#include "controller/Keyboard_mouse/mouse.h"
#include "controller/video/graphics.h"
#include "view/view.h"

typedef enum {
    RUNNING,
    OVER,
} SystemState;

typedef enum {
    START,
    GAME,
    END
} MenuState;

void update_timer_state();
void update_keyboard_state();
void update_mouse_state();
void update_buttons_state();
void setup_sprites();
void destroy_sprites();

#endif
