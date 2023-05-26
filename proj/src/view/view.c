#include "view.h"

uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern MenuState menuState;
extern Game game;


extern Sprite *typo_racer;
extern Sprite *play_button;
extern Sprite *play;
extern Sprite *cursor;
extern Sprite *quit;
extern Sprite *exit_button;
extern Sprite *esc;
extern Sprite *a;
extern Sprite *b;
extern Sprite *c;
extern Sprite *d;
extern Sprite *e;
extern Sprite *f;
extern Sprite *g;
extern Sprite *h;
extern Sprite *letter_i;
extern Sprite *letter_j;
extern Sprite *k;
extern Sprite *l;
extern Sprite *m;
extern Sprite *n;
extern Sprite *o;
extern Sprite *p;
extern Sprite *q;
extern Sprite *r;
extern Sprite *s;
extern Sprite *t;
extern Sprite *u;
extern Sprite *v;
extern Sprite *w;
extern Sprite *x;
extern Sprite *y;





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
    phrase_writer( game.phrase , 100);

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
                view_draw_sprite_xpm(a, x_pos, y_line); break;
            case 'b': case 'B':
                view_draw_sprite_xpm(b, x_pos, y_line); break;
            case 'c': case 'C':
                view_draw_sprite_xpm(c, x_pos, y_line); break;
            case 'd': case 'D':
                view_draw_sprite_xpm(d, x_pos, y_line); break;
            case 'e': case 'E':
                view_draw_sprite_xpm(e, x_pos, y_line); break;
            case 'f': case 'F':
                view_draw_sprite_xpm(f, x_pos, y_line); break;
            case 'g': case 'G':
                view_draw_sprite_xpm(g, x_pos, y_line); break;
            case 'h': case 'H':
                view_draw_sprite_xpm(h, x_pos, y_line); break;
            case 'i': case 'I':
                view_draw_sprite_xpm(letter_i, x_pos, y_line); break;
            case 'j': case 'J':
                view_draw_sprite_xpm(letter_j, x_pos, y_line); break;
            case 'k': case 'K':
                view_draw_sprite_xpm(k, x_pos, y_line); break;
            case 'l': case 'L':
                view_draw_sprite_xpm(l, x_pos, y_line); break;
            case 'm': case 'M':
                view_draw_sprite_xpm(m, x_pos, y_line); break;
            case 'n': case 'N':
                view_draw_sprite_xpm(n, x_pos, y_line); break;
            case 'o': case 'O':
                view_draw_sprite_xpm(o, x_pos, y_line); break;
            case 'p': case 'P':
                view_draw_sprite_xpm(p, x_pos, y_line); break;
            case 'q': case 'Q':
                view_draw_sprite_xpm(q, x_pos, y_line); break;
            case 'r': case 'R':
                view_draw_sprite_xpm(r, x_pos, y_line); break;
            case 's': case 'S':
                view_draw_sprite_xpm(s, x_pos, y_line); break;
            case 't': case 'T':
                view_draw_sprite_xpm(t, x_pos, y_line); break;
            case 'u': case 'U':
                view_draw_sprite_xpm(u, x_pos, y_line); break;
            case 'v': case 'V':
                view_draw_sprite_xpm(v, x_pos, y_line); break;
            case 'w': case 'W':
                view_draw_sprite_xpm(w, x_pos, y_line); break;
            case 'x': case 'X':
                view_draw_sprite_xpm(x, x_pos, y_line); break;
            case 'y': case 'Y':
                view_draw_sprite_xpm(a, x_pos, y_line); break;
            case 'z': case 'Z':
                view_draw_sprite_xpm(a, x_pos, y_line); break;
            case '.': case ',': case ' ':
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

