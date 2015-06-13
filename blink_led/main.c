#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

void Delay(uint32_t nTime);


int main(void){
    
    
    if(SysTick_Config(SystemCoreClock / 1000))
        while(1);
    
    while(1) {

        
        Delay(250);
    }
    return 0;
}

/*(5) Timer code*/
static __IO uint32_t TimingDelay;
void Delay(uint32_t nTime) 
{
    TimingDelay = nTime;
    while(TimingDelay !=0);
}

void SysTick_Handler(void) 
{
    if(TimingDelay != 0x00) 
        TimingDelay--;
}

#ifdef USE_FULL_ASSERT 
void assert_failed(uint8_t * file, uint32_t line)
{
    /* Infinite loop*/
    /* use GDB to find where we're here*/
    while(1);
}
#endif

