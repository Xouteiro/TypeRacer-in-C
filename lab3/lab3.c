#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include "keyboard.h"
#include "timer.c"


#include <stdbool.h>
#include <stdint.h>

uint8_t scancode;
extern int cnt;
extern bool ih_flag;
extern int timer_counter;


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (kbd_test_scan)()
{
  int ipc_status;
  uint8_t irq_set;
  message msg;

  if (keyboard_subscribe_interrupts(&irq_set) != 0)
    return 1;

  while(scancode != BREAK_ESC) {
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)){
        case HARDWARE: {
          if (msg.m_notify.interrupts & irq_set) {
            
            kbc_ih();
          
          kbd_print_scancode(ih_flag,sizeof(scancode),&scancode);
          }
          break;
        }

          default: break;
        }
        
      }
      
    }

  if (keyboard_unsubscribe_interrupts() != 0)
    return 1;
  if (kbd_print_no_sysinb(cnt) != 0)
    return 1;

  return 0;
}

int(kbd_test_poll)() {


  while(scancode != BREAK_ESC){
    read_KBC_output(0x60, &scancode);
    if (scancode & BIT(7)) {
      kbd_print_scancode(0,sizeof(scancode),&scancode);
    } else {
      kbd_print_scancode(1,sizeof(scancode),&scancode);
    }
      

  }

  if(kbc_restore() != 0) return 1;

  if (kbd_print_no_sysinb(cnt) != 0)
    return 1;

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t kbc_bit_no;
  keyboard_subscribe_interrupts(&kbc_bit_no);

  uint8_t timer_bit_no;
  timer_subscribe_int(&timer_bit_no);


  uint32_t kbc_irq_set = BIT(kbc_bit_no);
  uint32_t timer_irq_set = BIT(timer_bit_no);

  message msg;
  int ipc_status;

  while (scancode != BREAK_ESC && (timer_counter/60.0) < n) {
    
    if ((driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("Error");
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE: {
          if (msg.m_notify.interrupts & kbc_irq_set) { // keyboard interrupt

            kbc_ih();
          
            kbd_print_scancode(ih_flag, sizeof(scancode), &scancode);
            

          }

          if (msg.m_notify.interrupts & timer_irq_set) { // timer interrupt
            
            timer_int_handler();
            
          }

          break;
        }

        default: break;
      }
    }
  }

  if(kbc_restore()!=0)
    return 1;
  if (keyboard_unsubscribe_interrupts() != 0)
    return 1;
  if(timer_unsubscribe_int() != 0)
    return 1;
  if (kbd_print_no_sysinb(cnt) != 0)
    return 1;

  return 0;
}




