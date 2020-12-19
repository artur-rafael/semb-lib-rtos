#include "keypadRTOS.h"

/***************************** Global Variables *****************************/

static QueueHandle_t xKeypadQueue = NULL;

/*************************** Functions Signatures ***************************/

static void KEYPADRTOS_Task(void * pvParameters);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

bool KEYPADRTOS_Init(void) {
    return xTaskCreate(KEYPADRTOS_Task, "KeypadTask", KEYPAD_RTOS_STACK_SIZE, NULL, KEYPAD_RTOS_TASK_PRIORITY, NULL) == pdPASS;
} /* KEYPADRTOS_Init() */

bool KEYPADRTOS_GetEvent(uint32_t * event, TickType_t ticksToWait) {
    if(!xKeypadQueue)
        return false;
    return xQueueReceive(xKeypadQueue, event, ticksToWait) == pdPASS;
    //return (!xKeypadQueue) ? false : xQueueReceive(xKeypadQueue, event, ticksToWait) == pdPASS;
} /* KEYPADRTOS_GetEvent() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static void KEYPADRTOS_Task(void * pvParameters) {
    xKeypadQueue = xQueueCreate(KEYPAD_RTOS_QUEUE_SIZE, sizeof(uint32_t));
    vQueueAddToRegistry(xKeypadQueue, "KeypadQueue");

    KEYPAD_Init();
    uint32_t keypadEvent = KEYPAD_NO_EVENT;

    while(true) {
        if((keypadEvent = KEYPAD_KeyEvent()) != KEYPAD_NO_EVENT)
            xQueueSend(xKeypadQueue, &keypadEvent, KEYPAD_RTOS_WAITING_TICKS);

        vTaskDelay(pdMS_TO_TICKS(KEYPAD_RTOS_TASK_DELAY));
    }
} /* KEYPADRTOS_Task() */
