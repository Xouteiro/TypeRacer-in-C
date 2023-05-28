#include "keyboard.h"

uint8_t scancode = 0;
int keyboard_hook_id = 1;

bool ih_flag;

// interrupt subscription
int (keyboard_interrupts_subscription)(uint8_t *bit_no) {
    if(bit_no == NULL) return 1;
    (*bit_no) = BIT(keyboard_hook_id);
    return sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id);
}

// interrupt unsubscription
int (keyboard_interrupts_unsubscription)() {
    return sys_irqrmpolicy(&keyboard_hook_id);
}

// interrupt handler
void (kbc_ih)() {
    KBC_read_output(KBC_OUT_CMD, &scancode, 0);
}
