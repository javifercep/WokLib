/**
  ******************************************************************************
  * @file    PWM.h
  * @brief   This file contains PWM API for the modulable general purpose inputs outputs
  * 	     	  available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PWM_H
#define __PWM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f2xx.h"
/* Exported defines	  --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	PWM_POL_STD,
	PWM_POL_REV
}PWMPolarity;


/* Exported class		  --------------------------------------------------------*/
/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class PWMInstance {
private:
    PWMPolarity Polarity;
    uint32_t    Duty;
public:
	PWMInstance(void);
	~PWMInstance(void);
	void Initialization(void);
	void Config(unsigned int pin,  unsigned int period, unsigned int duty, PWMPolarity polarity);
	void SetPeriod(unsigned int pin, unsigned int period);
	void SetDuty(unsigned int pin, unsigned int duty);
	void SetPolarity(unsigned int pin, PWMPolarity polarity);
};

/* Exported variables	  --------------------------------------------------------*/
extern PWMInstance PWM;

#endif

