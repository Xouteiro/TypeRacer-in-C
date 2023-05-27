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

char get_letter_from_keyboard(int scancode){
    if(scancode == A_KEY) return 'a';
    if(scancode == B_KEY) return 'b';
    if(scancode == C_KEY) return 'c';
    if(scancode == D_KEY) return 'd';
    if(scancode == E_KEY) return 'e';
    if(scancode == F_KEY) return 'f';
    if(scancode == G_KEY) return 'g';
    if(scancode == H_KEY) return 'h';
    if(scancode == I_KEY) return 'i';
    if(scancode == J_KEY) return 'j';
    if(scancode == K_KEY) return 'k';
    if(scancode == L_KEY) return 'l';
    if(scancode == M_KEY) return 'm';
    if(scancode == N_KEY) return 'n';
    if(scancode == O_KEY) return 'o';
    if(scancode == P_KEY) return 'p';
    if(scancode == Q_KEY) return 'q';
    if(scancode == R_KEY) return 'r';
    if(scancode == S_KEY) return 's';
    if(scancode == T_KEY) return 't';
    if(scancode == U_KEY) return 'u';
    if(scancode == V_KEY) return 'v';
    if(scancode == W_KEY) return 'w';
    if(scancode == X_KEY) return 'x';
    if(scancode == Y_KEY) return 'y';
    if(scancode == Z_KEY) return 'z';
    if(scancode == COMMA_KEY) return ',';
    if(scancode == DOT_KEY) return '.';
    if(scancode == SPACE_KEY) return ' ';
    else {
      return '\0';
    }

}



int game_controls(int scancode, Game* game){
    char letter = get_letter_from_keyboard(scancode);
    if(letter == sentence[game->pos_player] && !game->misses_after_hit){
        if(game->pos_player == 0){
            rtc_start_counter();
            return 1;
        }
        game->pos_player++;
        if(game->pos_player == game->phrase_size){
            game->elapsed_time = rtc_get_time_elapsed();
            return 0;
        }
        return 1;
    }
    if(letter == '\0' && scancode != BACKSPACE_KEY){
        game->misses_after_hit++;
        game->typo_overall_count++;
        return 1;
    }
    if( scancode == BACKSPACE_KEY){
        game->misses_after_hit--;
        if(game->misses_after_hit < 0){
            game->misses_after_hit = 0;
        }
        return 1;
    }
    
    else{
        return 1;
    }
    
return 1;
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


