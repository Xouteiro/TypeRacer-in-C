#ifndef GAME_H
#define GAME_H

#include "view/view.h"
#include "model/model.h"
#include "controller/rtc/rtc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Game {
  int pos_player;
  int misses_after_hit;
  int typo_overall_count;
  int wpm;
  int phrase_size;
  int elapsed_time;
  char* phrase;
  
} Game;

char get_letter_from_keyboard(int scancode);

void create_game(Game *game);

int game_controls(int scancode, Game* game);

int get_random_phrase();


#endif
