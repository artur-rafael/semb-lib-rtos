#ifndef __WAIT_RTOS_H__
#define __WAIT_RTOS_H__

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "wait.h"

#define WAITRTOS_TIMEOUT    1000

bool WAITRTOS_Init(void);

void WAITRTOS_ChronoMicro(uint32_t wait);

void WAITRTOS_Ms(uint32_t millis);
uint32_t WAITRTOS_Elapsed(uint32_t time);

#endif /* __WAIT_RTOS_H__ */
