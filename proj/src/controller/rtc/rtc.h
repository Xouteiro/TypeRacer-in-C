#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#define RTC_MASK            5
#define IRQ_RTC             8
#define REGISTER_INPUT      0x70
#define REGISTER_OUTPUT     0x71

#define REGISTER_UPDATING   10
#define REGISTER_COUNTING   11

#define SECONDS    0
#define MINUTES    2
#define HOURS      4   
#define DAY        7
#define MONTH      8
#define YEAR       9

#define BINARY              BIT(2)
#define UPDATING            BIT(7)
#define RATE (BIT(0) | BIT(1) | BIT(2) | BIT(3))

typedef struct {
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
} real_time_info;

int (rtc_setup)();
int (rtc_interrupts_subscription)(uint8_t *bit_no);
int (rtc_interrupts_unsubscription)();
int (rtc_output_read)(uint8_t command, uint8_t *output);
int (rtc_write)(uint8_t command, uint8_t output);
void rtc_handle_period(void);
int rtc_get_time_elapsed(void);
int rtc_start_counter(void);
int (rtc_is_updating)();
int (rtc_is_binary)();
int (rtc_is_bcd)();
int (rtc_update_time_info)();
uint8_t (to_binary)(uint8_t bcd_number);

#endif
