/**
  ******************************************************************************
  * @file    ADC.h
  * @brief   This file contains ADC API for the analog inputs
  * 	     available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_H
#define __USB_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
#include "stm32f2xx_hal.h"
#include "usbd_def.h"

/* Exported defines	  --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Experted variables --------------------------------------------------------*/
extern USBD_HandleTypeDef hUsbDeviceFS;

/* Exported class-------------------------------------------------------------*/
class USBInstance {

public:
	USBInstance(void);
	~USBInstance(void);
	void Initialization(void);
	void Configuration(unsigned int command, void* arg);
	unsigned int Available(void);
	unsigned int Write(char *source, unsigned int size);
	unsigned int Read(char *destination, unsigned int size);
	unsigned int Print(char* source);
	unsigned int Print(const char* source);
	unsigned int Print(int source);
	unsigned int Println(char * source);
	unsigned int Println(const char * source);
	unsigned int Println(int source);
};

/* Exported variables	  --------------------------------------------------------*/
extern USBInstance USBObj;


#endif /*__ADC_H */


