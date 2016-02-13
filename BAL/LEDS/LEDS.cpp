/**
  ******************************************************************************
  * @file    GPIO.c
  * @brief   This file contains GPIO API for the general purpose inputs outputs
  * 	     available on board.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "LEDS.h"
#include "GPIO/GPIO.h"
#include "BAPI.h"
#include "stm32f2xx_hal.h"
/* Exported variables	  --------------------------------------------------------*/
LEDSInstance LEDS;

/* private variables	  --------------------------------------------------------*/
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_LEDS] = {LED1_PORT, LED2_PORT,
													 LED3_PORT, LED4_PORT};
static const uint16_t GPIOPinList[NUMBER_OF_LEDS] = {LED1_PIN, LED2_PIN, LED3_PIN,
													 LED4_PIN};
/* private class functions -------------------------------------------------------*/

LEDSInstance::LEDSInstance(void)
{
}

LEDSInstance::~LEDSInstance(void)
{
}

void LEDSInstance::Initialization(unsigned int pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pins : PB10 PB11 */
	GPIO_InitStruct.Pin = GPIOPinList[pin];
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(GPIOPortList[pin], &GPIO_InitStruct);
}

void LEDSInstance::On(unsigned int pin)
{
	HAL_GPIO_WritePin(GPIOPortList[pin], GPIOPinList[pin], GPIO_PIN_SET);
}

void LEDSInstance::Off(unsigned int pin)
{
	HAL_GPIO_WritePin(GPIOPortList[pin], GPIOPinList[pin], GPIO_PIN_RESET);
}

void LEDSInstance::Toggle(unsigned int pin)
{
	HAL_GPIO_TogglePin(GPIOPortList[pin], GPIOPinList[pin]);
}



