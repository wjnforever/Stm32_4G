
/* Includes ------------------------------------------------------------------*/
#include "data_handle.h"
#include "stm32f10x.h"
#include "queue.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "flash.h"

extern CycQueue *q;

#define UART_MAX_RECV_LEN		255					//最大接收缓存字节数

volatile uint8_t offset = 0;
volatile uint8_t rx_index = 0;
uint8_t rx_frame_len = 0;
uint8_t frame_data_len = 0;
uint8_t uart_rx_buf[UART_MAX_RECV_LEN+1] = {0};
uint8_t data_handle_buf[50] = {0};
/*
 *
 * 将串口接收到的数据分为一帧一帧的
 *
 */
void frame_data_parse(void)
{
	char *uart_data_left, *p, *p1;
	char *p_temp = NULL;	
	u16 length = 0; 	
	if( (rx_index < UART_MAX_RECV_LEN) && (CycQueueIsEmpty(q) == 0 ) ) // CycQueueIsEmpty() return true when queue is empty.
	{
		uint8_t ch = CycQueueOut(q);
		uart_rx_buf[rx_index++] = ch;	
	}

	uart_rx_buf[rx_index]=0;

	if(rx_index <= MSG_STR_LEN_OF_HEADER )
	{
		return;
	}

#if 0	
	uart_data_left = &uart_rx_buf[offset];
	while((p=strstr(uart_data_left, MSG_SERVER_STR_HEADER))!=NULL)
	{
		if((p1=strstr((const char*)p,"#"))!=NULL)
		{
			//调用异或和函数来校验回文	
			length = p1 - p +1;
			//校验数据
			uint8_t sum = get_check_sum((unsigned char *)p,length-5);			
			BSP_Printf("sum:%d\r\n",sum);
			
			//取字符串中的校验值,校验值转化为数字，并打印
			uint8_t sum_field = atoi((const char *)(p+length-5));	
			BSP_Printf("sum_field:%d\r\n",sum_field);
			
			//回文正确
			if(sum == sum_field)
			{
				memcpy(data_handle_buf, p, length);
				
				cmd_handle();
			}
			uart_data_left = p1;
		}
		else
			break;
	}
	

	
	while((rx_index - offset) >  PROTOCOL_FIXED_LENGTH)
	{
 
		if(uart_rx_buf[offset + HEAD_FIRST] != 0x5A)
		{
		  offset ++;
		  continue;
		}
		
		if(uart_rx_buf[offset + HEAD_SECOND] != 0xA5)
		{
		  offset ++;
		  continue;
		}      

		rx_frame_len = uart_rx_buf[offset + FRAME_LENGTH];
		
		// 
		frame_data_len = rx_frame_len - PROTOCOL_FIXED_LENGTH;
		
		//
		if( (rx_frame_len > 249) && (rx_frame_len == 0) )
		{
			offset += 2;
			continue;
		}

		if(( rx_index < (rx_frame_len + offset) ) || ( (rx_frame_len + offset) < 1))
		{
			break;
		}
		
		uint8_t recvSum = uart_rx_buf[offset + rx_frame_len - 1];
		BSP_Printf("recvSum: %x\n",recvSum);
		uint8_t sum = get_check_sum((unsigned char *)&uart_rx_buf[offset],rx_frame_len - 1);
		BSP_Printf("sum: %x\n",sum);
		
		//
		if(sum != recvSum)
		{
		  BSP_Printf("check sum fail\n");
		  //
		  offset += 2;
		  continue;
		}
		

		memcpy(data_handle_buf,&uart_rx_buf[offset],rx_frame_len);
		
		cmd_handle();
		
		BSP_Printf("one frame parse over\n");

		offset += rx_frame_len;
		
		BSP_Printf("offset: %d\n",offset);
			
	}//end while
		
	rx_index -= offset;
	  
	BSP_Printf("rx_in: %d\n",rx_index);
	
	if(rx_index > 0)
	{
		memcpy(uart_rx_buf,&uart_rx_buf[offset],rx_index);
	}

	
	offset = 0;
	rx_frame_len = 0;
#endif	
}

/*
 * 命令处理
 *
 */
void cmd_handle(void)
{


}




void write_cmd_handle(void)
{

}


/*
 * send ack
 *
 */
void send_ack(void)
{


	
}

