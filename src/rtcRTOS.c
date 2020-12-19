#include "rtcRTOS.h"

/***************************** Global Variables *****************************/

static SemaphoreHandle_t xRtcSemaphore = NULL;

/*************************** Functions Signatures ***************************/

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

bool RTCRTOS_Init(void) {
    if(!(xRtcSemaphore = xSemaphoreCreateMutex()))
        return false;
    RTC_Init();
    return true;
} /* RTCRTOS_Init() */

void RTCRTOS_SetDateAndTime(struct tm * dtTm) {
    if(xSemaphoreTake(xRtcSemaphore, pdMS_TO_TICKS(RTCRTOS_TIMEOUT)) == pdFAIL)
        return;
    RTC_SetDateAndTime(dtTm);
    xSemaphoreGive(xRtcSemaphore);
} /* RTCRTOS_SetDateAndTime() */

struct tm * RTCRTOS_GetDateAndTime(void) {
    if(xSemaphoreTake(xRtcSemaphore, pdMS_TO_TICKS(RTCRTOS_TIMEOUT)) == pdFAIL)
        return NULL;
    struct tm * dtTm = RTC_GetDateAndTime();
    xSemaphoreGive(xRtcSemaphore);
    return dtTm;
} /* RTCRTOS_GetDateAndTime() */

void RTCRTOS_SetSeconds(time_t seconds) {
    if(xSemaphoreTake(xRtcSemaphore, pdMS_TO_TICKS(RTCRTOS_TIMEOUT)) == pdFAIL)
        return;
    RTC_SetSeconds(seconds);
    xSemaphoreGive(xRtcSemaphore);
} /* RTCRTOS_SetSeconds() */

time_t RTCRTOS_GetSeconds(void) {
    if(xSemaphoreTake(xRtcSemaphore, pdMS_TO_TICKS(RTCRTOS_TIMEOUT)) == pdFAIL)
        return (time_t) -1;
    time_t time = RTC_GetSeconds();
    xSemaphoreGive(xRtcSemaphore);
    return time;
} /* RTCRTOS_GetSeconds() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/
