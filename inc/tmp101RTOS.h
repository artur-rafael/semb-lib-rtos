#ifndef __TMP101RTOS_H__
#define __TMP101RTOS_H__

#include "tmp101.h"

#include "i2cRTOS.h"

#define TMP101RTOS_ERROR_VALUE  0xFFFF

void TMP101RTOS_Init(void);
float TMP101RTOS_GetTemperature(void);

#endif /* __TMP101RTOS_H__ */
