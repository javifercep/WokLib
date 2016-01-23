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

/* Exported defines	  --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
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
};

/* Exported variables	  --------------------------------------------------------*/
extern USBInstance USBObj;


#endif /*__ADC_H */


