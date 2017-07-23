#ifndef __RTC_H__
#define __RTC_H__

#include "stm32f10x.h"




void rtc_init(void);
void RTC_Configuration(void);
void Time_Adjust(void);
void Time_Show(void);
void NVIC_Configuration(void);
void Time_Display(uint32_t TimeVar);

#endif
