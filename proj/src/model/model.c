#include "model.h"

extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
Game game;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;   

Sprite *typo_racer;
Sprite *play_button;
Sprite *play;
Sprite *cursor;
Sprite *quit;
Sprite *exit_button;
Sprite *esc;
Sprite *a;
Sprite *b;
Sprite *c;
Sprite *d;
Sprite *e;
Sprite *f;
Sprite *g;
Sprite *h;
Sprite *letter_i;
Sprite *letter_j;
Sprite *k;
Sprite *l;
Sprite *m;
Sprite *n;
Sprite *o;
Sprite *p;
Sprite *q;
Sprite *r;  
Sprite *s;
Sprite *t;
Sprite *u;
Sprite *v;
Sprite *w;
Sprite *x;
Sprite *y;
Sprite *z;


int timer_interrupts = 0;

void (sprites_setup)() {
   typo_racer = sprite_create_xpm((xpm_map_t) typo_racer_xpm);
   play_button =  sprite_create_button(105, 40, DARKBLUE); 
   play = sprite_create_xpm((xpm_map_t) play_button_xpm);
   cursor = sprite_create_xpm((xpm_map_t) mouse_xpm);
   quit = sprite_create_xpm((xpm_map_t) exit_xpm);
   exit_button = sprite_create_button(105, 40, DARKBLUE);
   esc = sprite_create_xpm((xpm_map_t) esc_xpm);
    a = sprite_create_xpm((xpm_map_t) a_xpm);
    b = sprite_create_xpm((xpm_map_t) b_xpm);
    c = sprite_create_xpm((xpm_map_t) c_xpm);
    d = sprite_create_xpm((xpm_map_t) d_xpm);
    e = sprite_create_xpm((xpm_map_t) e_xpm);
    f = sprite_create_xpm((xpm_map_t) f_xpm);
    g = sprite_create_xpm((xpm_map_t) g_xpm);
    h = sprite_create_xpm((xpm_map_t) h_xpm);
    letter_i = sprite_create_xpm((xpm_map_t) i_xpm);
    letter_j = sprite_create_xpm((xpm_map_t) j_xpm);
    k = sprite_create_xpm((xpm_map_t) k_xpm);
    l = sprite_create_xpm((xpm_map_t) l_xpm);   
    m = sprite_create_xpm((xpm_map_t) m_xpm);
    n = sprite_create_xpm((xpm_map_t) n_xpm);
    o = sprite_create_xpm((xpm_map_t) o_xpm);
    p = sprite_create_xpm((xpm_map_t) p_xpm);
    q = sprite_create_xpm((xpm_map_t) q_xpm);
    r = sprite_create_xpm((xpm_map_t) r_xpm);
    s = sprite_create_xpm((xpm_map_t) s_xpm);
    t = sprite_create_xpm((xpm_map_t) t_xpm);
    u = sprite_create_xpm((xpm_map_t) u_xpm);
    v = sprite_create_xpm((xpm_map_t) v_xpm);
    w = sprite_create_xpm((xpm_map_t) w_xpm);
    x = sprite_create_xpm((xpm_map_t) x_xpm);
    /*
    y = sprite_create_xpm((xpm_map_t) y_xpm);
    z = sprite_create_xpm((xpm_map_t) z_xpm);
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
    sprites_destroy(a);
    sprites_destroy(b);
    sprites_destroy(c);
    sprites_destroy(d);
    sprites_destroy(e);
    sprites_destroy(f);
    sprites_destroy(g);
    sprites_destroy(h);
    sprites_destroy(letter_i);
    sprites_destroy(letter_j);
    sprites_destroy(k);
    sprites_destroy(l);
    sprites_destroy(m);
    sprites_destroy(n);
    sprites_destroy(o);
    sprites_destroy(p);
    sprites_destroy(q);
    sprites_destroy(r);
    sprites_destroy(s);
    sprites_destroy(t);
    sprites_destroy(u);
    sprites_destroy(v);
    sprites_destroy(w);
    sprites_destroy(x);
    sprites_destroy(y);
    sprites_destroy(z);
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
