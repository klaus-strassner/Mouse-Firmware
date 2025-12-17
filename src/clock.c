    #include "clock.h"
    #include "stm32f730xx.h"

    void clock_init(void) {
        // turn on HSE
        RCC->CR |= RCC_CR_HSEON;
        while(!(RCC->CR & RCC_CR_HSERDY));

        // turn off PLL
        RCC->CR &= ~RCC_CR_PLLON;
        while(RCC->CR & RCC_CR_PLLRDY);

        // configure PLL
        MODIFY_REG(RCC->PLLCFGR,
            RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLSRC,
            _VAL2FLD(RCC_PLLCFGR_PLLM, CLOCK_PLLM) | // set HSE divider for PLL
            _VAL2FLD(RCC_PLLCFGR_PLLN, CLOCK_PLLN) | // set PLL multiplier for VCO
            _VAL2FLD(RCC_PLLCFGR_PLLP, CLOCK_PLLP) | // set PLL divider for sysclock
            _VAL2FLD(RCC_PLLCFGR_PLLQ, CLOCK_PLLQ) | // set PLL divider for USB
            RCC_PLLCFGR_PLLSRC_HSE); // set PLL source to HSE

        // turn on PLL
        RCC->CR |= RCC_CR_PLLON;
        while(!(RCC->CR & RCC_CR_PLLRDY));

        // enable overdrive mode
        PWR->CR1 |= PWR_CR1_ODEN;
        while(!(PWR->CSR1 & PWR_CSR1_ODRDY));
        PWR->CR1 |= PWR_CR1_ODSWEN;
        while(!(PWR->CSR1 & PWR_CSR1_ODSWRDY));

        // set flash memory wait states
        MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, CLOCK_FLASH_WS);

        // set APB prescalers
        MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, CLOCK_PPRE1);
        MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, CLOCK_PPRE2);

        // set AHB prescaler
        MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, CLOCK_HPRE);

        // wait for PLL lock
        while(!(RCC->CR & RCC_CR_PLLRDY));

        // switch to PLL used as sysclock
        RCC->CFGR |= RCC_CFGR_SW_PLL;
        while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

        // enable USB OTG HS PHY Controller
        RCC->APB2ENR |= RCC_APB2ENR_OTGPHYCEN;

        // turn off HSI
        RCC->CR &= ~RCC_CR_HSION;
        while((RCC->CR & RCC_CR_HSIRDY));
    }