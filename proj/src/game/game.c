#include "game.h"

static char phrases[3000];



void create_game(Game *game){
    char * text = get_random_phrase("/home/lcom/labs/g3/proj/src/xpm/phrases.txt");
    game->phrase = text;
    game->phrase_size = strlen(text);
    return;
}

void game_controls(int scancode){
return;
}

char* get_random_phrase(char* file){
    FILE *infile;
    if((infile = fopen(file,"r"))== NULL){
        perror("cannot open file");
        return NULL;
    }
    int r = rand() % 10;
    size_t string_size = 0;
    char* string = NULL;
    int i = 0;
    while(getline(&string, &string_size, infile)> 0){
        if(i == r){
            for (size_t j = 0;j<string_size;j++){
                if(string[j]=='\n'){
                    phrases[j] = '\0';
                    break;
                }
                phrases[j] = string[j];
            }
            break;
        }
        i++;
    }
    fclose(infile);
    return phrases;

}


