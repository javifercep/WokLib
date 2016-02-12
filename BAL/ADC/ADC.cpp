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

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc1;


/* private variables	  --------------------------------------------------------*/
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_AN_INPUTS] = {AN1_PORT, AN2_PORT,
														  AN3_PORT, AN4_PORT,
														  AN5_PORT, AN6_PORT};
static const uint16_t GPIOPinList[NUMBER_OF_AN_INPUTS] = {AN1_PIN, AN2_PIN, AN3_PIN,
														  AN4_PIN, AN5_PIN, AN6_PIN};

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
	uint8_t ii = 0;

	for(ii = 0; ii < NUMBER_OF_ADC_CHANNEL; ii++)
	{
		this->ADCBuffer[ii] = 0;
	}

	/* DMA controller clock enable */
	__DMA2_CLK_ENABLE();

	/* DMA interrupt init */
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	hadc.Init.Resolution = ADC_RESOLUTION12b;
	hadc.Init.ScanConvMode = ENABLE;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = NUMBER_OF_ADC_CHANNEL;
	hadc.Init.DMAContinuousRequests = ENABLE;
	hadc.Init.EOCSelection = EOC_SEQ_CONV;
	HAL_ADC_Init(&hadc);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = 5;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = 6;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_12;
	sConfig.Rank = 1;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_13;
	sConfig.Rank = 2;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.Rank = 3;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	/**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	*/
	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = 4;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	HAL_ADC_Start_DMA(&hadc, this->ADCBuffer, NUMBER_OF_ADC_CHANNEL);
}

void ADCInstance::Enable(uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Peripheral clock enable */
	__ADC1_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIOPinList[pin];
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOPortList[pin], &GPIO_InitStruct);
}

void ADCInstance::Disable(uint8_t pin)
{
	/* Peripheral clock disable */
	__ADC1_CLK_DISABLE();

	HAL_GPIO_DeInit(GPIOPortList[pin], GPIOPinList[pin]);
}

uint32_t ADCInstance::Read(uint8_t pin)
{
	return this->ADCBuffer[pin];
}


