#include "main.h"
#include "paw3399.h"
#include "clock.h"
#include "spi.h"
#include "usb.h"

void main(void) {
    clock_init();
    spi_init();
    paw3399_init();
    usb_init();

    asm_main_loop();
}