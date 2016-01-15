/**
  ******************************************************************************
  * @file    ADC.c
  * @brief   This file contains ADC API for the ganalog inputs
  * 	     available on board.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "ADC.h"

/* Exported variables	  --------------------------------------------------------*/
ADCInstance ADCObj;

/* private variables	  --------------------------------------------------------*/
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_AN_INPUTS] = {AN1_PORT, AN2_PORT,
														  AN3_PORT, AN4_PORT,
														  AN5_PORT, AN6_PORT};
static const uint16_t GPIOPinList[NUMBER_OF_AN_INPUTS] = {AN1_PIN, AN2_PIN, AN3_PIN,
														  AN4_PIN, AN5_PIN, AN6_PIN};

static ADC_HandleTypeDef hadc1;

/* ADC1 init function */
ADCInstance::ADCInstance(void)
{

}

ADCInstance::~ADCInstance(void)
{

}

void ADCInstance::Initialization(void)
{
	ADC_ChannelConfTypeDef sConfig;

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	hadc1.Init.Resolution = ADC_RESOLUTION12b;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 1;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

void ADCInstance::Enable(unsigned int pin)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

	  if (hadc1.Instance == ADC1)
	  {
	    /* Peripheral clock enable */
	    __ADC1_CLK_ENABLE();

	    GPIO_InitStruct.Pin = GPIOPinList[pin];
	    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(GPIOPortList[pin], &GPIO_InitStruct);

	  }

}

void ADCInstance::Disable(unsigned int pin)
{
	  if (hadc1.Instance == ADC1)
	  {
	    /* Peripheral clock disable */
	    __ADC1_CLK_DISABLE();

	    HAL_GPIO_DeInit(GPIOPortList[pin], GPIOPinList[pin]);
	  }
}

unsigned int ADCInstance::Read(unsigned int pin)
{
	return HAL_ADC_GetValue(&hadc1);
}


