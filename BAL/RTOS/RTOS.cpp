/**
 ******************************************************************************
 * @file    RTOS.c
 * @brief   This file contains GPIO API for the general purpose inputs outputs
 * 	     available on board.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "stm32f2xx_hal.h"
#include "task.h"
#include <string.h>

/* Exported variables	  --------------------------------------------------------*/
RTOSInstance RTOS;
/* private variables	  --------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);

/* Main threads */
osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);

/* private class functions -------------------------------------------------------*/

RTOSInstance::RTOSInstance(void)
{
}

RTOSInstance::~RTOSInstance(void)
{
}

void RTOSInstance::Initialization(void)
{
  /* Init main and woklib threads */
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* Start scheduler */
  osKernelStart();
}

osThreadId RTOSInstance::CreateTask(const osThreadDef_t *thread_def, void *argument)
{
  return osThreadCreate(thread_def, argument);
}

osStatus RTOSInstance::DeleteTask(osThreadId TaskID)
{
  return osThreadTerminate(TaskID);
}

void StartDefaultTask(void const * argument)
{
  /* init code for FATFS */

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for (;;)
  {
    GPIO.Toggle(PIN3);
    GPIO.Toggle(PIN5);
    LEDS.Toggle(LED3);
    LEDS.Toggle(LED4);

    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}
