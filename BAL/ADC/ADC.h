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
#define NUMBER_OF_ADC_CHANNEL 6
/* Exported types ------------------------------------------------------------*/
/* Exported class-------------------------------------------------------------*/
class ADCInstance {
private:
	//static ADC_HandleTypeDef hadc;
	uint32_t ADCBuffer[NUMBER_OF_ADC_CHANNEL];
public:
	ADCInstance(void);
	~ADCInstance(void);
	void Initialization(void);
	void Enable(uint8_t pin);
	void Disable(uint8_t pin);
	uint32_t Read(uint8_t pin);
};

/* Exported variables	  --------------------------------------------------------*/
extern ADCInstance ADCObj;


#endif /*__ADC_H */


