/**
  ******************************************************************************
  * @file    ESP8266.cpp
  * @brief   This file contains ESP8266 API.
  *******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "ESP8266/ESP8266.h"

#include <stdio.h>
#include <string.h>

/* Global variables ----------------------------------------------------------*/
ESP8266Instance ESP8266;

/* Private variables ---------------------------------------------------------*/
osThreadId ESP8266ConfigTaskID;

/* Private function prototypes -----------------------------------------------*/
static void ESP8266ConfigTask(void const * argument);

/* Create a new task reference */
NewTask(ESP8266ConfigTask);

/* Private function **********************************************************/
/**
  * @brief  Initializes Tibuboard LEDs and Buttons.
  * @param  None
  * @retval None
  */
ESP8266Instance::ESP8266Instance(void)
{

}

ESP8266Instance::~ESP8266Instance(void)
{

}

void ESP8266Instance::Initialization()
{
	/* Set the ESP8266 reset to low to disable the ESP */
	GPIO.Mode(ESP_RST, OUTPUT_OPENDRAIN);
	GPIO.Write(ESP_RST, LOW);

	/* Set the GPIO0, GPIO2 and CE pins in order to enter in normal boot */
	GPIO.Mode(ESP_GPIO0, INPUT_PULLUP);
	GPIO.Mode(ESP_GPIO0, INPUT_PULLUP);
	GPIO.Mode(ESP_CE, OUTPUT_PULLUP);
	GPIO.Write(ESP_CE, HIGH);

	/* Release the reset to initialize the ESP */
	GPIO.Write(ESP_RST, HIGH);

	/* Wait for ESP initialization */
	HAL_Delay(1000);
	/* Initialize USART module */
	USARTInst.Initialization(ESP_USART, ESP_BAUDRATE);

}

void ESP8266Instance::StartConfigMode(void)
{
  ESP8266ConfigTaskID = RTOS.CreateTask(TaskRef(ESP8266ConfigTask),NULL);
}

void ESP8266Instance::StopConfigMode(void)
{
  RTOS.DeleteTask(ESP8266ConfigTaskID);
}

unsigned int ESP8266Instance::Available(void)
{
	return USARTInst.Available();
}

unsigned int ESP8266Instance::Write(char *source, unsigned int size)
{
	char *pTemp = source;

	USARTInst.Write(pTemp, size);

	return size;
}

unsigned int ESP8266Instance::Read(char *destination, unsigned int size)
{
	char *pTemp = destination;
	unsigned int result = size;

	if (result > USARTInst.Available())
	{
		result = USARTInst.Available();
	}

	USARTInst.Read(pTemp, result);

	return result;
}

unsigned int ESP8266Instance::Print(char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	pTemp = (char* )pvPortMalloc(strlen(source));

	if(pTemp != NULL)
	{
		strcpy(pTemp, source);

		this->Write(pTemp, size);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int ESP8266Instance::Print(int source)
{
	char pTemp[4];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d", source);

	if( size > 0)
	{
		this->Write(pTemp, size);

		result = size;

	}

	return result;
}

unsigned int ESP8266Instance::Println(char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = 0;

	pTemp = (char *) pvPortMalloc(strlen(source) + 2);

	if (pTemp != NULL)
	{
		strcpy(pTemp, source);
		strcat(pTemp, "\n");

		size = strlen(pTemp);

		this->Write(pTemp, size);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int ESP8266Instance::Println(int source)
{
	char pTemp[6];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d\n", source);

	if(size > 0)
	{
		this->Write(pTemp, size);

		result = size;
	}

	return result;
}


static void ESP8266ConfigTask(void const * argument)
{
  char Question1[64];
  char Question2[64];
  unsigned int size;

  /* Infinite loop */
   for (;;)
   {
     /* USB to UART converter */
     size = USBObj.Available();
     if (size > 0)
     {
       USBObj.Read(Question1, size);
       USARTObj1.Write(Question1, size);
     }

     size = USARTObj1.Available();
     if (size > 0)
     {
       USARTObj1.Read(Question2, size);
       USBObj.Write(Question2, size);
     }

     osDelay(10);
   }
}

