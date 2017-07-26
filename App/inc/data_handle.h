#ifndef __DATA_HANDLE__
#define __DATA_HANDLE__

#include "stm32f10x.h"

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
}msg_device_info;

typedef struct
{
	char id[MSG_STR_LEN_OF_HEADER+1];
	char cmd[MSG_STR_LEN_OF_ID+1];	
	char length[MSG_STR_LEN_OF_LENGTH+1];
	char seq[MSG_STR_LEN_OF_SEQ+1];
	char dup[MSG_STR_LEN_OF_DUP+1];
	char device[MSG_STR_LEN_OF_DEVICE+1];
}msg_server_info;

void cmd_handle(void);
void frame_data_parse(void);
void write_cmd_handle(void);


#endif
