#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <misc.h>

#include "ring.h"
#include "usart.h"

static RingBuffer txbuffer = {0, 0};
static RingBuffer rxbuffer = {0, 0};

#define countof(a)   (sizeof(a) / sizeof(*(a)))

uint8_t txbuf[] = "Hello\r\n";
#define txbufsize  (countof(txbuf) - 1)

#define USARTx                           USART3
#define USARTx_CLK                       RCC_APB1Periph_USART3
#define USARTx_CLK_INIT                  RCC_APB1PeriphClockCmd
#define USARTx_IRQn                      USART3_IRQn
#define USARTx_IRQHandler                USART3_IRQHandler

#define USARTx_TX_PIN                    GPIO_Pin_10                
#define USARTx_TX_GPIO_PORT              GPIOC                       
#define USARTx_TX_GPIO_CLK               RCC_AHB1Periph_GPIOC
#define USARTx_TX_SOURCE                 GPIO_PinSource10
#define USARTx_TX_AF                     GPIO_AF_USART3

#define USARTx_RX_PIN                    GPIO_Pin_11                
#define USARTx_RX_GPIO_PORT              GPIOC                    
#define USARTx_RX_GPIO_CLK               RCC_AHB1Periph_GPIOC
#define USARTx_RX_SOURCE                 GPIO_PinSource11
#define USARTx_RX_AF                     GPIO_AF_USART3

static int TxPrimed = 0;
int RxOverflow = 0;

int usart_init() {
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  USARTx_CLK_INIT(USARTx_CLK, ENABLE);
  
  /* Connect USART pins to AF7 */
  GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
  GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

  /* Enable the USART OverSampling by 8 */
  USART_OverSampling8Cmd(USARTx, ENABLE);  

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follows:
        - BaudRate = 5250000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 8
		     is: (USART APB Clock / 8) 
			 Example: 
			    - (USART3 APB1 Clock / 8) = (42 MHz / 8) = 5250000 baud
			    - (USART1 APB2 Clock / 8) = (84 MHz / 8) = 10500000 baud
		   - Maximum BaudRate that can be achieved when using the Oversampling by 16
		     is: (USART APB Clock / 16) 
			 Example: (USART3 APB1 Clock / 16) = (42 MHz / 16) = 2625000 baud
			 Example: (USART1 APB2 Clock / 16) = (84 MHz / 16) = 5250000 baud
        - Word Length = 8 Bits
        - one Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */ 
  USART_InitStructure.USART_BaudRate = 57600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStructure);
  
  /* NVIC configuration */
  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(USARTx, ENABLE);
  NVIC_EnableIRQ(USART3_IRQn);
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    return 0;
}

int usart_TxTest()
{
    int idx;
    for(idx=0; idx < txbufsize; idx++) {
        USART_SendData(USART3, txbuf[idx]);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    }
}

void USART3_IRQHandler(void) {
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
    {
        uint8_t data;
        //buffer the data or toss it f there is no room
        //flow control will prevent this
        data = USART_ReceiveData(USART3) & 0xff;
        if(!Enqueue(&rxbuffer, data))
            RxOverflow = 1;
        
    }
    
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET) {
        uint8_t data;
        
        if(Dequeue(&txbuffer, &data)){
            USART_SendData(USART3, data);
        } else {
            //if nothing to send disable interrupt
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
            TxPrimed = 0;
        }
    }
}

int usart_getc(void) 
{       
    uint8_t data;
    while(!Dequeue(&rxbuffer, &data));
    return data;
}

int usart_putc(int c)
{
    while(!Enqueue(&txbuffer, c)); 
    
    if(!TxPrimed) {
        TxPrimed = 1;
        USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    }
    
}

int usart_write_arr(char *p, int len)
{
    int i;
    
    for(i=0; i<len; i++) {
        usart_putc(*p++);
    }
    return len;
}

int usart_read_arr(char *p, int len)
{
    int i = len;

    while(i > 0) {
        *p++ = usart_getc();
        i--;
    }
    return len - i;
}