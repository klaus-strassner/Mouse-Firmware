#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

typedef union {
    struct { uint16_t btn, x, y, pad };
    uint8_t u8[8];
    uint32_t u32[2];
} usb_packet_t;

extern void asm_main_loop();

#endif