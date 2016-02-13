/**
  ******************************************************************************
  * @file    USB.c
  * @brief   This file contains USB API for communicate the board with a PC.
  * 		 This USB implements the standard VCP from STmicroelectronics.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "USB.h"
#include "TOOLS/BufferFunctions.h"
#include "FreeRTOS.h"

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include <stdio.h>
#include <string.h>

/* private defines	  ------------------------------------------------------------*/

/* private variables	  --------------------------------------------------------*/
extern Queue USBRxQueue;

USBInstance USBObj;
USBD_HandleTypeDef hUsbDeviceFS;

/* private variables	  --------------------------------------------------------*/
/* USB Device Core handle declaration */
USBInstance::USBInstance(void)
{

}

USBInstance::~USBInstance(void)
{

}

void USBInstance::Initialization(void)
{
	USBRxQueue.Alloc(2047);
	/* Init Device Library,Add Supported Class and Start the library*/
	USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

	USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);

	USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);

	USBD_Start(&hUsbDeviceFS);
}

void USBInstance::Configuration(unsigned int command, void* arg)
{


}

unsigned int USBInstance::Available(void)
{
	return USBRxQueue.Available(); //UserRxSize;
}

unsigned int USBInstance::Write(char *source, unsigned int size)
{
	char *pTemp = source;
	unsigned int result = size;

	/* wait until the last message has been sent and set the new buffer */
	while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

	return result;
}

unsigned int USBInstance::Read(char *destination, unsigned int size)
{
	unsigned char *pTemp = (unsigned char *)destination;
	unsigned int result = size;

	if (result > USBRxQueue.Available())
	{
		result = USBRxQueue.Available();
	}

	USBRxQueue.ReadToArray(pTemp, result);

	return result;
}

unsigned int USBInstance::Print(char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	pTemp = (char* )pvPortMalloc(strlen(source));

	if(pTemp != NULL)
	{
		strcpy(pTemp, source);

		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int USBInstance::Print(const char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	pTemp = (char* )pvPortMalloc(strlen(source));

	if(pTemp != NULL)
	{
		strcpy(pTemp, source);

		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int USBInstance::Print(int source)
{
	char pTemp[4];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d", source);

	if( size > 0)
	{
		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;

	}

	return result;
}

unsigned int USBInstance::Println(char* source)
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

		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;


		vPortFree(pTemp);
	}

	return result;
}

unsigned int USBInstance::Println(const char* source)
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

		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;


		vPortFree(pTemp);
	}

	return result;
}

unsigned int USBInstance::Println(int source)
{
	char pTemp[6];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d\n", source);

	if(size > 0)
	{
		while (CDC_Transmit_FS((uint8_t *)pTemp, size) != USBD_OK);

		result = size;
	}

	return result;
}

