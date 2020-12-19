#ifndef __LCD_RTOS_H__
#define __LCD_RTOS_H__

#include <stdbool.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "utils/ustdlib.h"

#include "lcd.h"

#define LCD_RTOS_STACK_SIZE      (configMINIMAL_STACK_SIZE * 2)
#define LCD_RTOS_TASK_PRIORITY   (tskIDLE_PRIORITY + 1)

#define LCD_RTOS_QUEUE_SIZE      10

#define LCD_RTOS_WAITING_TICKS   0

typedef enum {
    WRITE_CHAR,
    WRITE_STRING,
    PRINTF,
    CENTERED_PRINTF,
    CLEAR,
    HOME,
    DISPLAY,
    CURSOR,
    BLINK,
    SET_CURSOR
} LCDRTOS_CommandId;

typedef struct {
    char * str;
    uint8_t ddram;
} LCDTextRTOS_CenteredPrintf;

typedef struct LCDRTOS_Commands {
    LCDRTOS_CommandId id;
    union {
        char ch;
        char * str;
        LCDTextRTOS_CenteredPrintf centeredPrintf;
        LCD_DisplayState display;
        LCD_CursorState cursor;
        LCD_BlinkState blink;
        uint8_t ddram;
    };
} LCDRTOS_commands;

bool LCDRTOS_Init(void);

void LCDRTOS_WriteChar(char ch);
void LCDRTOS_WriteString(char * str);
void LCDRTOS_Printf(char * fmt, ...);
void LCDRTOS_CenteredPrintf(char * fmt, ...);

void LCDRTOS_Clear(void);
void LCDRTOS_Home(void);

void LCDRTOS_Display(LCD_DisplayState display);
void LCDRTOS_Cursor(LCD_CursorState cursor);
void LCDRTOS_Blink(LCD_BlinkState blink);

void LCDRTOS_SetCursor(uint8_t ddram);

#endif /* __LCD_RTOS_H__ */
