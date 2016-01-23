/**
  ******************************************************************************
  * @file    BAPI.h
  * @brief   This file contains Board API.
  *******************************************************************************
  */

#ifndef BAPI_H_
#define BAPI_H_

/* Includes ------------------------------------------------------------------*/
#include "GPIO/GPIO.h"
#include "RTOS/RTOS.h"
#include "LEDS/LEDS.h"
#include "USB/USB.h"

/* Exported define ------------------------------------------------------------*/
#define NUMBER_OF_LEDS					4

#define LED1							0
#define LED1_PIN						GPIO_PIN_4
#define LED1_GPIO_PORT					GPIOB

#define LED2							1
#define LED2_PIN						GPIO_PIN_5
#define LED2_GPIO_PORT					GPIOB

#define LED3							2
#define LED3_PIN						GPIO_PIN_11
#define LED3_GPIO_PORT					GPIOB

#define LED4							3
#define LED4_PIN						GPIO_PIN_10
#define LED4_GPIO_PORT					GPIOB
/********************************************************/
#define NUMBER_OF_AN_INPUTS				6

#define A1								0
#define AN1_PIN							GPIO_PIN_0
#define AN1_PORT						GPIOB

#define A2								1
#define AN2_PIN							GPIO_PIN_1
#define AN2_PORT						GPIOB

#define A3								2
#define AN3_PIN							GPIO_PIN_2
#define AN3_PORT						GPIOC

#define A4								3
#define AN4_PIN							GPIO_PIN_3
#define AN4_PORT						GPIOC

#define A5								4
#define AN5_PIN							GPIO_PIN_4
#define AN5_PORT						GPIOC

#define A6								5
#define AN6_PIN							GPIO_PIN_5
#define AN6_PORT						GPIOC

/* Exported typedef ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class BoardInstance {

public:
	BoardInstance(void);
	~BoardInstance(void);
	void Initialization(void);
};


#endif /* BAPI_H_ */
