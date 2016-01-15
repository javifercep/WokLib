/**
  ******************************************************************************
  * @file    RTOS.c
  * @brief   This file contains GPIO API for the general purpose inputs outputs
  * 	     available on board.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "GPIO/GPIO.h"
#include "LEDS/LEDS.h"
#include "stm32f2xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* Exported variables	  --------------------------------------------------------*/
RTOSInstance RTOS;
/* private variables	  --------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);

/* private class functions -------------------------------------------------------*/


RTOSInstance::RTOSInstance(void)
{
}

RTOSInstance::~RTOSInstance(void)
{
}

void RTOSInstance::Initialization(void)
{
   osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
   defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

   /* Start scheduler */
   osKernelStart(NULL, NULL);
}

void StartDefaultTask(void const * argument)
{
  /* init code for FATFS */

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	GPIO.Toggle(LED1);
	GPIO.Toggle(LED2);
	LEDS.Toggle(LED3);
	LEDS.Toggle(LED4);
    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}
