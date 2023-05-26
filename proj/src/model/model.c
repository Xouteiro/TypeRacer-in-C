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
Sprite *letter_a;
Sprite *letter_b;
Sprite *letter_c;
Sprite *letter_d;
Sprite *letter_e;
Sprite *letter_f;
Sprite *letter_g;
Sprite *letter_h;
Sprite *letter_i;
Sprite *letter_j;
Sprite *letter_k;
Sprite *letter_l;
Sprite *letter_m;
Sprite *letter_n;
Sprite *letter_o;
Sprite *letter_p;
Sprite *letter_q;
Sprite *letter_r;  
Sprite *letter_s;
Sprite *letter_t;
Sprite *letter_u;
Sprite *letter_v;
Sprite *letter_w;
Sprite *letter_x;
Sprite *letter_y;
Sprite *letter_z;


int timer_interrupts = 0;

void (sprites_setup)() {
   typo_racer = sprite_create_xpm((xpm_map_t) typo_racer_xpm);
   play_button =  sprite_create_button(105, 40, DARKBLUE); 
   play = sprite_create_xpm((xpm_map_t) play_button_xpm);
   cursor = sprite_create_xpm((xpm_map_t) mouse_xpm);
   quit = sprite_create_xpm((xpm_map_t) exit_xpm);
   exit_button = sprite_create_button(105, 40, DARKBLUE);
   esc = sprite_create_xpm((xpm_map_t) esc_xpm);
    letter_a = sprite_create_xpm((xpm_map_t) a_xpm);
    letter_b = sprite_create_xpm((xpm_map_t) b_xpm);
    letter_c = sprite_create_xpm((xpm_map_t) c_xpm);
    letter_d = sprite_create_xpm((xpm_map_t) d_xpm);
    letter_e = sprite_create_xpm((xpm_map_t) e_xpm);
    letter_f = sprite_create_xpm((xpm_map_t) f_xpm);
    letter_g = sprite_create_xpm((xpm_map_t) g_xpm);
    letter_h = sprite_create_xpm((xpm_map_t) h_xpm);
    letter_i = sprite_create_xpm((xpm_map_t) i_xpm);
    letter_j = sprite_create_xpm((xpm_map_t) j_xpm);
    letter_k = sprite_create_xpm((xpm_map_t) k_xpm);
    letter_l = sprite_create_xpm((xpm_map_t) l_xpm);   
    letter_m = sprite_create_xpm((xpm_map_t) m_xpm);
    letter_n = sprite_create_xpm((xpm_map_t) n_xpm);
    letter_o = sprite_create_xpm((xpm_map_t) o_xpm);
    letter_p = sprite_create_xpm((xpm_map_t) p_xpm);
    letter_q = sprite_create_xpm((xpm_map_t) q_xpm);
    letter_r = sprite_create_xpm((xpm_map_t) r_xpm);
    letter_s = sprite_create_xpm((xpm_map_t) s_xpm);
    letter_t = sprite_create_xpm((xpm_map_t) t_xpm);
    letter_u = sprite_create_xpm((xpm_map_t) u_xpm);
    letter_v = sprite_create_xpm((xpm_map_t) v_xpm);
    letter_w = sprite_create_xpm((xpm_map_t) w_xpm);
    letter_x = sprite_create_xpm((xpm_map_t) x_xpm);
    /*
    letter_y = sprite_create_xpm((xpm_map_t) y_xpm);
    letter_z = sprite_create_xpm((xpm_map_t) z_xpm);
    */
}

void (sprites_destroy)() {
    sprites_destroy(typo_racer);
    sprites_destroy(play_button);
    sprites_destroy(play);
    sprites_destroy(cursor);
    sprites_destroy(quit);
    sprites_destroy(exit_button);
    sprites_destroy(esc);
    sprites_destroy(letter_a);
    sprites_destroy(letter_b);
    sprites_destroy(letter_c);
    sprites_destroy(letter_d);
    sprites_destroy(letter_e);
    sprites_destroy(letter_f);
    sprites_destroy(letter_g);
    sprites_destroy(letter_h);
    sprites_destroy(letter_i);
    sprites_destroy(letter_j);
    sprites_destroy(letter_k);
    sprites_destroy(letter_l);
    sprites_destroy(letter_m);
    sprites_destroy(letter_n);
    sprites_destroy(letter_o);
    sprites_destroy(letter_p);
    sprites_destroy(letter_q);
    sprites_destroy(letter_r);
    sprites_destroy(letter_s);
    sprites_destroy(letter_t);
    sprites_destroy(letter_u);
    sprites_destroy(letter_v);
    sprites_destroy(letter_w);
    sprites_destroy(letter_x);
    sprites_destroy(letter_y);
    sprites_destroy(letter_z);
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
            break;
        case GAME:
            //gameControls(scancode);
            if(scancode == BREAK_ESC) menuState = START;
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
            //create_game(&game);
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
