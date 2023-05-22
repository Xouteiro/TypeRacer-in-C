#include <lcom/lcf.h>
#include "proj.h"



extern SystemState systemState;
extern MenuState menuState;

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/g3/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/g3/proj/src/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}


int setup(){ 

  setup_sprites();

  if (timer_set_frequency(TIMER, GAME_FREQ) != 0) return 1;

  // Inicialização dos buffers de vídeo (double buffering)
  if (set_frame_buffers(VIDEO_MODE) != 0) return 1;

  // Inicialização do modo gráfico
  if (set_graphic_mode(VIDEO_MODE) != 0) return 1;

   // Ativação das interrupções dos dispositivos
  // Ativação das interrupções dos dispositivos
  if (timer_subscribe_interrupts() != 0) return 1;
  if (keyboard_subscribe_interrupts() != 0) return 1;
  if (mouse_subscribe_interrupts() != 0) return 1;
  if (rtc_subscribe_interrupts() != 0) return 1;

  // Ativar stream-mode e report de dados do rato
  if (mouse_write(ENABLE_STREAM_MODE) != 0) return 1;
  if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;


  return 0;

}

int proj_cleanup(){
  // Volta ao modo de texto
  if (vg_exit() != 0) return 1;

  destroy_sprites();

  if (timer_unsubscribe_interrupts() != 0) return 1;
  if (keyboard_unsubscribe_interrupts() != 0) return 1;
  if (mouse_unsubscribe_interrupts() != 0) return 1;
  if (rtc_unsubscribe_interrupts() != 0) return 1;

  // Desativar o report de dados do rato
  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;

  // Desativar o report de dados do rato
  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;

  return 0;
}
/*
void proj_set_state(MenuState new_state) {
  menuState = new_state;
  switch (new_state) {
    case GAME:
      // develop game state
      break;
    case START:
      proj_step_state = menu_step;
      break;
    case END:
      proj_step_state = proj_step_game_over;
      break;
    default:
      break;
  }
}
*/


int(proj_main_loop)(int argc, char* argv[]){
  
  if (setup()) return 1;
  
  draw_new_frame();

  int ipc_status;
  message msg;
  while (systemState == RUNNING) {
    
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & TIMER_MASK)    update_timer_state();
          if (msg.m_notify.interrupts & KEYBOARD_MASK) update_keyboard_state();
          if (msg.m_notify.interrupts & MOUSE_MASK)    update_mouse_state();
        }
    }
  }
  
  if (proj_cleanup() != 0) return 1;

  return 0;
}

