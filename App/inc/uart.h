#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

#define HEAD_FIRST       0
#define HEAD_SECOND      1
#define FRAME_LENGTH     2
#define CMD              3
#define DEVICE_ENDPOINT  4 
#define DATA             5


#define READ             0x00
#define READ_ACK         0x01
#define WRITE						 0x02
#define WRITE_ACK        0x03
#define DATA_UPLOAD      0x05
#define ERROR            0xFF

// 协议帧固定部分
#define MSG_DEVICE_STR_HEADER    "TRVAP"
#define MSG_SERVER_STR_HEADER    "TRVBP"

#define MSG_STR_LEN_OF_HEADER                         5         //strlen("TRVXP")
#define MSG_STR_LEN_OF_ID                                  2         
#define MSG_STR_LEN_OF_LENGTH                         3
#define MSG_STR_LEN_OF_SEQ                               3
#define MSG_STR_LEN_OF_DUP                               2
#define MSG_STR_LEN_OF_DEVICE                          3
#define MSG_STR_LEN_OF_PORTS                           4
#define MSG_STR_LEN_OF_PORTS_PERIOD            (MSG_STR_LEN_OF_PORTS*4)

typedef struct
{
	char id[MSG_STR_LEN_OF_HEADER+1];
	char cmd[MSG_STR_LEN_OF_ID+1];	
	char length[MSG_STR_LEN_OF_LENGTH+1];
	char seq[MSG_STR_LEN_OF_SEQ+1];
	char dup[MSG_STR_LEN_OF_DUP+1];
	char device[MSG_STR_LEN_OF_DEVICE+1];
	char ports[MSG_STR_LEN_OF_PORTS+1];
	char period[MSG_STR_LEN_OF_PORTS_PERIOD+1];
}msg_static_info;

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void data_upload(uint8_t endpoint, uint8_t *data, uint8_t len);
uint8_t get_check_sum(uint8_t *pack, uint8_t pack_len);

#endif
