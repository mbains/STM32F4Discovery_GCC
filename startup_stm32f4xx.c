#include <stm32f4xx.h>
#include <core_cm4.h>

extern void _estack(void);  // to force type checking
void Reset_Handler(void);
void default_handler (void) 
{
  while(1);
}

void __attribute__ ((weak)) __libc_init_array (void){}

// Linker supplied pointers

extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;

extern int main(void);

void Reset_Handler(void) {

   unsigned long *src, *dst;

   src = &_sidata;
   dst = &_sdata;

   // Copy data initializers

    while (dst < &_edata)
      *(dst++) = *(src++);

   // Zero bss

   dst = &_sbss;
   while (dst < &_ebss)
       *(dst++) = 0;

  SystemInit();
  __libc_init_array();
  main();
  while(1) {}
}

/* Vector Table */

void NMI_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void HardFault_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void MemMange_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void BusFault_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void UsageFault_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void SVC_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void DebugMon_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void PendSV_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void SysTick_Handler (void) __attribute__ ((weak,  alias ("default_handler")));
void WWDG_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void PVD_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TAMPER_STAMP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void RTC_WKUP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void FLASH_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void RCC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI0_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI4_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream0_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream4_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream5_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void DMA1_Stream6_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void ADC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void CAN1_TX_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));
void CAN1_RX0_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));
void CAN1_RX1_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));
void CAN1_SCE_IRQHandler(void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI9_5_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_BRK_TIM9_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_UP_TIM10_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_TRG_COM_TIM11_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));

void TIM1_BRK_TIM15_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_UP_TIM16_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_TRG_COM_TIM17_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM1_CC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void TIM4_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void I2C1_EV_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void I2C1_ER_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void I2C2_EV_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void I2C2_ER_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void SPI1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void SPI2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void USART1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void USART2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void USART3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void EXTI15_10_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void RTC_Alarm_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler")));
void OTG_FS_WKUP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM8_BRK_TIM12_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM8_UP_TIM13_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM8_TRG_COM_TIM14_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM8_CC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA1_Stream7_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void FSMC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void SDIO_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM5_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void SPI3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void UART4_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void UART5_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM6_DAC_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void TIM7_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream0_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream2_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream3_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream4_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void ETH_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void ETH_WKUP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void CAN2_TX_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void CAN2_RX0_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void CAN2_RX1_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void OTG_FS_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream5_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream6_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DMA2_Stream7_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void USART6_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void I2C3_EV_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void I2C3_ER_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void OTG_HS_EP1_OUT_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void OTG_HS_EP1_IN_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void OTG_HS_WKUP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void OTG_HS_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void DCMI_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void CRYP_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void HASH_RNG_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 
void FPU_IRQHandler (void) __attribute__ ((weak,  alias ("default_handler"))); 




__attribute__ ((section(".isr_vector")))

void (* const g_pfnVectors[])(void) = {

	_estack,
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemMange_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	0, 
        0, 
        0, 
        0,
	SVC_Handler,
	DebugMon_Handler,
	0,
	PendSV_Handler,
	SysTick_Handler,
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMPER_STAMP_IRQHandler,
	RTC_WKUP_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_Stream0_IRQHandler,
	DMA1_Stream1_IRQHandler,
	DMA1_Stream2_IRQHandler,
	DMA1_Stream3_IRQHandler,
	DMA1_Stream4_IRQHandler,
	DMA1_Stream5_IRQHandler,
	DMA1_Stream6_IRQHandler,
	ADC_IRQHandler,
	CAN1_TX_IRQHandler,
        CAN1_RX0_IRQHandler,
        CAN1_RX1_IRQHandler,
        CAN1_SCE_IRQHandler, 
	EXTI9_5_IRQHandler,
	TIM1_BRK_TIM9_IRQHandler,
	TIM1_UP_TIM10_IRQHandler,
	TIM1_TRG_COM_TIM11_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
	TIM4_IRQHandler,
	I2C1_EV_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_IRQHandler,
	USART2_IRQHandler,
	USART3_IRQHandler,
	EXTI15_10_IRQHandler,
	RTC_Alarm_IRQHandler, 
        OTG_FS_WKUP_IRQHandler,
        TIM8_BRK_TIM12_IRQHandler,
        TIM8_UP_TIM13_IRQHandler,
        TIM8_TRG_COM_TIM14_IRQHandler,
        TIM8_CC_IRQHandler,
        DMA1_Stream7_IRQHandler,
        FSMC_IRQHandler,
        SDIO_IRQHandler,
        TIM5_IRQHandler,
        SPI3_IRQHandler,
        UART4_IRQHandler,
        UART5_IRQHandler,
        TIM6_DAC_IRQHandler,
        TIM7_IRQHandler,
        DMA2_Stream0_IRQHandler,
        DMA2_Stream1_IRQHandler,
        DMA2_Stream2_IRQHandler,
        DMA2_Stream3_IRQHandler,
        DMA2_Stream4_IRQHandler,
        ETH_IRQHandler,
        ETH_WKUP_IRQHandler,
        CAN2_TX_IRQHandler,
        CAN2_RX0_IRQHandler,
        CAN2_RX1_IRQHandler,
        OTG_FS_IRQHandler,
        DMA2_Stream5_IRQHandler,
        DMA2_Stream6_IRQHandler,
        DMA2_Stream7_IRQHandler,
        USART6_IRQHandler,
        I2C3_EV_IRQHandler,
        I2C3_ER_IRQHandler,
        OTG_HS_EP1_OUT_IRQHandler,
        OTG_HS_EP1_IN_IRQHandler,
        OTG_HS_WKUP_IRQHandler,
        OTG_HS_IRQHandler,
        DCMI_IRQHandler,
        CRYP_IRQHandler,
        HASH_RNG_IRQHandler,
        FPU_IRQHandler
	};
