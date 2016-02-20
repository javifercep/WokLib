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

   osThreadDef(CommunicationTask, StartCommunicationTask, osPriorityAboveNormal, 0, 1024);
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
	GPIO.Toggle(PIN3);
	GPIO.Toggle(PIN5);
	LEDS.Toggle(LED3);
	LEDS.Toggle(LED4);

    osDelay(500);
  }
  /* USER CODE END StartDefaultTask */
}


void StartCommunicationTask(void const * argument)
{
	char Question1[64];
	char Question2[255];
	unsigned int size;

	/* Wait for the ESP initialization before reading data
	 * from UART
	 */
	osDelay(1000);
	USART.Initialization();

	/* Infinite loop */
	for(;;)
	{
		/* USB to UART converter */
		size = USBObj.Available();
		if (size > 0)
		{
			USBObj.Read(Question1,size);
			USART.Write(Question1,size);
		}

		size = USART.Available();
		if (size > 0)
		{
			USART.Read(Question2,size);
			USBObj.Write(Question2,size);
		}

		osDelay(100);
	}
	/* USER CODE END StartDefaultTask */
}
