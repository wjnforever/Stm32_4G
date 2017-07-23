
/* Includes ------------------------------------------------------------------*/
#include "data_handle.h"
#include "stm32f10x.h"
#include "queue.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include "flash.h"

extern CycQueue *q;

volatile uint8_t offset = 0;
volatile uint8_t rx_index = 0;
uint8_t rx_frame_len = 0;
uint8_t frame_data_len = 0;
uint8_t uart_rx_buf[255] = {0};
uint8_t data_handle_buf[50] = {0};
/*
 *
 * 将串口接收到的数据分为一帧一帧的
 *
 */
void frame_data_prase(void)
{
	while( (rx_index < 255) && (CycQueueIsEmpty(q) == 0 ) ) // CycQueueIsEmpty() return true when queue is empty.
	{

		uint8_t ch = CycQueueOut(q);
		uart_rx_buf[rx_index++] = ch;
		printf("%x ",ch);
		
	}
	
	if(rx_index <= PROTOCOL_FIXED_LENGTH )
	{
		return;
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
		printf("recvSum: %x\n",recvSum);
		uint8_t sum = get_check_sum((unsigned char *)&uart_rx_buf[offset],rx_frame_len - 1);
		printf("sum: %x\n",sum);
		
		//
		if(sum != recvSum)
		{
		  printf("check sum fail\n");
		  //
		  offset += 2;
		  continue;
		}
		

		memcpy(data_handle_buf,&uart_rx_buf[offset],rx_frame_len);
		
		cmd_handle();
		
		printf("one frame parse over\n");

		offset += rx_frame_len;
		
		printf("offset: %d\n",offset);
			
	}//end while
		
	rx_index -= offset;
	  
	printf("rx_in: %d\n",rx_index);
	
	if(rx_index > 0)
	{
		memcpy(uart_rx_buf,&uart_rx_buf[offset],rx_index);
	}

	
	offset = 0;
	rx_frame_len = 0;
	
}

/*
 * 命令处理
 *
 */
void cmd_handle(void)
{

	switch(data_handle_buf[CMD])
	{
	
		case READ:
			
			//read_cmd_handle();
		
		break;
		
		case WRITE:
			
			write_cmd_handle();
		
		break;
		
		default:
			
		break;
		
	}

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

