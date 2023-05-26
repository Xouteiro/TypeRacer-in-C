#include "game.h"

char *sentence;


void create_game(Game *game){
    get_random_phrase();    
    game->phrase = sentence;
    game->phrase_size = strlen(sentence) - 1;
    return;
}

void game_controls(int scancode){
return;
}

int get_random_phrase(){
    FILE *textfile;
    char line[1000];
     
    textfile = fopen("/home/lcom/labs/g3/proj/src/xpm/phrases.txt", "r");
    if(textfile == NULL)
        return 1;
     
    while(fgets(line, 1000, textfile)){
        sentence = line;
    }
     
    fclose(textfile);
    return 0;
}


