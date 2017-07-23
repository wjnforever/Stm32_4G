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

// Э��֡�̶����ֳ���
#define PROTOCOL_FIXED_LENGTH    6

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void data_upload(uint8_t endpoint, uint8_t *data, uint8_t len);
uint8_t get_check_sum(uint8_t *pack, uint8_t pack_len);

#endif
