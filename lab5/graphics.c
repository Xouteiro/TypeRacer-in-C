#include "graphics.h"
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

vbe_mode_info_t mode_info;
uint8_t *frame_buffer;
uint8_t bytes_per_pixel;

int (set_frame_buffer)(uint16_t mode){
    memset(&mode_info, 0, sizeof(mode_info));
    if(vbe_get_mode_info(mode, &mode_info)) return 1;

    bytes_per_pixel = (mode_info.BitsPerPixel + 7) / 8;
    unsigned int frame_size = mode_info.XResolution * mode_info.YResolution * bytes_per_pixel;
    
    struct minix_mem_range physic_addresses;
    physic_addresses.mr_base = mode_info.PhysBasePtr;
    physic_addresses.mr_limit = physic_addresses.mr_base + frame_size;

    if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_addresses)) return 1;

    frame_buffer = vm_map_phys(SELF, (void*) physic_addresses.mr_base, frame_size);
    if (frame_buffer == NULL) return 1;
    

    return 0;
}

int (set_graphic_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10;    
    reg86.ah = 0x4F;
    reg86.al = 0x02;
    reg86.bx = submode | BIT(14);

    if (sys_int86(&reg86)) return 1;
    
    return 0;
}
