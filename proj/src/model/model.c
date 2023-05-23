#include "model.h"

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t byte_index;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern MouseInfo mouse_info;
extern vbe_mode_info_t mode_info;

// Objetos a construir e manipular com a mudança de estados
Sprite *typo_racer;
Sprite *play_button;
Sprite *play;
Sprite *cursor;
Sprite *quit;
Sprite *exit_button;


// Criação dos objetos via XPM e via comum
void setup_sprites() {
   typo_racer = create_sprite_xpm((xpm_map_t) typo_racer_xpm);
   play_button =  create_sprite_button(105, 40, DARKBLUE); 
   play = create_sprite_xpm((xpm_map_t) play_button_xpm);
   cursor = create_sprite_xpm((xpm_map_t) mouse_xpm);
   quit = create_sprite_xpm((xpm_map_t) exit_xpm);
   exit_button = create_sprite_button(105, 40, DARKBLUE);
}

// É boa prática antes de acabar o programa libertar a memória alocada
void destroy_sprites() {
    destroy_sprite(typo_racer);
    destroy_sprite(play_button);
    destroy_sprite(play);
    destroy_sprite(cursor);
    destroy_sprite(quit);
    destroy_sprite(exit_button);
}

// Na altura da interrupção há troca dos buffers
void update_timer_state() {
    swap_buffers();
}


void update_keyboard_state() {
    (kbc_ih)();
    switch (scancode) {
        case BREAK_ESC:
            systemState = OVER;
            break;
        case S_KEY:
            menuState = START;
            break;
        case G_KEY:
            menuState = GAME;
            break;
        case E_KEY:
            menuState = END;
        default:
            break;
    }
    draw_new_frame();
}

// Sempre que há um novo pacote completo do rato
// - muda o seu estado interno (x, y, left_pressed, right_pressed) - mouse_sync_info();
// - pode mudar o estado do botão por baixo dele - update_buttons_state();
void update_mouse_state() {
    (mouse_ih)();
    mouse_sync_bytes();
    if (byte_index == 3) {
        mouse_sync_info();
        update_buttons_state();
        draw_new_frame();
        byte_index = 0;
    }
}


// Se o rato tiver o botão esquerdo pressionado (mouse_info.left_click) então
// muda o estado do botão no mesmo quadrante
// Senão, todos os botões voltam a não estar pressionados (buttonX->pressed = 0;)
void update_buttons_state() {

    if (mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 && mouse_info.y < mode_info.YResolution/2 +40 ){
        play_button->pressed = 1;
        if (mouse_info.left_click) {
            menuState = GAME;
            draw_new_frame();
        }
    } else if(mouse_info.x > mode_info.XResolution/2 - 65 && mouse_info.x < mode_info.XResolution/2 - 62 + 104 && mouse_info.y > mode_info.YResolution/2 + 50 && mouse_info.y < mode_info.YResolution/2 + 90 ){
        exit_button->pressed = 1;
        if (mouse_info.left_click) {
            systemState = OVER;
        }
    } else {
        play_button->pressed = 0;
        exit_button->pressed = 0;
    }
}

