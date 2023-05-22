#ifndef PROJ_H
#define PROJ_H


#define VIDEO_MODE 0x115
#define GAME_FREQ 60


#include <lcom/lcf.h>
#include "controller/timer/timer.h"
#include "controller/video/graphics.h"
#include "controller/keyboard_mouse/keyboard.h"
#include "controller/keyboard_mouse/mouse.h"
#include "controller/rtc/rtc.h"
#include "model/model.h"
#include "view/view.h"

/**
 * @brief Initializes everything needed for the program.
 * 
 * @return int 0 upon success, non-zero otherwise.
 */
int setup(void);

/**
 * @brief Runs a step of the program.
 * This should be done once per iteration. The function checks for 
 * interrupts and delegates tasks depending on the current program
 * state
 * 
 */
void proj_step(void);

/**
 * @brief Cleans up the program.
 * This function **must** be called before exiting the program.
 * 
 * @return int 0 upon success, non-zero otherwise.
 */
int proj_cleanup(void);


/**
 * @brief Changes the current state of the programing.
 * This function changes the execution state and makes the actions 
 * necessary for all the possible states.
 * 
 * @param new_state New program state.
 */
//void proj_set_state(State new_state);

/**
 * @brief Get a pointer to the project's mouse sprite.
 * This can be useful to check for mouse collision e.g.
 * 
 * @return mouse_sprite* Mouse sprite struct.
 */
//mouse_sprite* proj_get_mouse();



/**@}*/


#endif
