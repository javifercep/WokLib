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


/* Exported variables	  --------------------------------------------------------*/
PWMInstance PWM;

/* private variables	  --------------------------------------------------------*/
TIM_HandleTypeDef htim[NUMBER_OF_TIMER_USED];

static TIM_TypeDef* UsedTimer[NUMBER_OF_TIMER_USED] = TIMER_USED_ARRAYS;

static const uint32_t ChannelsMapping1[ATTACHED_OUT_TO_TIMER_1] = OUT_TO_TIMER_MAPPING_1_ARRAY;

static const uint8_t NumberOfChannelsPerTimer[NUMBER_OF_TIMER_USED] = ATTACHED_OUT_PER_TIMER_ARRAY;

#if NUMBER_OF_TIMER_USED > 1
static const uint32_t ChannelsMapping2[ATTACHED_OUT_TO_TIMER_2] = OUT_TO_TIMER_MAPPING_2_ARRAY;
#endif

static const uint8_t PinTimerMapping[NUMBER_OF_PWM] = PWM_INSTANCE_ARRAY;

static const uint32_t PinChannelMapping[NUMBER_OF_PWM] = PWM_TIM_CHANNEL_ARRAY;

static GPIO_TypeDef* GPIOPortList[NUMBER_OF_PWM] = PWM_PORT_ARRAY;

static const uint16_t GPIOPinList[NUMBER_OF_PWM] = PWM_PIN_ARRAY;

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
  uint8_t TimerIndex;
  uint8_t ChannelIndex;

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = DEFAULT_PWM_DUTY;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  for (TimerIndex = 0; TimerIndex < NUMBER_OF_TIMER_USED; TimerIndex++)
  {
    htim[TimerIndex].Instance = UsedTimer[TimerIndex];
    htim[TimerIndex].Init.Prescaler = DEFAULT_PWM_PRESCALER;
    htim[TimerIndex].Init.CounterMode = TIM_COUNTERMODE_UP;
    htim[TimerIndex].Init.Period = DEFAULT_PWM_PERIOD;
    htim[TimerIndex].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&(htim[TimerIndex]));

    HAL_TIMEx_MasterConfigSynchronization(&(htim[TimerIndex]), &sMasterConfig);

    for (ChannelIndex = 0; ChannelIndex < NumberOfChannelsPerTimer[TimerIndex]; ChannelIndex++)
    {
      HAL_TIM_PWM_ConfigChannel(&(htim[TimerIndex]), &sConfigOC, ChannelsMapping1[ChannelIndex]);
    }
  }
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
  else if (htim[PinTimerMapping[pin]].Instance == TIM3)
  {
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
  }
  else
  {

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

/* ST microelectronics HAL code **********************************/

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM2)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  }
  else if(htim_pwm->Instance==TIM3)
  {
    /* Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();
  }
  else if(htim_pwm->Instance==TIM3)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  }

}
