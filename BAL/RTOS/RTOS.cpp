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
	GPIO.Toggle(PIN3);
	GPIO.Toggle(PIN5);
	LEDS.Toggle(LED3);
	LEDS.Toggle(LED4);

	GPIO.Toggle(PIN0);
	GPIO.Toggle(PIN1);
	GPIO.Toggle(PIN2);
	GPIO.Toggle(PIN4);
	GPIO.Toggle(PIN7);
	GPIO.Toggle(PIN8);

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
	uint8_t ADCChannel = 0;

	ADCObj.Enable(A1);
	ADCObj.Enable(A2);
	ADCObj.Enable(A3);
	ADCObj.Enable(A4);
	ADCObj.Enable(A5);
	ADCObj.Enable(A6);

	/* USER CODE BEGIN StartDefaultTask */
	USBObj.Println(LoopString2);
	USBObj.Println(LoopString1);

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

		USBObj.Println(LoopString1);

		for (ADCChannel = 0; ADCChannel < NUMBER_OF_ADC_CHANNEL; ADCChannel++)
		{
			sprintf(LoopString2, "ADC channel %d: ", ADCChannel);

			USBObj.Print(LoopString2);
			USBObj.Println(ADCObj.Read(ADCChannel));
		}

		osDelay(900);
	}
	/* USER CODE END StartDefaultTask */
}
