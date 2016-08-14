/**
  ******************************************************************************
  * @file    GPIO.h
  * @brief   This file contains GPIO API for the general purpose inputs outputs
  * 	     available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
/* Exported defines	  --------------------------------------------------------*/
/* Standard configuration of the GPIO */
#define INPUT INPUT_PULLUP
#define OUTPUT OUTPUT_PULLUP

#define HIGH	1
#define LOW		0

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	INPUT_OPENDRAIN = 0,
	INPUT_PULLUP,
	INPUT_PULLDOWN,
	OUTPUT_OPENDRAIN,
	OUTPUT_PULLUP,
	OUTPUT_PULLDOWN
}eGPIOModes;


/* Exported class		  --------------------------------------------------------*/
/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class GPIOInstance {

public:
	GPIOInstance(void);
	~GPIOInstance(void);
	void Mode(unsigned int pin,  eGPIOModes mode);
	void Write(unsigned int pin, unsigned int value);
	void Toggle(unsigned int pin);
	unsigned int Read(unsigned int pin);
};

/* Exported variables	  --------------------------------------------------------*/
extern GPIOInstance GPIO;

#endif

