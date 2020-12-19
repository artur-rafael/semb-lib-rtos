#ifndef __I2CRTOS_H__
#define __I2CRTOS_H__

#include "stdbool.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "i2c.h"

#define I2CRTOS_TIMEOUT 1000

bool I2CRTOS_Init(I2C_Module module);

bool I2CRTOS_SemaphoreTake(void);
void I2CRTOS_SemaphoreGive(void);

void I2CRTOS_Transfer(I2C_Module module, uint8_t slaveAddress, uint8_t * tx, size_t txSize, uint8_t * rx, size_t rxSize);

#endif /* __I2CRTOS_H__ */
