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
void (KBC_interrupt_handler)() {
    KBC_read_output(KBC_OUT_CMD, &scancode, 0);
}
/*
// restore keyboard interrupts
int (keyboard_restore)() {
    uint8_t cmdByte;

    if (KBC_write_command(KBC_IN_CMD, KBC_READ_CMD) != 0) return 1;          
    if (KBC_read_output(KBC_OUT_CMD, &cmdByte, 0) != 0) return 1; 

    cmdByte |= ENABLE_INT;  

    if (KBC_write_command(KBC_IN_CMD, KBC_WRITE_CMD) != 0) return 1;    
    if (KBC_write_command(KBC_WRITE_CMD, cmdByte) != 0) return 1;

    return 0;
}

*/
void (kbc_ih)() {
    KBC_read_output(KBC_OUT_CMD, &scancode, 0);
}
