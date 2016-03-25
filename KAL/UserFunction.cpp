/**
 ******************************************************************************
 * @file    UserFunction.cPP
 * @brief   This file contains Kodillo API.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "ESP8266/ESP8266.h"

/* Private variables ---------------------------------------------------------*/
osThreadId UserTaskID;

/* Private function prototypes -----------------------------------------------*/
static void UserTask(void const * argument);

/* Create a new task reference */
NewTask(UserTask);

void UserFunctionSetup(void)
{
  UserTaskID = RTOS.CreateTask(TaskRef(UserTask), NULL);
}

static void UserTask(void const * argument)
{
  char command;
  char Test[6] = "Test\n";
  unsigned int size;

  ESP8266.Initialization();

  /* Initialize board LEDs for debug purpose */
  GPIO.Mode(PIN3, OUTPUT_PULLUP);
  GPIO.Mode(PIN5, OUTPUT_PULLUP);
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  /* Set the initial value of the board LEDs */
  GPIO.Write(PIN3, HIGH);
  GPIO.Write(PIN5, LOW);
  LEDS.On(LED3);
  LEDS.Off(LED4);

  /* Infinite loop */
  for (;;)
  {
    /* USB to UART converter */
    size = USBObj.Available();
    if (size > 0)
    {
      USBObj.Read(&command, 1);
      switch (command)
      {
        case 'c':
          ESP8266.StartConfigMode();
          break;
        case 'o':
          ESP8266.StopConfigMode();
          break;
        case 'a':
          break;
        case 't':
          USBObj.Println(Test);
          break;
        default:
          break;
      }
    }
    osDelay(100);
  }
}

