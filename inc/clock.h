#ifndef CLOCK_H
#define CLOCK_H

#include "stm32f730xx.h"

// define clock speeds
#define CLOCK_VCO_OUT               384
#define CLOCK_SYS                   192
#define CLOCK_AHB                   192
#define CLOCK_APB1                  48
#define CLOCK_APB2                  96

#define CLOCK_HSE                   24
#define CLOCK_VCO_IN                2
#define CLOCK_USB                   48

// define PLL config values
#define CLOCK_PLLM                  CLOCK_HSE/CLOCK_VCO_IN
#define CLOCK_PLLN                  CLOCK_VCO_OUT/CLOCK_VCO_IN
#define CLOCK_PLLP                  (CLOCK_VCO_OUT/CLOCK_SYS)/2-1
#define CLOCK_PLLQ                  CLOCK_VCO_OUT/CLOCK_USB

// define power scales
#define CLOCK_PWR_SCALE_3           0b01
#define CLOCK_PWR_SCALE_2           0b10
#define CLOCK_PWR_SCALE_1           0b11

// define power scale mode
#if(CLOCK_SYS > 168)
    #define CLOCK_PWR_SCALE         CLOCK_PWR_SCALE_1
#elif(CLOCK_SYS > 108)
    #define CLOCK_PWR_SCALE         CLOCK_PWR_SCALE_2
#else
    #define CLOCK_PWR_SCALE         CLOCK_PWR_SCALE_3
#endif

// define over-drive requirement
#if (CLOCK_PWR_SCALE == CLOCK_PWR_SCALE_1)
    #define CLOCK_USE_OVERDRIVE     (CLOCK_SYS > 180)
#elif (CLOCK_PWR_SCALE == CLOCK_PWR_SCALE_2)
    #define CLOCK_USE_OVERDRIVE     (CLOCK_SYS > 144)
#else
    #define CLOCK_USE_OVERDRIVE     0
#endif

// define AHB prescaler
#if(CLOCK_SYS/CLOCK_AHB == 1)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV1
#elif(CLOCK_SYS/CLOCK_AHB == 2)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV2
#elif(CLOCK_SYS/CLOCK_AHB == 4)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV4
#elif(CLOCK_SYS/CLOCK_AHB == 8)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV8
#elif(CLOCK_SYS/CLOCK_AHB == 16)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV16
#elif(CLOCK_SYS/CLOCK_AHB == 64)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV64
#elif(CLOCK_SYS/CLOCK_AHB == 128)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV128
#elif(CLOCK_SYS/CLOCK_AHB == 256)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV256
#elif(CLOCK_SYS/CLOCK_AHB == 512)
    #define CLOCK_HPRE              RCC_CFGR_HPRE_DIV512
#else
    #error "invalid ratio"
#endif

// define APB1 prescaler
#if(CLOCK_SYS/CLOCK_APB1 == 1)
    #define CLOCK_PPRE1              RCC_CFGR_PPRE1_DIV1
#elif(CLOCK_SYS/CLOCK_APB1 == 2)
    #define CLOCK_PPRE1              RCC_CFGR_PPRE1_DIV2
#elif(CLOCK_SYS/CLOCK_APB1 == 4)
    #define CLOCK_PPRE1              RCC_CFGR_PPRE1_DIV4
#elif(CLOCK_SYS/CLOCK_APB1 == 8)
    #define CLOCK_PPRE1              RCC_CFGR_PPRE1_DIV8
#elif(CLOCK_SYS/CLOCK_APB1 == 16)
    #define CLOCK_PPRE1              RCC_CFGR_PPRE1_DIV16
#else
    #error "invalid ratio"
#endif

// define APB2 prescaler
#if(CLOCK_SYS/CLOCK_APB2 == 1)
    #define CLOCK_PPRE2              RCC_CFGR_PPRE2_DIV1
#elif(CLOCK_SYS/CLOCK_APB2 == 2)
    #define CLOCK_PPRE2              RCC_CFGR_PPRE2_DIV2
#elif(CLOCK_SYS/CLOCK_APB2 == 4)
    #define CLOCK_PPRE2              RCC_CFGR_PPRE2_DIV4
#elif(CLOCK_SYS/CLOCK_APB2 == 8)
    #define CLOCK_PPRE2              RCC_CFGR_PPRE2_DIV8
#elif(CLOCK_SYS/CLOCK_APB2 == 16)
    #define CLOCK_PPRE2              RCC_CFGR_PPRE2_DIV16
#else
    #error "invalid ratio"
#endif

// define wait state for 3.3V
#if (CLOCK_AHB <= 30)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_0WS
#elif (CLOCK_AHB <= 60)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_1WS
#elif (CLOCK_AHB <= 90)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_2WS
#elif (CLOCK_AHB <= 120)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_3WS
#elif (CLOCK_AHB <= 150)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_4WS
#elif (CLOCK_AHB <= 180)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_5WS
#elif (CLOCK_AHB <= 210)
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_6WS
#else
    #define CLOCK_FLASH_WS    FLASH_ACR_LATENCY_7WS
#endif


void clock_init(void);

#endif