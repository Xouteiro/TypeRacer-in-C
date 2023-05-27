#include "model.h"

extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
Game game;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;   

Sprite *typo_racer, *play_button, *play, *cursor, *quit, *exit_button, *esc, *dot, *comma;
Sprite *letters[LETTERS];
Sprite *numbers[NUMBERS];

int timer_interrupts = 0;

void (sprites_setup)() {
    typo_racer = sprite_create_xpm((xpm_map_t) typo_racer_xpm);
    play_button = sprite_create_button(105, 40, DARKBLUE); 
    play = sprite_create_xpm((xpm_map_t) play_button_xpm);
    cursor = sprite_create_xpm((xpm_map_t) mouse_xpm);
    quit = sprite_create_xpm((xpm_map_t) exit_xpm);
    exit_button = sprite_create_button(105, 40, DARKBLUE);
    esc = sprite_create_xpm((xpm_map_t) esc_xpm);
    letters[0] = sprite_create_xpm((xpm_map_t) xpm_a);
    letters[1] = sprite_create_xpm((xpm_map_t) xpm_b);
    letters[2] = sprite_create_xpm((xpm_map_t) xpm_c);
    letters[3] = sprite_create_xpm((xpm_map_t) xpm_d);
    letters[4] = sprite_create_xpm((xpm_map_t) xpm_e);
    letters[5] = sprite_create_xpm((xpm_map_t) xpm_f);
    letters[6] = sprite_create_xpm((xpm_map_t) xpm_g);
    letters[7] = sprite_create_xpm((xpm_map_t) xpm_h);
    letters[8] = sprite_create_xpm((xpm_map_t) xpm_i);
    letters[9] = sprite_create_xpm((xpm_map_t) xpm_j);
    letters[10] = sprite_create_xpm((xpm_map_t) xpm_k);
    letters[11] = sprite_create_xpm((xpm_map_t) xpm_l);   
    letters[12] = sprite_create_xpm((xpm_map_t) xpm_m);
    letters[13] = sprite_create_xpm((xpm_map_t) xpm_n);
    letters[14] = sprite_create_xpm((xpm_map_t) xpm_o);
    letters[15] = sprite_create_xpm((xpm_map_t) xpm_p);
    letters[16] = sprite_create_xpm((xpm_map_t) xpm_q);
    letters[17] = sprite_create_xpm((xpm_map_t) xpm_r);
    letters[18] = sprite_create_xpm((xpm_map_t) xpm_s);
    letters[19] = sprite_create_xpm((xpm_map_t) xpm_t);
    letters[20] = sprite_create_xpm((xpm_map_t) xpm_u);
    letters[21] = sprite_create_xpm((xpm_map_t) xpm_v);
    letters[22] = sprite_create_xpm((xpm_map_t) xpm_w);
    letters[23] = sprite_create_xpm((xpm_map_t) xpm_x);
    letters[24] = sprite_create_xpm((xpm_map_t) xpm_y);
    letters[25] = sprite_create_xpm((xpm_map_t) xpm_z);
    numbers[0] = sprite_create_xpm((xpm_map_t) xpm_o);
    numbers[1] = sprite_create_xpm((xpm_map_t) xpm_1);
    numbers[2] = sprite_create_xpm((xpm_map_t) xpm_2);
    numbers[3] = sprite_create_xpm((xpm_map_t) xpm_3);
    numbers[4] = sprite_create_xpm((xpm_map_t) xpm_4);
    numbers[5] = sprite_create_xpm((xpm_map_t) xpm_5);
    numbers[6] = sprite_create_xpm((xpm_map_t) xpm_6);
    numbers[7] = sprite_create_xpm((xpm_map_t) xpm_7);
    numbers[8] = sprite_create_xpm((xpm_map_t) xpm_8);
    numbers[9] = sprite_create_xpm((xpm_map_t) xpm_9);
    dot = sprite_create_xpm((xpm_map_t) xpm_dot);
    comma = sprite_create_xpm((xpm_map_t) xpm_comma);
}

void (sprites_destroy)() {
    sprite_destroy(typo_racer);
    sprite_destroy(play_button);
    sprite_destroy(play);
    sprite_destroy(cursor);
    sprite_destroy(quit);
    sprite_destroy(exit_button);
    sprite_destroy(esc);
    for(int i = 0 ; i < 26 ; i++){
        sprite_destroy(letters[i]);
    }
    for(int i = 0 ; i < 10 ; i++){
        sprite_destroy(numbers[i]);
    }
    sprite_destroy(dot);
    sprite_destroy(comma);
}

void (timer_update_state)() {
    view_draw_new_frame();
    view_draw_mouse();
    view_swap_buffers();
    timer_interrupts++;
}

void (keyboard_update_state)() {
    kbc_ih();
    switch (menuState) {
        case START:
            if(scancode == BREAK_ESC) systemState = OVER;
            if(scancode == KEY_1){
                menuState = GAME;
                create_game(&game);

            } 
            break;
        case GAME:
            if(scancode == BREAK_ESC) menuState = START;
            if(game_controls(scancode, &game) == 0)  menuState = END;
            break;
            
        case END:
            if(scancode == BREAK_ESC) systemState = OVER;
        default:
            break;
    }
}

void (mouse_update_state)() {
    (mouse_ih)();
    mouse_get_bytes();
    if (byte_index == 3) {
        byte_index = 0;
        mouse_get_info();
        if(menuState == START){
            menu_buttons_update();
        }
    }
}
void update_rtc_state() {
    if (timer_interrupts % 60 == 0) rtc_update_time_info();
}

void (menu_buttons_update)() {
    if (mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 && mouse_info.y < mode_info.YResolution/2 +40 ){
        play_button->pressed = 1;
        if (mouse_info.left_click) {
            menuState = GAME;
            create_game(&game);
        }
    } else if(mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 + 50 && mouse_info.y < mode_info.YResolution/2 + 100 ){
        exit_button->pressed = 1;
        if (mouse_info.left_click) {
            systemState = OVER;
        }
    } else {
        play_button->pressed = 0;
        exit_button->pressed = 0;
    }
}
