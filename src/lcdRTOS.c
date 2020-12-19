#include "lcdRTOS.h"

/***************************** Global Variables *****************************/

static QueueHandle_t xLcdQueue = NULL;

/*************************** Functions Signatures ***************************/

static void LCDRTOS_Task(void * pvParameters);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

bool LCDRTOS_Init(void) {
    return xTaskCreate(LCDRTOS_Task, "LcdTask", LCD_RTOS_STACK_SIZE, NULL, LCD_RTOS_TASK_PRIORITY, NULL) == pdPASS;
} /* LDCRTOS_Init() */

void LCDRTOS_WriteChar(char ch) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;

    cmd->id = WRITE_CHAR;
    cmd->ch = ch;

    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_WriteChar() */

void LCDRTOS_WriteString(char * str) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;

    cmd->id = WRITE_STRING;
    cmd->str = str;

    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_WriteString() */

void LCDRTOS_Printf(char * fmt, ...) {
    if(!xLcdQueue)
        return;

    va_list arg;
    va_start(arg, fmt);

    char * buffer = pvPortMalloc(LCD_DISPLAY_SIZE);
    uvsnprintf(buffer, LCD_DISPLAY_SIZE + 1, fmt, arg);

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = PRINTF;
    cmd->str = buffer;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Printf() */

void LCDRTOS_CenteredPrintf(char * fmt, ...) {
    if(!xLcdQueue)
        return;

    va_list arg;
    va_start(arg, fmt);

    char * buffer = pvPortMalloc(LCD_DISPLAY_SIZE);
    uvsnprintf(buffer, LCD_DISPLAY_SIZE + 1, fmt, arg);

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;

    cmd->id = CENTERED_PRINTF;
    cmd->centeredPrintf.str = buffer;
    cmd->centeredPrintf.ddram = (LCD_DISPLAY_SIZE - ustrlen(buffer))/2;

    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_CenteredPrintf() */

void LCDRTOS_Clear(void) {
    if(!xLcdQueue)
        return;
    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = CLEAR;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Clear() */

void LCDRTOS_Home(void) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = HOME;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Home() */

void LCDRTOS_Display(LCD_DisplayState display) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = DISPLAY;
    cmd->display = display;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Display() */

void LCDRTOS_Cursor(LCD_CursorState cursor) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = CURSOR;
    cmd->cursor = cursor;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Cursor() */

void LCDRTOS_Blink(LCD_BlinkState blink) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = BLINK;
    cmd->blink = blink;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_Blink() */

void LCDRTOS_SetCursor(uint8_t ddram) {
    if(!xLcdQueue)
        return;

    struct LCDRTOS_Commands * cmd = pvPortMalloc(sizeof(LCDRTOS_commands));
    if(!cmd)
        return;
    cmd->id = SET_CURSOR;
    cmd->ddram = ddram;
    xQueueSend(xLcdQueue, &cmd, LCD_RTOS_WAITING_TICKS);
} /* LCDRTOS_SetCursor() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static void LCDRTOS_Task(void * pvParameters) {
    xLcdQueue = xQueueCreate(LCD_RTOS_QUEUE_SIZE, sizeof(LCDRTOS_commands *));
    vQueueAddToRegistry(xLcdQueue, "LcdQueue");

    LCD_Init();

    struct LCDRTOS_Commands * cmd;

    while(true) {
        if(xQueueReceive(xLcdQueue, &cmd, portMAX_DELAY) == pdPASS) {
            switch(cmd->id) {
                case WRITE_CHAR:
                    LCD_WriteChar(cmd->ch);
                    break;
                case WRITE_STRING:
                    LCD_WriteString(cmd->str);
                    break;
                case PRINTF:
                    LCD_WriteString(cmd->str);
                    vPortFree(cmd->str);
                    break;
                case CENTERED_PRINTF:
                    LCD_SetCursor(cmd->centeredPrintf.ddram);
                    LCD_WriteString(cmd->centeredPrintf.str);
                    vPortFree(cmd->centeredPrintf.str);
                    break;
                case CLEAR:
                    LCD_Clear();
                    break;
                case HOME:
                    LCD_Home();
                    break;
                case DISPLAY:
                    LCD_Display(cmd->display);
                    break;
                case CURSOR:
                    LCD_Cursor(cmd->cursor);
                    break;
                case BLINK:
                    LCD_Blink(cmd->blink);
                    break;
                case SET_CURSOR:
                    LCD_SetCursor(cmd->ddram);
                    break;
            }
            vPortFree(cmd);
        }
    }
} /* LCDRTOS_Task() */
