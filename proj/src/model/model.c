#include "model.h"

extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;

Sprite *typo_racer;
Sprite *play_button;
Sprite *play;
Sprite *cursor;
Sprite *quit;
Sprite *exit_button;
Sprite *esc;


void (sprites_setup)() {
   typo_racer = sprite_create_xpm((xpm_map_t) typo_racer_xpm);
   play_button =  sprite_create_button(105, 40, DARKBLUE); 
   play = sprite_create_xpm((xpm_map_t) play_button_xpm);
   cursor = sprite_create_xpm((xpm_map_t) mouse_xpm);
   quit = sprite_create_xpm((xpm_map_t) exit_xpm);
   exit_button = sprite_create_button(105, 40, DARKBLUE);
   esc = sprite_create_xpm((xpm_map_t) esc_xpm);
}

void (sprites_destroy)() {
    sprites_destroy(typo_racer);
    sprites_destroy(play_button);
    sprites_destroy(play);
    sprites_destroy(cursor);
    sprites_destroy(quit);
    sprites_destroy(exit_button);
    sprites_destroy(esc);
}

void (timer_update_state)() {
    view_swap_buffers();
}

void (keyboard_update_state)() {
    (kbc_ih)();
    switch (scancode) {
        case BREAK_ESC:
            menuState = START;
            break;
        case G_KEY:
            menuState = GAME;
            break;
        case E_KEY:
            menuState = END;
        default:
            break;
    }
    view_draw_new_frame();
}

void (mouse_update_state)() {
    (mouse_ih)();
    mouse_get_bytes();
    if (byte_index == 3) {
        mouse_get_info();
        buttons_update_state();
        view_draw_new_frame();
        byte_index = 0;
    }
}

void (buttons_update_state)() {
    if (mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 && mouse_info.y < mode_info.YResolution/2 +40 ){
        play_button->pressed = 1;
        if (mouse_info.left_click) {
            menuState = GAME;
            view_draw_new_frame();
        }
    } else if(mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 + 50 && mouse_info.y < mode_info.YResolution/2 + 90 ){
        exit_button->pressed = 1;
        if (mouse_info.left_click) {
            systemState = OVER;
        }
    } else {
        play_button->pressed = 0;
        exit_button->pressed = 0;
    }
}
