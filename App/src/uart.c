
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "uart.h"
#include <stdio.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void uart1_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1 

}
/**
  * @brief  uart2 init for 
  * @param  None
  * @retval None
  */
void uart2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef Usart_InitStr;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// configure clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
	USART_DeInit(USART2);
	
	
	/* Configure USART2 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	// uart configure
	Usart_InitStr.USART_BaudRate			     	= bound;
	Usart_InitStr.USART_WordLength					= USART_WordLength_8b;
	Usart_InitStr.USART_StopBits						= USART_StopBits_1;
	Usart_InitStr.USART_Parity							= USART_Parity_No;
	Usart_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	Usart_InitStr.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &Usart_InitStr);
	
	NVIC_InitStructure.NVIC_IRQChannel					          = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0x00;	
	NVIC_InitStructure.NVIC_IRQChannelCmd					        = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  uart3 is used to print log
  * @param  None
  * @retval None
  */
void uart3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef Usart_InitStr;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// configure clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
	USART_DeInit(USART3);
	
	
	/* Configure USART3 Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	/* Configure USART3 Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	// uart configure
	Usart_InitStr.USART_BaudRate			     	= bound;
	Usart_InitStr.USART_WordLength					= USART_WordLength_8b;
	Usart_InitStr.USART_StopBits						= USART_StopBits_1;
	Usart_InitStr.USART_Parity							= USART_Parity_No;
	Usart_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
	Usart_InitStr.USART_Mode								= USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &Usart_InitStr);
	
	NVIC_InitStructure.NVIC_IRQChannel					          = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority	= 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0x01;	
	NVIC_InitStructure.NVIC_IRQChannelCmd					        = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART3, ENABLE);
}

/*
 * upload data
 *
 */ 
void data_upload(uint8_t endpoint, uint8_t *data, uint8_t len)
{
	uint8_t i = 0;
	uint8_t temp_buf[100] = {0};
	uint8_t frame_length = PROTOCOL_FIXED_LENGTH + len;
	
	temp_buf[0] = 0x5A;
	USART_SendData(USART2, (uint8_t) 0x5A); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	
	temp_buf[1] = 0xA5;
	USART_SendData(USART2, (uint8_t) 0xA5); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	
	temp_buf[2] = frame_length;
	USART_SendData(USART2, (uint8_t) frame_length); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	
	temp_buf[3] = DATA_UPLOAD;
	USART_SendData(USART2, (uint8_t) DATA_UPLOAD); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}	
		
	temp_buf[4] =	endpoint;
	USART_SendData(USART2, (uint8_t) endpoint); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	
	for(i=0;i<len;i++)
	{
		temp_buf[5+i] = data[i];
		USART_SendData(USART2, data[i]); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	}
	
	USART_SendData(USART2, get_check_sum(temp_buf,frame_length-1)); while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	
}


/*******************************************************************************
 * FunctionName: get_check_sum
 * Description : calculator check sum
 * Parameters  : pack 
 *               pack_len 
 * Returns     : check sum
 *
 *******************************************************************************/
uint8_t get_check_sum(uint8_t *pack, uint8_t pack_len)
{
  uint8_t i;
  uint8_t check_sum = 0;
  
  for(i = 0; i < pack_len; i ++)
  {
    check_sum += *(pack++);
  }
  
  return check_sum;
}



/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART3, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
  {}

  return ch;
}

