#ifndef __KEYPAD_RTOS_H__
#define __KEYPAD_RTOS_H__

#include <stdint.h>
#include <stdbool.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "keypad.h"

#define KEYPAD_RTOS_STACK_SIZE      (configMINIMAL_STACK_SIZE * 2)
#define KEYPAD_RTOS_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)

#define KEYPAD_RTOS_QUEUE_SIZE      10
#define KEYPAD_RTOS_TASK_DELAY      50

#define KEYPAD_RTOS_WAITING_TICKS   0

bool KEYPADRTOS_Init(void);
bool KEYPADRTOS_GetEvent(uint32_t * event, TickType_t ticksToWait);

#endif /* __KEYPAD_RTOS_H__ */
