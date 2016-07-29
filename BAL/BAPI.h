/**
  ******************************************************************************
  * @file    BAPI.h
  * @brief   This file contains Board API.
  *******************************************************************************
  */

#ifndef BAPI_H_
#define BAPI_H_

/* Includes ------------------------------------------------------------------*/
#ifdef KRAKOSKI_BOARD
#include "Krakoski.h"
#elif NOODLE_BOARD
#include "Noodle.h"
#endif

#if NUMBER_OF_GPIO > 0
#include "GPIO/GPIO.h"
#endif

#if NUMBER_OF_LEDS > 0
#include "LEDS/LEDS.h"
#endif

#if NUMBER_OF_AN_INPUTS > 0
#include "ADC/ADC.h"
#endif

#if NUMBER_OF_PWM > 0
#include "PWM/PWM.h"
#endif

#if NUMBER_OF_USART > 0
#include "USART/USART.h"
#endif

#if NUMBER_OF_SPI > 0
#include "SPI/SPI.h"
#endif

#if NUMBER_OF_USB_CLASS > 0
#include "USB/USB.h"
#endif

#if RTOS_SUPPORTED != 0
#include "RTOS/RTOS.h"
#endif

#if SD_SUPPORTED != 0
#include "uSD/uSD.h"
#endif


/* Exported typedef ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class BoardInstance {

public:
	BoardInstance(void); 	/**< Main board instance constructor */
	~BoardInstance(void);	/**< Main board instance destructor */
	/**
	 *  Initializes the main MCU elements (sys clock, board features)
	 */
	void Initialization(void);
};


#endif /* BAPI_H_ */
