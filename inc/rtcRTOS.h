#ifndef __RTC_RTOS_H__
#define __RTC_RTOS_H__

#include <stdbool.h>
#include <time.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "rtc.h"

#define RTCRTOS_TIMEOUT 1000

bool RTCRTOS_Init(void);

void RTCRTOS_SetDateAndTime(struct tm * dtTm);
struct tm * RTCRTOS_GetDateAndTime(void);

void RTCRTOS_SetSeconds(time_t seconds);
time_t RTCRTOS_GetSeconds(void);


#endif /* __RTC_RTOS_H__ */
