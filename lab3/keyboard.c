#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "KBC.h"

int keyboard_hook_id = 1;
bool ih_flag;
uint8_t scancode[2];
int i = 0;



// subscribe interrupts
int keyboard_subscribe_interrupts(uint8_t *bit_no)
{
  if (bit_no == NULL)
    return 1;
  *bit_no = BIT(keyboard_hook_id);
  // para detectar as interrupções geradas
  // subscrição das interrupções em modo exclusivo
  return sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, 
                          &keyboard_hook_id);
}

// unsubscribe interrupts
int keyboard_unsubscribe_interrupts ()
{
  return sys_irqrmpolicy(&keyboard_hook_id);
}


void (kbc_ih)(){
  
  uint8_t output;
  read_KBC_output(0x60, &output);

  uint8_t st;
  read_KBC_status(&st);

  if (check_status(st) == 0) {

    scancode[i] = output;

    if (output != TWO_BYTES) {
      if (output & MAKE_CODE) {
        ih_flag = false;
      } else {
        ih_flag = true;
      }
    }

  }
}

int kbc_restore()
{
  uint8_t commandWord;

  // Leitura da configuração atual
  if (write_KBC_command(0x64, 0x20) != 0)
    return 1;  // notificar o i8042 da leitura
    
  if (read_KBC_output(0x60, &commandWord) != 0)
    return 1;  // ler a configuração

  // Activar o bit das interrupções
  commandWord = commandWord | BIT(0);

  // Escrita da nova configuração
  if (write_KBC_command(0x64, 0x60) != 0)
    return 1;  // notificar o i8042 da escrita
    
  if (write_KBC_command(0x60, commandWord) != 0)
    return 1;  // escrever a configuração
    
  return 0;
}








