#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include "controller/video/graphics.h"

#define LETTERS_SPRITES     26     // 26 letters of the alphabet
#define OTHER_SPRITES       5     
#define MAX_SPRITES         (LETTERS_SPRITES + OTHER_SPRITES)

typedef struct {
    uint16_t height;
    uint16_t width;
    uint32_t *colors;
    uint32_t color;
    uint8_t pressed;
} Sprite; 

Sprite* (sprite_create_xpm)(xpm_map_t sprite);
Sprite* (sprite_create_button)(uint16_t width, uint16_t height, uint32_t color);
void (sprite_destroy)(Sprite *sprite);


#endif
