#include "view.h"

uint8_t *main_frame_buffer;
uint8_t *secondary_frame_buffer;
uint8_t *drawing_frame_buffer;
uint32_t frame_buffer_size;
extern vbe_mode_info_t mode_info;
extern MouseInfo mouse_info;
extern MenuState menuState;

extern Sprite *typo_racer;
extern Sprite *play_button;
extern Sprite *play;
extern Sprite *cursor;
extern Sprite *quit;
extern Sprite *exit_button;
extern Sprite *esc;


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


