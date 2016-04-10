/**
 ******************************************************************************
 * @file    PWM.c
 * @brief   This file contains PWM API for the general purpose inputs outputs
 * 	     	  available on board.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "stm32f2xx_hal.h"

/* Private defines	  --------------------------------------------------------*/
#define	DEFAULT_PWM_PRESCALER   3		/* 0,1 us every tick */
#define	DEFAULT_PWM_PERIOD      10000 	/* 1 ms */
#define	DEFAULT_PWM_DUTY        5000  	/* 50 % */

#define NUM_TIM_INDEX           2
#define TIM3_INDEX              0
#define TIM2_INDEX              1

/* Exported variables	  --------------------------------------------------------*/
PWMInstance PWM;

/* private variables	  --------------------------------------------------------*/
TIM_HandleTypeDef htim[NUM_TIM_INDEX];

static const uint8_t PinTimerMapping[NUMBER_OF_PWM] =
{
TIM3_INDEX, TIM3_INDEX, TIM2_INDEX, TIM2_INDEX };

static const uint32_t PinChannelMapping[NUMBER_OF_PWM] =
{
TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_4, TIM_CHANNEL_3 };

static GPIO_TypeDef* GPIOPortList[NUMBER_OF_PWM] =
{ PWM1_PORT, PWM2_PORT, PWM3_PORT, PWM4_PORT};

static const uint16_t GPIOPinList[NUMBER_OF_PWM] =
{ PWM1_PIN, PWM2_PIN, PWM3_PIN, PWM4_PIN};

/* private functions prototypes -------------------------------------------------*/
/* private class functions -------------------------------------------------------*/

PWMInstance::PWMInstance(void)
{
}

PWMInstance::~PWMInstance(void)
{
}

void PWMInstance::Initialization(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = DEFAULT_PWM_DUTY;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  htim[TIM2_INDEX].Instance = TIM2;
  htim[TIM2_INDEX].Init.Prescaler = DEFAULT_PWM_PRESCALER;
  htim[TIM2_INDEX].Init.CounterMode = TIM_COUNTERMODE_UP;
  htim[TIM2_INDEX].Init.Period = DEFAULT_PWM_PERIOD;
  htim[TIM2_INDEX].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&(htim[TIM2_INDEX]));

  HAL_TIMEx_MasterConfigSynchronization(&(htim[TIM2_INDEX]), &sMasterConfig);

  HAL_TIM_PWM_ConfigChannel(&(htim[TIM2_INDEX]), &sConfigOC, TIM_CHANNEL_3);
  HAL_TIM_PWM_ConfigChannel(&(htim[TIM2_INDEX]), &sConfigOC, TIM_CHANNEL_4);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = DEFAULT_PWM_DUTY;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  htim[TIM3_INDEX].Instance = TIM3;
  htim[TIM3_INDEX].Init.Prescaler = DEFAULT_PWM_PRESCALER;
  htim[TIM3_INDEX].Init.CounterMode = TIM_COUNTERMODE_UP;
  htim[TIM3_INDEX].Init.Period = DEFAULT_PWM_PERIOD;
  htim[TIM3_INDEX].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&(htim[TIM3_INDEX]));

  HAL_TIMEx_MasterConfigSynchronization(&(htim[TIM3_INDEX]), &sMasterConfig);

  HAL_TIM_PWM_ConfigChannel(&(htim[TIM3_INDEX]), &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&(htim[TIM3_INDEX]), &sConfigOC, TIM_CHANNEL_2);
}

void PWMInstance::Config(unsigned int pin, unsigned int period,
    unsigned int duty, PWMPolarity polarity)
{
  TIM_OC_InitTypeDef sConfigOC;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Compute preescaler and period using the input frequency */
  htim[PinTimerMapping[pin]].Init.Prescaler = DEFAULT_PWM_PRESCALER;
  htim[PinTimerMapping[pin]].Init.CounterMode = TIM_COUNTERMODE_UP;
  htim[PinTimerMapping[pin]].Init.Period = period;
  htim[PinTimerMapping[pin]].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&(htim[PinTimerMapping[pin]]));

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  this->Duty = duty;
  sConfigOC.Pulse = this->Duty;
  this->Polarity = polarity;
  if (this->Polarity == PWM_POL_STD)
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  }
  else
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  }
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&(htim[PinTimerMapping[pin]]), &sConfigOC, PinChannelMapping[pin]);

  GPIO_InitStruct.Pin = GPIOPinList[pin];
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  if (htim[PinTimerMapping[pin]].Instance == TIM2)
  {
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  }
  else
  {
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  }

  HAL_GPIO_Init(GPIOPortList[pin], &GPIO_InitStruct);

  HAL_TIM_PWM_Start(&(htim[PinTimerMapping[pin]]), PinChannelMapping[pin]);
}

void PWMInstance::SetPeriod(unsigned int pin, unsigned int period)
{
  /* Compute preescaler and period using the input frequency */
  htim[PinTimerMapping[pin]].Init.Prescaler = DEFAULT_PWM_PRESCALER;
  htim[PinTimerMapping[pin]].Init.CounterMode = TIM_COUNTERMODE_UP;
  htim[PinTimerMapping[pin]].Init.Period = period;
  htim[PinTimerMapping[pin]].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_PWM_Init(&(htim[PinTimerMapping[pin]]));
}

void PWMInstance::SetDuty(unsigned int pin, unsigned int duty)
{
  TIM_OC_InitTypeDef sConfigOC;

  /* Compute preescaler and period using the input frequency */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  this->Duty = duty;
  sConfigOC.Pulse = this->Duty;
  if (this->Polarity == PWM_POL_STD)
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  }
  else
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  }
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&(htim[PinTimerMapping[pin]]), &sConfigOC, PinChannelMapping[pin]);

  HAL_TIM_PWM_Start(&(htim[PinTimerMapping[pin]]), PinChannelMapping[pin]);
}

void PWMInstance::SetPolarity(unsigned int pin, PWMPolarity polarity)
{
  TIM_OC_InitTypeDef sConfigOC;

  /* Compute preescaler and period using the input frequency */
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = this->Duty;
  if (this->Polarity == PWM_POL_STD)
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  }
  else
  {
    sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
  }
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&(htim[PinTimerMapping[pin]]), &sConfigOC, PinChannelMapping[pin]);
}

