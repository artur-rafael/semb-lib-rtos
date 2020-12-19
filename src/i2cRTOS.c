#include "i2cRTOS.h"

/***************************** Global Variables *****************************/

static SemaphoreHandle_t xI2cSemaphore = NULL;

/*************************** Functions Signatures ***************************/

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

bool I2CRTOS_Init(I2C_Module module) {
    if(!(xI2cSemaphore = xSemaphoreCreateMutex()))
        return false;
    I2C_Init(module);
    return true;
} /* I2CRTOS_Init() */

bool I2CRTOS_SemaphoreTake(void) {
    return xSemaphoreTake(xI2cSemaphore, pdMS_TO_TICKS(I2CRTOS_TIMEOUT)) == pdPASS;
} /* I2CRTOS_SemaphoreTake() */

void I2CRTOS_SemaphoreGive(void) {
    xSemaphoreGive(xI2cSemaphore);
} /* I2CRTOS_SemaphoreGive() */

void I2CRTOS_Transfer(I2C_Module module, uint8_t slaveAddress, uint8_t * tx, size_t txSize, uint8_t * rx, size_t rxSize) {
    I2C_Transfer(module, slaveAddress, tx, txSize, rx, rxSize);
} /* I2CRTOS_Transfer() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/
