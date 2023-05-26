#include "view.h"

uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern MenuState menuState;
Game *game;


extern Sprite *typo_racer;
extern Sprite *play_button;
extern Sprite *play;
extern Sprite *cursor;
extern Sprite *quit;
extern Sprite *exit_button;
extern Sprite *esc;
extern Sprite *letter_a;
extern Sprite *letter_b;
extern Sprite *letter_c;
extern Sprite *letter_d;
extern Sprite *letter_e;
extern Sprite *letter_f;
extern Sprite *letter_g;
extern Sprite *letter_h;
extern Sprite *letter_i;
extern Sprite *letter_j;
extern Sprite *letter_k;
extern Sprite *letter_l;
extern Sprite *letter_m;
extern Sprite *letter_n;
extern Sprite *letter_o;
extern Sprite *letter_p;
extern Sprite *letter_q;
extern Sprite *letter_r;
extern Sprite *letter_s;
extern Sprite *letter_t;
extern Sprite *letter_u;
extern Sprite *letter_v;
extern Sprite *letter_w;
extern Sprite *letter_x;
extern Sprite *letter_y;
letter_




int (view_set_frame_buffers)(uint16_t mode) {
    if (graphics_set_frame_buffer(mode, &main_frame_buffer)) return 1;
    frame_buffer_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
    secondary_frame_buffer = (uint8_t *) malloc(frame_buffer_size);
    drawing_frame_buffer = secondary_frame_buffer;

    return 0;
}

void (view_swap_buffers)() {
    memcpy(main_frame_buffer, secondary_frame_buffer, frame_buffer_size);
}

void (view_draw_new_frame)() {
    switch (menuState) {
        case START:
            view_draw_initial_menu();
            break;
        case GAME:
            view_draw_game_menu();
            break;
        case END:
            view_draw_finish_menu();
            break;
    }
}

void (view_draw_initial_menu)() { 
    graphics_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, DARKBLUE, drawing_frame_buffer);
    view_draw_sprite_xpm(typo_racer, mode_info.XResolution/4 + 18, mode_info.YResolution/4);
    view_draw_sprite_button(play_button, mode_info.XResolution/2 - 65, mode_info.YResolution/2);
    view_draw_sprite_xpm(play, mode_info.XResolution/2 - 58 + 5, mode_info.YResolution/2 - 10);
    view_draw_sprite_button(exit_button, mode_info.XResolution/2 - 65, mode_info.YResolution/2 + 70);
    view_draw_sprite_xpm(quit, mode_info.XResolution/2 - 58 + 10, mode_info.YResolution/2 + 60);
   
    return;
}

void (view_draw_game_menu)() {
    graphics_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, DARKBLUE, drawing_frame_buffer);
    view_draw_sprite_xpm(esc, mode_info.XResolution - 365, mode_info.YResolution - 45);
    phrase_writer( "sdfghjkkjhgfdsdfghjklkjhgf" , 100);

    return;
} 

void (view_draw_finish_menu)() {
    graphics_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, BLUE, drawing_frame_buffer);
    return;
}

void (view_draw_mouse)() {
    view_draw_sprite_xpm(cursor, mouse_info.x, mouse_info.y);
}

int (view_draw_sprite_xpm)(Sprite *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t current_color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        current_color = sprite->colors[w + h*width];
        if (current_color == TRANSPARENT) continue;
        if (graphics_draw_pixel(x + w, y + h, current_color, drawing_frame_buffer)) return 1;
      }
    }
    return 0; 
}

int (view_draw_sprite_button)(Sprite *sprite, int x, int y) { 
    uint16_t height = sprite->height;
    uint16_t width = sprite->width;
    uint32_t color = sprite->pressed ? PRESSED : sprite->color;
    for (int h = 0 ; h < height ; h++) {
      for (int w = 0 ; w < width ; w++) {
        if (graphics_draw_pixel(x + w, y + h, color, drawing_frame_buffer)) return 1;
      }
    }
    return 0; 
}

int (phrase_writer)(char* word, int y_line){
    int x_pos =40;
    int safe_x = x_pos;
    size_t size = strlen(word);
    for(int i=0; i<(int)size; i++){
        if((safe_x >= mode_info.XResolution - 170 && *(word+i) == ' ') || safe_x >= mode_info.XResolution - 50){
            y_line += 30;
            x_pos = 15;
            safe_x = x_pos;
        }
        if( *(word+i) == '\0') break;
        switch( *(word+i) ){
            case 'a': case 'A':
                view_draw_sprite_xpm(letter_a, x_pos, y_line); break;
            case 'b': case 'B':
                view_draw_sprite_xpm(letter_b, x_pos, y_line); break;
            case 'c': case 'C':
                view_draw_sprite_xpm(letter_c, x_pos, y_line); break;
            case 'd': case 'D':
                view_draw_sprite_xpm(letter_d, x_pos, y_line); break;
            case 'e': case 'E':
                view_draw_sprite_xpm(letter_e, x_pos, y_line); break;
            case 'f': case 'F':
                view_draw_sprite_xpm(letter_f, x_pos, y_line); break;
            case 'g': case 'G':
                view_draw_sprite_xpm(letter_g, x_pos, y_line); break;
            case 'h': case 'H':
                view_draw_sprite_xpm(letter_h, x_pos, y_line); break;
            case 'i': case 'I':
                view_draw_sprite_xpm(letter_i, x_pos, y_line); break;
            case 'j': case 'J':
                view_draw_sprite_xpm(letter_j, x_pos, y_line); break;
            case 'k': case 'K':
                view_draw_sprite_xpm(letter_k, x_pos, y_line); break;
            case 'l': case 'L':
                view_draw_sprite_xpm(letter_l, x_pos, y_line); break;
            case 'm': case 'M':
                view_draw_sprite_xpm(letter_m, x_pos, y_line); break;
            case 'n': case 'N':
                view_draw_sprite_xpm(letter_n, x_pos, y_line); break;
            case 'o': case 'O':
                view_draw_sprite_xpm(letter_o, x_pos, y_line); break;
            case 'p': case 'P':
                view_draw_sprite_xpm(letter_p, x_pos, y_line); break;
            case 'q': case 'Q':
                view_draw_sprite_xpm(letter_q, x_pos, y_line); break;
            case 'r': case 'R':
                view_draw_sprite_xpm(letter_r, x_pos, y_line); break;
            case 's': case 'S':
                view_draw_sprite_xpm(letter_s, x_pos, y_line); break;
            case 't': case 'T':
                view_draw_sprite_xpm(letter_t, x_pos, y_line); break;
            case 'u': case 'U':
                view_draw_sprite_xpm(letter_u, x_pos, y_line); break;
            case 'v': case 'V':
                view_draw_sprite_xpm(letter_v, x_pos, y_line); break;
            case 'w': case 'W':
                view_draw_sprite_xpm(letter_w, x_pos, y_line); break;
            case 'x': case 'X':
                view_draw_sprite_xpm(letter_x, x_pos, y_line); break;
            case 'y': case 'Y':
                view_draw_sprite_xpm(letter_y, x_pos, y_line); break;
            case 'z': case 'Z':
                view_draw_sprite_xpm(letter_a, x_pos, y_line); break;
            case '.': case ',':
                view_draw_sprite_xpm(letter_a, x_pos, y_line); break;
            case ' ':
                x_pos+=10;
                safe_x += 15;
                break;
            default:
                return 1;
        }
        safe_x += 15;
      x_pos+=15;
    }

    return 0;
}

