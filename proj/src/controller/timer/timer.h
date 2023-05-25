#ifndef _LCOM_TIMER_H_
#define _LCOM_TIMER_H_

#define TIMER_MASK BIT(0)

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq);
int (timer_interrupts_subscription)(uint8_t *bit_no);
int (timer_interrupts_unsubscription)();
int (timer_get_conf)(uint8_t timer, uint8_t *st);

#endif
