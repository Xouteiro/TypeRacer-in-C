#include "KBC.h"

int (KBC_read_status)(uint8_t* status) {
    if(status == NULL) return 1;
    return util_sys_inb(KBC_STATUS_REG, status);
}

int (KBC_read_output)(uint8_t port, uint8_t *output, uint8_t mouse) {
    uint8_t status;
    uint8_t attemps = 10;
    
    while (attemps) {

        if (KBC_read_status(&status)) {
            printf("Error: Status not available!\n");
            return 1;
        }

        if ((status & BIT(0))) {
            if(util_sys_inb(port, output)){
                printf("Error: Could not read output!\n");
                return 1;
            }
            if((status & BIT(7))){
                printf("Error: Parity error!\n");           
                return 1;
            }
            if((status & BIT(6))){
                printf("Error: Timeout error!\n");          
                return 1;
            }
            if (mouse && !(status & BIT(5))) {
                printf("Error: Mouse output not found\n");  
                return 1;
            } 
            if (!mouse && (status & BIT(5))) {
                printf("Error: Keyboard output not found\n"); 
                return 1;
            } 
            return 0; 
        }
        tickdelay(micros_to_ticks(20000));
        attemps--;
    }
    return 1;
}

int (KBC_write_command)(uint8_t port, uint8_t commandByte) {
    uint8_t status;
    uint8_t attemps = MAX_ATTEMPS;

    while (attemps) {

        if (KBC_read_status(&status)){
            printf("Error: Status not available!\n");
            return 1;
        }

        if ((status & FULL_IN_BUFFER) == 0){

            if(sys_outb(port, commandByte)){
                printf("Error: Could not write commandByte!\n");
                return 1;
            }

            return 0;
        }
        tickdelay(micros_to_ticks(WAIT_KBC));
        attemps--;
    }
    
    return 1;
}
