#include "waitRTOS.h"

/***************************** Global Variables *****************************/

static SemaphoreHandle_t xWaitSemaphore = NULL;

/*************************** Functions Signatures ***************************/

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

bool WAITRTOS_Init(void) {
    if(!(xWaitSemaphore = xSemaphoreCreateMutex()))
        return false;
    WAIT_Timer0AInit();
    return true;
} /* WAITRTOS_Init() */

void WAITRTOS_ChronoMicro(uint32_t wait) {
    if(xSemaphoreTake(xWaitSemaphore, pdMS_TO_TICKS(WAITRTOS_TIMEOUT)) == pdFAIL)
        return;
    WAIT_ChronoMicro(wait);
    xSemaphoreGive(xWaitSemaphore);
} /* WAITRTOS_ChronoMicro() */

void WAITRTOS_Ms(uint32_t millis) {
    uint32_t start = xTaskGetTickCount();
    while((xTaskGetTickCount() - start) < pdMS_TO_TICKS(millis));
} /* WAITRTOS_Ms() */

uint32_t WAITRTOS_Elapsed(uint32_t time) {
    return (xTaskGetTickCount() - pdMS_TO_TICKS(time)) * portTICK_RATE_MS;
} /* WAITRTOS_Elapsed() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

