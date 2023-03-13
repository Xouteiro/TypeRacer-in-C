#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq < 19 || freq < TIMER_FREQ)
    return 1;
  uint16_t counter = TIMER_FREQ / freq;
  uint8_t conf;
  if (timer_get_conf(timer, &conf))
    return 1;
  conf = conf & 0xF;
  conf = conf | BIT(5) | BIT(4);
  sys_outb(0x43, conf);
  uint8_t MSB, LSB;
  util_get_LSB(counter, &LSB);
  util_get_MSB(counter, &MSB);
  sys_outb(0x40 + timer, LSB);
  sys_outb(0x40 + timer, MSB);
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  int hook_id = 0;
  if (bit_no == NULL)
    return 1;
  if (sys_irqsetpolicy(TIMER0_IRQ, irq_penable, &hook_id))
    return 1;
  *bit_no = BIT(hook_id);
  return 0;
}

int(timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void(timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer < 0 || timer > 2)
    return 1;
  uint8_t controlword = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);
  sys_outb(0x43, controlword);
  if (util_sys_inb(0x40, configuration))
    return 1;
  return 0;
}

int(timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
