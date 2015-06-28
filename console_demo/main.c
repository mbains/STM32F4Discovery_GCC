#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <usart/usart.h>
#include <stdio.h>

void Delay(uint32_t nTime);
const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
const uint16_t LED[4] = {GPIO_Pin_12, GPIO_Pin_13, GPIO_Pin_14, GPIO_Pin_15};

int main(void) {
  
    char str[40];

    SystemCoreClockUpdate();
    
    usart_init();
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LEDS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);


    if (SysTick_Config(SystemCoreClock / 1000))
        while (1);

    while (1) {
        static uint32_t counter = 0;

        ++counter;

        GPIO_ResetBits(GPIOD, LEDS);

        GPIO_SetBits(GPIOD, LED[counter % 4]);
        printf("input:");
        char c = usart_getc();
        printf("%c\r\n", c);

    }
    return 0;
}

/*(5) Timer code*/
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
    TimingDelay = nTime;
    while (TimingDelay != 0);
}

void SysTick_Handler(void) {
    if (TimingDelay != 0x00)
        TimingDelay--;
}

#ifdef USE_FULL_ASSERT 

void assert_failed(uint8_t * file, uint32_t line) {
    /* Infinite loop*/
    /* use GDB to find where we're here*/
    while (1);
}
#endif

