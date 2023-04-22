#ifndef DRIVER_H
#define DRIVER_H


#include <lcom/lcf.h>
#include "controller/keyboard_mouse/keyboard.h"
#include "controller/keyboard_mouse/mouse.h"
#include "controller/rtc/rtc.h"
#include "controller/video/graphics.h"
#include "controller/timer/timer.h"


/**
 * @brief Subscribe interrupts: keyboard, mouse, timer.
 * @return int Returns zero upon success.
 */
int (subscribe_interrupts)(void);

/**
 * @brief Unsubscribe interrupts: keyboard, mouse, timer.
 * @return int Returns zero upon success.
 */
int (unsubscribe_interrupts)(void);


#endif
