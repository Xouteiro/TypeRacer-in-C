#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(*LSB == NULL) return 1;
    *LSB = value & 0xFF;
    return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  
    if(*MSB == NULL) return 1;
    *MSB = value >> 8;
    return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t value;
    if(sysinb(port,&value) != 0) return 1;
     *temp = value & 0xFF;
    return 0;
}
