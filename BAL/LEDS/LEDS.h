/**
  ******************************************************************************
  * @file    LEDS.h
  * @brief   This file contains LEDS API for the general purpose inputs outputs
  * 	     available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDS_H
#define __LEDS_H

/* Includes ------------------------------------------------------------------*/
/* Exported defines	  --------------------------------------------------------*/
/* Standard configuration of the GPIO */
/* Exported types ------------------------------------------------------------*/

typedef enum
{
	ON = 0,
	OFF = 1
}eLEDStates;

/* Exported variables	  --------------------------------------------------------*/

/* Exported class		  --------------------------------------------------------*/
/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class LEDSInstance {

public:
	LEDSInstance(void);
	~LEDSInstance(void);
	void Initialization (unsigned int led);
	void On(unsigned int led);
	void Off(unsigned int led);
	void Toggle(unsigned int led);
};

extern LEDSInstance LEDS;

#endif

