#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id = 0;
int timer_counter = 0;

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
    if(freq > TIMER_FREQ || freq < 19 || timer < 0 || timer > 2) return 1;

  uint32_t initialValue = TIMER_FREQ / freq;
  uint8_t msb, lsb;
  if(util_get_LSB(initialValue, &lsb)) return 1;
  if(util_get_MSB(initialValue, &msb)) return 1;

  uint8_t controlword;
  if(timer_get_conf(timer, &controlword)) return 1;
  controlword = (controlword & 0xF) | TIMER_LSB_MSB;

  if(timer == 1) controlword = controlword | BIT(6);
  else if(timer == 2) controlword = controlword | BIT(7);
  

  if(sys_outb(TIMER_CTRL, controlword)) return 1;
  if(sys_outb(TIMER_0 + timer, lsb)) return 1;
  if(sys_outb(TIMER_0 + timer, msb)) return 1;

  return 0;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL)
    return 1;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id))
    return 1;
  *bit_no = BIT(hook_id);
  return 0;
}

int(timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id))
    return 1;
  return 0;
}

void(timer_int_handler)() {
  timer_counter++;
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer < 0 || timer > 2) return 1;
  uint8_t controlword = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);
  if(sys_outb(TIMER_CTRL, controlword)) return 1;
  if (util_sys_inb(TIMER_0, st)) return 1;
  return 0;
}

int(timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val val;

  switch (field) {
    case tsf_all:
      val.byte = st;
      return timer_print_config(timer, field, val);
    case tsf_initial:
      val.in_mode = ((st & (BIT(5) | BIT(6))) >> 4);
      return timer_print_config(timer, field, val);
    case tsf_mode:
      val.count_mode = ((st & (BIT(1) | BIT(2) | BIT(3))) >> 1);
      return timer_print_config(timer, field, val);
    case tsf_base:
      val.bcd = (st & BIT(0));
      return timer_print_config(timer, field, val);
  }
}
