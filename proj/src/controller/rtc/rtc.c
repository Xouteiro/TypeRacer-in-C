#include "rtc.h"

// global variables
int rtc_hook_id = RTC_MASK;
real_time_info time_info;
uint8_t binary_mode;
static int count_interrupts = 0;

int (rtc_setup)() {
    binary_mode = rtc_is_binary();
    if(rtc_update_time_info()) return 1;
    return 0;
}

// interrupt subscription
int (rtc_interrupts_subscription)(uint8_t *bit_no) {
    if(bit_no == NULL) return 1;
    (*bit_no) = BIT(rtc_hook_id);
    return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &rtc_hook_id);
}

// interrupt unsubscription
int (rtc_interrupts_unsubscription)() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

// reads rtc output by a given command
int (rtc_output_read)(uint8_t command, uint8_t *output) {
    if (sys_outb(REGISTER_INPUT, command)) return 1;
	if (util_sys_inb(REGISTER_OUTPUT, output)) return 1;
    return 0;
}

int (rtc_write)(uint8_t command, uint8_t output) {
    if (sys_outb(REGISTER_INPUT, command)) return 1;
	if (sys_outb(REGISTER_OUTPUT, output)) return 1;
    return 0;
}

// returns 1 if rtc is still updating
int (rtc_is_updating)() {
    uint8_t result;
    if (rtc_output_read(REGISTER_UPDATING, &result)) return 1;
	return result & UPDATING;
}

// returns 1 if the counting mode is binary
int (rtc_is_binary)() {
    uint8_t result;
    if (rtc_output_read(REGISTER_COUNTING, &result)) return 1;
	return result & BINARY;
}

// returns 1 if the counting mode is BCD
int (rtc_is_bcd)() {
    return !rtc_is_binary();
}

// updates time_info
int (rtc_update_time_info)() {
    if (rtc_is_updating()) return 1;
    uint8_t output;

    if (rtc_output_read(SECONDS, &output)) return 1;
    time_info.seconds = binary_mode ? output : to_binary(output);

    if (rtc_output_read(MINUTES, &output)) return 1;
    time_info.minutes = binary_mode ? output : to_binary(output);

    if (rtc_output_read(HOURS, &output)) return 1;
    time_info.hours = binary_mode ? output : to_binary(output);

    if (rtc_output_read(DAY, &output)) return 1;
    time_info.day = binary_mode ? output : to_binary(output);

    if (rtc_output_read(MONTH, &output)) return 1;
    time_info.month = binary_mode ? output : to_binary(output);

    if (rtc_output_read(YEAR, &output)) return 1;
    time_info.year = binary_mode ? output : to_binary(output);

    return 0;
}

uint8_t (to_binary)(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

int rtc_start_counter(void) {
  uint8_t reg = 0;
  do {
    if (rtc_output_read(0xA, &reg)) return 1;
  } while(reg & UPDATING);
  count_interrupts = 0;
  return rtc_write(0xA, reg | RATE);
}


void rtc_handle_period(void) {
  count_interrupts++;
}

int rtc_get_time_elapsed(void) {
  return count_interrupts / 2;
}
