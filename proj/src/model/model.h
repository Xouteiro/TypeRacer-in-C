#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "controller/keyboard_mouse/KBC.h"
#include "controller/Keyboard_mouse/mouse.h"
#include "controller/video/graphics.h"
#include "view/view.h"
#include "xpm/typo_racer.xpm"
#include "xpm/play_button.xpm"
#include "xpm/mouse.xpm"
#include "xpm/exit_button.xpm"
#include "xpm/esc_menu.xpm"


typedef enum {
    RUNNING,
    OVER,
} SystemState;

typedef enum {
    START,
    GAME,
    END
} MenuState;

void (timer_update_state)();
void (keyboard_update_state)();
void (mouse_update_state)();
void (buttons_update_state)();
void (sprites_setup)();
void (sprites_destroy)();

#endif
