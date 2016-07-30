/**
 ******************************************************************************
 * @file    UserFunction.cPP
 * @brief   This file contains Kodillo API.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "ESP8266/ESP8266.h"
#include "TLC5940/TLC5940.h"
#include "stdlib.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
osThreadId UserTaskID;

/* Private function prototypes -----------------------------------------------*/
static void UserLoopTask(void const * argument);

/* Create a new task reference */
ExtendedNewTask(UserLoopTask, osPriorityNormal, 0, 1024)

void UserSetupTask(void)
{
  UserTaskID = RTOS.CreateTask(TaskRef(UserLoopTask), NULL);
}

static void UserLoopTask(void const * argument)
{

  /* Initialize board LEDs for debug purpose */
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  /* Set the initial value of the board LEDs */
  LEDS.Off(LED3);
  LEDS.On(LED4);

  /* Infinite loop */
  for (;;)
  {
    osDelay(1000);
    USBObj.Println("Hello!");
    LEDS.Toggle(LED3);
    LEDS.Toggle(LED4);
  }
}

