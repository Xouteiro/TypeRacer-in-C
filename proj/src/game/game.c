#include "game.h"

char *sentence;


void create_game(Game *game){
    get_random_phrase();    
    game->phrase = sentence;
    game->phrase_size = strlen(sentence) - 1;
    game->pos_player = 0;
    game->misses_after_hit = 0;
    game->typo_overall_count = 0;
    game->wpm = 0;
    return;
}



void game_controls(int scancode){
    return;
}

int get_random_phrase(){
    FILE *textfile;
    char line[1000];
    int random_line;
    int i = 0;

    random_line = rand() % 10;
     
    textfile = fopen("/home/lcom/labs/g3/proj/src/xpm/phrases.txt", "r");
    if(textfile == NULL) {
        printf("Cannot read file\n");
        return 1;
    }
     
    while(fgets(line, 1000, textfile)){
        if(i == random_line){
            sentence = line;
            return 0;
        }
        else
            i++;
    }
     
    fclose(textfile);
    return 0;
}


