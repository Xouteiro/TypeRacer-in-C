#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
   uint16_t counter = TIMER_FREQ/freq;
    if(freq < 19 || freq>TIMER_FREQ) return 1;
    uint8_t conf;
    if(timer_get_conf(timer, &conf) != 0)return 1;
    conf = conf & 0x0F;
    conf =conf | BIT(5) | BIT(4);
    sys_outb(0x43,conf);
    uint8_t MSB,LSB;
    util_get_LSB(counter,&LSB);
    util_get_MSB(counter,&MSB);
    sys_outb(0x40+timer,LSB);
    sys_outb(0x40+timer,MSB);
    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(timer<0 || timer >2 ) return 1;
    uint8_t controlword = BIT(7) | BIT(6) | BIT(5) | BIT(timer+1);
    sys_outb(0x43,controlword);
    if(util_sys_inb(0x40,st) != 0)return 1;
    return 0;
    
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val conf;
  switch(field){
    case tsf_all:
      conf.byte = st;
      break;
    case tsf_initial:
      if(st & TIMER_LSB_MSB) conf.in_mode = MSB_after_LSB;
      else if(st & TIMER_LSB) conf.in_mode = LSB_only;
      else if(st & TIMER_MSB) conf.in_mode = MSB_only;
      else conf.in_mode = INVAL_val;
      break;
    case tsf_mode:
      conf.count_mode = (st >> 1) & 7;
      break;
    case tsf_base:
      conf.bcd = st & 1;
      break;
  }
  return timer_print_config(timer, field, conf);
}
