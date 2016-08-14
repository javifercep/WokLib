/**
  ******************************************************************************
  * @file    GPIO.c
  * @brief   This file contains GPIO API for the general purpose inputs outputs
  * 	     available on board.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "GPIO.h"
#include "BAPI.h"

/* Exported variables	  --------------------------------------------------------*/
GPIOInstance GPIO;

/* private variables	  --------------------------------------------------------*/
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_GPIO] = PIN_PORT_ARRAY;
static const uint16_t GPIOPinList[NUMBER_OF_GPIO] = PIN_PIN_ARRAY;

/* private class functions -------------------------------------------------------*/

GPIOInstance::GPIOInstance(void)
{
}

GPIOInstance::~GPIOInstance(void)
{
}

void GPIOInstance::Mode(unsigned int pin, eGPIOModes mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/*Configure GPIO pins : PB10 PB11 */
	GPIO_InitStruct.Pin = GPIOPinList[pin];
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	switch(mode)
	{
		case INPUT_OPENDRAIN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case INPUT_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case INPUT_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;
		case OUTPUT_OPENDRAIN:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case OUTPUT_PULLUP:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			break;
		case OUTPUT_PULLDOWN:
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			break;
		default:
			break;

	}

	HAL_GPIO_Init(GPIOPortList[pin], &GPIO_InitStruct);
}

void GPIOInstance::Write(unsigned int pin, unsigned int value)
{
	if (value == LOW )
	{
		HAL_GPIO_WritePin(GPIOPortList[pin], GPIOPinList[pin], GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOPortList[pin], GPIOPinList[pin], GPIO_PIN_SET);
	}
}

void GPIOInstance::Toggle(unsigned int pin)
{
	HAL_GPIO_TogglePin(GPIOPortList[pin], GPIOPinList[pin]);
}

unsigned int GPIOInstance::Read(unsigned int pin)
{
	unsigned int Result;

	if (HAL_GPIO_ReadPin(GPIOPortList[pin], GPIOPinList[pin]) == GPIO_PIN_RESET)
	{
		Result = LOW;
	}
	else
	{
		Result = HIGH;
	}

	return Result;
}
