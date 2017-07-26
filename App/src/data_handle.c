
/* Includes ------------------------------------------------------------------*/
#include "data_handle.h"
#include "stm32f10x.h"
#include "queue.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "flash.h"

extern CycQueue *q;

#define UART_MAX_RECV_LEN		256					//最大接收缓存字节数

//volatile uint8_t offset = 0;
//volatile uint8_t rx_index = 0;
uint8_t rx_frame_len = 0;
uint8_t frame_data_len = 0;
uint8_t uart_rx_buf[UART_MAX_RECV_LEN] = {0};
uint8_t data_handle_buf[50] = {0};

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

/*
 *
 * 将串口接收到的数据分为一帧一帧的
 *
 */
void frame_data_parse(void)
{
#if 1
	u16 length = 0; 
	u8 result = 0;
	u8 result_temp = 0;
	char *uart_data_left;
	char *p, *p1;
	char *p_temp = NULL;		
	
	strcpy(uart_rx_buf, USART3_RX_BUF);
	Clear_USART3();
	uart_data_left = (char *)uart_rx_buf;
	while((p=strstr(uart_data_left, MSG_SERVER_STR_HEADER))!=NULL)
	{
		if((p1=strstr((const char*)p,"#"))!=NULL)
		{
			//调用异或和函数来校验回文	
			length = p1 - p +1;
			//校验数据
			result = get_check_sum((char *)(p),length-5);
			BSP_Printf("result:%d\r\n",result);
			
			//取字符串中的校验值,校验值转化为数字，并打印
			result_temp = atoi((const char *)(p+length-5));	
			BSP_Printf("result_temp:%d\r\n",result_temp);
			
			//回文正确
			if(result == result_temp)
			{
				msg_server_info *pMsg=(msg_server_info *)p;
				u8 cmd=atoi(pMsg->cmd);
				if(atoi(pMsg->cmd)				
				if((p_temp+(MSG_STR_LEN_OF_SEQ+1)) < p1)
				{
					//BSP_Printf("seq:%d %d\r\n",dev.msg_seq, atoi(p_temp));
					if(msg_wait_check == MSG_STR_ID_OPEN)
					{
						BSP_Printf("Recv Seq:%d Msg:%d from Server\n", atoi(p_temp), msg_wait_check);
						dev.msg_seq_s = atoi(p_temp);
						Reset_Device_Status(CMD_OPEN_DEVICE);
						strncpy(dev.device_on_cmd_string, p, p1 - p +1);
						break;
					}
					else if((msg_wait_check == MSG_STR_ID_LOGIN) || (msg_wait_check == MSG_STR_ID_HB) || 
							(msg_wait_check == MSG_STR_ID_CLOSE))
					{
						if(atoi(p_temp) == dev.msg_seq)
						{
							BSP_Printf("Recv Seq:%d Msg:%d from Server\n", dev.msg_seq, msg_wait_check);
							Reset_Device_Status(CMD_TO_IDLE);
							break;							
						}
					}
				}
			}
			uart_data_left = p1;
		}
		else
			break;
	}			
#else
	char *uart_data_left, *p, *p1;
	char *p_temp = NULL;	
	u16 length = 0; 	
	if( (rx_index < UART_MAX_RECV_LEN) && (CycQueueIsEmpty(q) == 0 ) ) // CycQueueIsEmpty() return true when queue is empty.
	{
		uint8_t ch = CycQueueOut(q);
		uart_rx_buf[rx_index++] = ch;	
	}

	if(rx_index <= MSG_STR_LEN_OF_HEADER )
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

