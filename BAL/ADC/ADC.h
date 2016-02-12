/**
  ******************************************************************************
  * @file    ADC.h
  * @brief   This file contains ADC API for the analog inputs
  * 	     available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx_hal.h"

/* Exported defines	  --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported class-------------------------------------------------------------*/
class ADCInstance {
private:
	//static ADC_HandleTypeDef hadc;
public:
	ADCInstance(void);
	~ADCInstance(void);
	void Initialization(void);
	void Enable(unsigned int pin);
	void Disable(unsigned int pin);
	unsigned int Read(unsigned int pin);
};

/* Exported variables	  --------------------------------------------------------*/
extern ADCInstance ADCObj;


#endif /*__ADC_H */


