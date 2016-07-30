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
osTimerId BaseTimeHandle;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void BaseTimeCB(void const * argument);

/* Main threads */
osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
osTimerDef(BaseTime, BaseTimeCB);
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
  BaseTimeHandle = osTimerCreate(osTimer(BaseTime), osTimerPeriodic, NULL);

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

 LEDS.Initialization(LED1);
 //LEDS.Initialization(LED2);
 //LEDS.On(LED1);
 //LEDS.Off(LED2);

  /* Infinite loop */
  for (;;)
  {
    LEDS.Toggle(LED1);
    //LEDS.Toggle(LED2);

    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}

/* BaseTimeCB function */
void BaseTimeCB(void const * argument)
{
  /* USER CODE BEGIN BaseTimeCB */

  /* USER CODE END BaseTimeCB */
}
