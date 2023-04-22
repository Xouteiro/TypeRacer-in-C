#include "driver.h"

static int irq_keyboard;
static int irq_timer;
static int irq_mouse;
static int irq_rtc;


int(subscribe_interrupts)() {
  uint8_t bit_no = 0;
  if (keyboard_subscribe_interrupts(&bit_no)) {
    printf("Unable to subscribe to keyboard interrupts.\n");
    return 1;
  }
  irq_keyboard = BIT(bit_no);

  if (timer_subscribe_interrupts(&bit_no)) {
    printf("Unable to subscribe to timer interrupts.\n");
    return 1;
  }
  irq_timer = BIT(bit_no);

  if (mouse_subscribe_interrupts(&bit_no)) {
    printf("Unable to subscribe to mouse interrupts.\n");
    return 1;
  }
  irq_mouse = BIT(bit_no);

  if (rtc_subscribe_int(&bit_no)) {
    printf("Unable to subscribe to rtc interrupts.\n");
    return 1;
  }
  irq_rtc = BIT(bit_no);
  if (rtc_init()) {
    printf("Unable to initialize RTC.\n");
    return 1;
  }

  return 0;
}

int(unsubscribe_interrupts)() {
  if (keyboard_unsubscribe_interrupts()) {
    printf("Unable to unsubscribe keyboard interrupts.\n");
    return 1;
  }
  if (timer_unsubscribe_interrupts()) {
    printf("Unable to unsubscribe timer interrupts.\n");
    return 1;
  }
  if (rtc_unsubscribe_int()) {
    printf("Unable to unsubscribe rtc interrupts.\n");
    return 1;
  }
  if (mouse_unsubscribe_interrupts()) {
    printf("Unable to unsubscribe mouse interrupts.\n");
    return 1;
  }
  return 0;
}
