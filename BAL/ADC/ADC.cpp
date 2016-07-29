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
static GPIO_TypeDef* GPIOPortList[NUMBER_OF_AN_INPUTS] = AN_PORT_ARRAY;
static const uint16_t GPIOPinList[NUMBER_OF_AN_INPUTS] = AN_PIN_ARRAY;

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* STM32Cube HAL function prototypes */
void DMA2_Stream4_IRQHandler(void);

#ifdef __cplusplus
}
#endif

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
	HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

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


/**
* @brief This function handles DMA2 Stream0 global interrupt.
*/
void DMA2_Stream4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/* ST microelectronics HAL code **********************************/

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    __ADC1_CLK_ENABLE();

    /* Peripheral DMA init*/

    hdma_adc1.Instance = DMA2_Stream4;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_MEDIUM;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_adc1.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_adc1.Init.MemBurst = DMA_MBURST_SINGLE;
    hdma_adc1.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_Init(&hdma_adc1);

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __ADC1_CLK_DISABLE();

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(hadc->DMA_Handle);
  }
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */

}


