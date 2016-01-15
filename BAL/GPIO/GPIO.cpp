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
#include "stm32f2xx_hal.h"

/* Exported variables	  --------------------------------------------------------*/
GPIOInstance GPIO;

/* private variables	  --------------------------------------------------------*/
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_LEDS] = {LED1_GPIO_PORT, LED2_GPIO_PORT,
													 LED3_GPIO_PORT, LED4_GPIO_PORT};
static const uint16_t GPIOPinList[NUMBER_OF_LEDS] = {LED1_PIN, LED2_PIN, LED3_PIN,
													 LED4_PIN};
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


/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PB10   ------> S_TIM2_CH3
     PB11   ------> S_TIM2_CH4
     PA8   ------> USB_OTG_FS_SOF
     PA9   ------> USB_OTG_FS_VBUS
     PA10   ------> USB_OTG_FS_ID
     PA11   ------> USB_OTG_FS_DM
     PA12   ------> USB_OTG_FS_DP
     PB4   ------> S_TIM3_CH1
     PB5   ------> S_TIM3_CH2
*/
//void MX_GPIO_Init(void)
//{

//  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
//  __GPIOC_CLK_ENABLE();
//  __GPIOH_CLK_ENABLE();
//  __GPIOA_CLK_ENABLE();
//  __GPIOB_CLK_ENABLE();
//  __GPIOD_CLK_ENABLE();

  /*Configure GPIO pins : PC13 PC14 PC15 PC6 
                           PC7 */
//  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6
//                          |GPIO_PIN_7;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA1 */
//  GPIO_InitStruct.Pin = GPIO_PIN_1;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB12 */
//  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 */
//  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA10 PA11 PA12 */
//  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
//  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA9 */
//  GPIO_InitStruct.Pin = GPIO_PIN_9;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 */
//  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
//  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
//  GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//}
