#ifndef _TIMER_H
#define _TIMER_H
#include "device.h"
#include "stm32f10x.h"
#include "misc.h"

//���������������ķ��ͼ������λ�Ƿ��ӣ�
//����������������1���ӵ�10����
#define TIME_HEART 1
#define NUMBER_TIME_HEART_50_MS (TIME_HEART*60*1000/50)  	  //1MIN
#define HB_1_MIN (TIME_HEART*60)  	  //1MIN

#define NUMBER_TIMER_1_MINUTE       60
#define NUMBER_MSG_MAX_RETRY        5

#define OFFSET_Connec 30                      	//TRVBP00,000,UBICOM_AUTH_INFOR,0001,070,X,# 
#define OFFSET_TDS    35                      	//TRVBP00,000,UBICOM_AUTH_INFOR,0001,070,X,# 


void TIM6_Int_Init(u16 arr,u16 psc);

#endif
