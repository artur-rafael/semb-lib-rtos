#include "tmp101RTOS.h"

/***************************** Global Variables *****************************/

/*************************** Functions Signatures ***************************/

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void TMP101RTOS_Init(void) {
    if(!I2CRTOS_SemaphoreTake())
        return;
    TMP101_Init();
    I2CRTOS_SemaphoreGive();
} /* TMP101RTOS_Init() */

float TMP101RTOS_GetTemperature(void) {
    if(!I2CRTOS_SemaphoreTake())
        return TMP101RTOS_ERROR_VALUE;
    float temp = TMP101_GetTemperature();
    I2CRTOS_SemaphoreGive();
    return temp;
} /* TMP101RTOS_GetTemperature() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/
