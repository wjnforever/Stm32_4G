#ifndef __USART_H__
#define __USART_H__

#include "stm32f10x.h"

#define LOG_ENABLE
#ifdef LOG_ENABLE
/* ���������ڵ��Խ׶��Ŵ� */
#define BSP_Printf		printf
#else
#define BSP_Printf(...)
#endif

void usart1_init(u32 bound);

#endif
