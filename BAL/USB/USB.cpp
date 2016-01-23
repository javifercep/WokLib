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

#include "stm32f2xx.h"
#include "stm32f2xx_hal.h"
#include "usbd_def.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

/* private defines	  ------------------------------------------------------------*/
#define USB_TX_BUFF_SIZE	2048
#define USB_RX_BUFF_SIZE	2048

/* private variables	  --------------------------------------------------------*/
extern uint8_t UserRxBufferFS[];
extern uint16_t UserRxSize;

extern uint8_t UserTxBufferFS[];

QBuffer USBTxQBuffer;
QBuffer USBRxQBuffer;

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
	USBTxQBuffer.Alloc(USB_TX_BUFF_SIZE);
	USBRxQBuffer.Alloc(USB_RX_BUFF_SIZE);

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
	return UserRxSize;
}

unsigned int USBInstance::Write(char *source, unsigned int size)
{
	char *pTemp = source;
	unsigned int result = 0;

	if (CDC_Transmit_FS((uint8_t *)pTemp, size) == USBD_OK)
	{
		result = size;
	}

	return result;
}

unsigned int USBInstance::Read(char *destination, unsigned int size)
{
	char *pTemp = destination;
	unsigned int result = 0;

	if (size <= UserRxSize)
	{
		memcpy(pTemp, UserRxBufferFS, size);
		UserRxSize -=size;
	}

	return result;
}


