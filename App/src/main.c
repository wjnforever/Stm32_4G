
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "usart.h"
#include "usart3.h"
#include "systick.h"
#include <stdio.h>
#include "data_handle.h"
#include "queue.h"
#include "delay.h"
#include "rtc.h"
#include "timer.h"

/* Private function prototypes -----------------------------------------------*/
static void test_io(void);


/* Global variables ---------------------------------------------------------*/
CycQueue *q = NULL; 
extern __IO uint32_t TimeDisplay;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

	q = CycQueueInit();
	
	if(q == NULL)
	{
		//BSP_Printf("malloc error!\n");
	}
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(72);
	usart1_init(115200);
	usart3_init(115200);
	rtc_init();
	
	TIM6_Int_Init(9999,2399);						     // 1sÖÐ¶Ï
	TIM_SetCounter(TIM6,0); 
	TIM_Cmd(TIM6,ENABLE);	
	
	while(1)
	{
#if 0	
		unsigned long t = millis();
		if ((t - lastInActivity > MQTT_KEEPALIVE*1000UL) || (t - lastOutActivity > MQTT_KEEPALIVE*1000UL)) {
			if (pingOutstanding) {
				this->_state = MQTT_CONNECTION_TIMEOUT;
				_client->stop();
				return false;
			} else {
				buffer[0] = MQTTPINGREQ;
				buffer[1] = 0;
				_client->write(buffer,2);
				lastOutActivity = t;
				lastInActivity = t;
				pingOutstanding = true;
			}
		}	
#endif		
		frame_data_parse();
		//delay_ms(1000);

		/* If 1s has been elapsed */
		if (TimeDisplay == 1)
		{
			BSP_Printf("\n\r");
			/* Display current time */
			Time_Display(RTC_GetCounter());
			TimeDisplay = 0;
		}
	}
}


/**
  * @brief  test io
  * @param  None
  * @retval None
  */
static void test_io(void)
{

	GPIO_InitTypeDef Gpio_InitStr;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	Gpio_InitStr.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	Gpio_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;
	Gpio_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio_InitStr);
	
	Gpio_InitStr.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &Gpio_InitStr);

	GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	
	//GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
	//GPIO_SetBits(GPIOC,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);

}


