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
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>

/* Exported variables	  --------------------------------------------------------*/
RTOSInstance RTOS;
/* private variables	  --------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId CommunicationTaskHandle;

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);
void StartCommunicationTask(void const * argument);

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

   osThreadDef(CommunicationTask, StartCommunicationTask, osPriorityAboveNormal, 0, 512);
   CommunicationTaskHandle = osThreadCreate(osThread(CommunicationTask), NULL);


   /* Start scheduler */
   osKernelStart();
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


void StartCommunicationTask(void const * argument)
{
  /* init code for FATFS */
  char LoopString1[15] = "I'm Krakoski!";
  char LoopString2[15] = "Hey! Woman ;)";
  char KrakoskiAnswer[8] = "Hello!\n";
  char Question[10];
  char *CurrentString = LoopString2;
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
	if (USBObj.Available() > 5)
	{
		USBObj.Read(Question, USBObj.Available());
		if (strcmp(Question, "Hello!\n") != 0)
		{
			USBObj.Write(KrakoskiAnswer, 8);
			memset(Question, 0, 10);
		}
	}
	else
	{
		if (USBObj.Println(CurrentString) != 0)
		{
			if(CurrentString == LoopString2)
			{
				CurrentString = LoopString1;
			}
			else
			{
				CurrentString = LoopString2;
			}
		}
	}
    osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}
