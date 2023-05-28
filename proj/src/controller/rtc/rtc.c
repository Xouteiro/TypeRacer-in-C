#include "rtc.h"

static int hook_rtc = 0;
static uint8_t day, month, year;
static uint8_t second, minute, hour;
static int count_interrupts = 0;

int (rtc_interrupts_subscription)(uint8_t *bit_no) {
  if(bit_no == NULL) return 1;
  hook_rtc = RTC_IRQ;
  *bit_no = RTC_IRQ;
  return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_rtc);
}

int (rtc_interrupts_unsubscription)() {
  return sys_irqrmpolicy(&hook_rtc);
}

int (rtc_initialize)() {
  uint8_t reg_b = 0;
  if (rtc_read_register(0xB, &reg_b)) return 1;
  reg_b |= UIE | PIE;
  if (rtc_write_register(0xB, reg_b)) return 1;
  if (rtc_update_date()) return 1;
  if (rtc_update_hour()) return 1;
  return 0;
}

void (rtc_ih)() {
  uint8_t reg = 0;
  do {
    if (rtc_read_register(0xA, &reg)) return;
  } while(reg & UIP);
  if (rtc_read_register(0xC, &reg)) return;
  if (!(reg & IRQF)) return;
  if (reg & UF) {
    if (rtc_update_date()) return;
    if (rtc_update_hour()) return;
  }
  if (reg & PF) {
    rtc_interrupt_counter();
  }
}

int (rtc_counter_start)(void) {
  uint8_t reg = 0;
  do {
    if (rtc_read_register(0xA, &reg)) return 1;
  } while(reg & UIP);
  count_interrupts = 0;
  return rtc_write_register(0xA, reg | RATE);
}

void (rtc_interrupt_counter)(void) {
  count_interrupts++;
}

int (rtc_get_elapsed_time)(void) {
  return count_interrupts / 2;
}

int (rtc_update_date)(void) {
  if (rtc_read_register(DAY_REG, &day)) return 0;
  if (rtc_read_register(MONTH_REG, &month)) return 0;
  if (rtc_read_register(YEAR_REG, &year)) return 0;
  return 0;
}

int (rtc_update_hour)(void) {
  if (rtc_read_register(SECOND_REG, &second)) return 0;
  if (rtc_read_register(MINUTE_REG, &minute)) return 0;
  if (rtc_read_register(HOUR_REG, &hour)) return 0;
  return 0;
}

int (rtc_read_register)(uint8_t reg, uint8_t* byte) {
  if (sys_outb(RTC_ADDR_REG, reg)) return 1;
  if (util_sys_inb(RTC_DATA_REG, byte)) return 1;
  return 0;
}

int (rtc_write_register)(uint8_t reg, uint8_t byte) {
  if (sys_outb(RTC_ADDR_REG, reg)) return 1;
  if (sys_outb(RTC_DATA_REG, byte)) return 1;
  return 0;
}
