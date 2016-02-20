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
#include "ADC/ADC.h"
#include "USART/USART.h"

/* Exported define ------------------------------------------------------------*/
/* LEDS ***********/
#define NUMBER_OF_LEDS					4

#define LED1							0
#define LED1_PIN						GPIO_PIN_4
#define LED1_PORT						GPIOB

#define LED2							1
#define LED2_PIN						GPIO_PIN_5
#define LED2_PORT						GPIOB

#define LED3							2
#define LED3_PIN						GPIO_PIN_11
#define LED3_PORT						GPIOB

#define LED4							3
#define LED4_PIN						GPIO_PIN_10
#define LED4_PORT						GPIOB

/**ADC **********************************************/
#define NUMBER_OF_AN_INPUTS				6

#define A1								2
#define AN1_PIN							GPIO_PIN_2
#define AN1_PORT						GPIOC

#define A2								3
#define AN2_PIN							GPIO_PIN_3
#define AN2_PORT						GPIOC

#define A3								4
#define AN3_PIN							GPIO_PIN_4
#define AN3_PORT						GPIOC

#define A4								5
#define AN4_PIN							GPIO_PIN_5
#define AN4_PORT						GPIOC

#define A5								0
#define AN5_PIN							GPIO_PIN_0
#define AN5_PORT						GPIOB

#define A6								1
#define AN6_PIN							GPIO_PIN_1
#define AN6_PORT						GPIOB

/* GPIO *******************/
#define NUMBER_OF_GPIO					25

#define PIN0							0
#define PIN0_PIN						GPIO_PIN_2
#define PIN0_PORT						GPIOA

#define PIN1							1
#define PIN1_PIN						GPIO_PIN_3
#define PIN1_PORT						GPIOA

#define PIN2							2
#define PIN2_PIN						GPIO_PIN_7
#define PIN2_PORT						GPIOC

#define PIN3							3
#define PIN3_PIN						GPIO_PIN_4
#define PIN3_PORT						GPIOB

#define PIN4							4
#define PIN4_PIN						GPIO_PIN_13
#define PIN4_PORT						GPIOC

#define PIN5							5
#define PIN5_PIN						GPIO_PIN_5
#define PIN5_PORT						GPIOB

#define PIN6							6
#define PIN6_PIN						GPIO_PIN_11
#define PIN6_PORT						GPIOB

#define PIN7							7
#define PIN7_PIN						GPIO_PIN_1
#define PIN7_PORT						GPIOA

#define PIN8							8
#define PIN8_PIN						GPIO_PIN_15
#define PIN8_PORT						GPIOA

#define PIN9							9
#define PIN9_PIN						GPIO_PIN_10
#define PIN9_PORT						GPIOB

#define PIN10							10
#define PIN10_PIN						GPIO_PIN_2
#define PIN10_PORT						GPIOB

#define PIN11							11
#define PIN11_PIN						GPIO_PIN_6
#define PIN11_PORT						GPIOA

#define PIN12							12
#define PIN12_PIN						GPIO_PIN_7
#define PIN12_PORT						GPIOA

#define PIN13							13
#define PIN13_PIN						GPIO_PIN_5
#define PIN13_PORT						GPIOA

#define PINSDA							14
#define PINSDA_PIN						GPIO_PIN_9
#define PINSDA_PORT						GPIOB

#define PINSCL							15
#define PINSCL_PIN						GPIO_PIN_8
#define PINSCL_PORT						GPIOB

#define PINWKUP							16
#define PINWKUP_PIN						GPIO_PIN_0
#define PINWKUP_PORT					GPIOA

#define PINDAC							17
#define PINDAC_PIN						GPIO_PIN_4
#define PINDAC_PORT						GPIOA

#define PINA1							18
#define PINA1_PIN						GPIO_PIN_2
#define PINA1_PORT						GPIOC

#define PINA2							19
#define PINA2_PIN						GPIO_PIN_3
#define PINA2_PORT						GPIOC

#define PINA3							20
#define PINA3_PIN						GPIO_PIN_4
#define PINA3_PORT						GPIOC

#define PINA4							21
#define PINA4_PIN						GPIO_PIN_5
#define PINA4_PORT						GPIOC

#define PINA5							22
#define PINA5_PIN						GPIO_PIN_0
#define PINA5_PORT						GPIOB

#define PINA6							23
#define PINA6_PIN						GPIO_PIN_1
#define PINA6_PORT						GPIOB

#define PINRST_ESP						24
#define PINRST_ESP_PIN					GPIO_PIN_15
#define PINRST_ESP_PORT					GPIOC


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
