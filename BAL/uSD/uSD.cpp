/**
  ******************************************************************************
  * @file    ADC.c
  * @brief   This file contains ADC API for the ganalog inputs
  * 	     available on board.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "uSD.h"

/* Exported variables	  --------------------------------------------------------*/
uSDInstance uSD;

SD_HandleTypeDef hsd;
DMA_HandleTypeDef hdma_sdio_rx;
DMA_HandleTypeDef hdma_sdio_tx;

HAL_SD_CardInfoTypedef SDCardInfo;

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

void DMA2_Stream3_IRQHandler(void);
void DMA2_Stream6_IRQHandler(void);

#ifdef __cplusplus
}
#endif


/* private variables	  --------------------------------------------------------*/

/* ADC1 init function */
uSDInstance::uSDInstance(void)
{
	  hsd.Instance = SDIO;
	  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
	  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
	  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
	  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
	  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
	  hsd.Init.ClockDiv = 16;
}

uSDInstance::~uSDInstance(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	FATFS_UnLinkDriver(this->SDPath);
}

void uSDInstance::Initialization(void)
{
	/*## FatFS: Link the SD driver ###########################*/
	if (FATFS_LinkDriver(&SD_Driver, this->SDPath) == 0)
	{
		this->SDStatus = uSD_AVAILABLE;
	}
	else
	{
		this->SDStatus = uSD_ERROR;
	}
}

uint8_t uSDInstance::MountSD()
{
	if(f_mount(&this->DiskFatFs, (TCHAR const*)this->SDPath, 0) == FR_OK)
	{
		this->SDStatus = uSD_AVAILABLE;
	}
	else
	{
		this->SDStatus = uSD_ERROR;
	}
	return 0;
}

uint8_t uSDInstance::UnMountSD()
{
	return 0;
}

uint8_t uSDInstance::CreateFile(const char* path)
{
	if(this->SDStatus == uSD_AVAILABLE)
	{
		f_open(&(this->FileInstance), path, FA_CREATE_ALWAYS | FA_WRITE);
	}
	return 0;
}

uint8_t uSDInstance::DeleteFile()
{
	return 0;
}


uint8_t uSDInstance::OpenFile(const char* path)
{
	if(this->SDStatus == uSD_AVAILABLE)
	{
		f_open(&(this->FileInstance), path, FA_OPEN_ALWAYS | FA_WRITE);
	}

	return 0;
}

uint8_t uSDInstance::CloseFile()
{
	if(this->SDStatus == uSD_AVAILABLE)
	{
		f_close(&(this->FileInstance));
	}

	return 0;
}

uint32_t uSDInstance::WriteFile(const void *buff, uint32_t Len)
{
	uint32_t WrittenBytes = 0;

	if(this->SDStatus == uSD_AVAILABLE)
	{
		f_write(&(this->FileInstance), buff, Len, (UINT *)&WrittenBytes);
	}

	return WrittenBytes;
}

uint32_t uSDInstance::Print(char *source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	if(this->SDStatus == uSD_AVAILABLE)
	{
		pTemp = (char* )pvPortMalloc(strlen(source));

		if(pTemp != NULL)
		{
			strcpy(pTemp, source);

			this->WriteFile(pTemp, size);

			result = size;

			vPortFree(pTemp);
		}
	}

	return result;
}

uint32_t uSDInstance::Print(const char *source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	if(this->SDStatus == uSD_AVAILABLE)
	{
		pTemp = (char* )pvPortMalloc(strlen(source));

		if(pTemp != NULL)
		{
			strcpy(pTemp, source);

			this->WriteFile(pTemp, size);

			result = size;

			vPortFree(pTemp);
		}
	}

	return result;
}

uint32_t uSDInstance::Print(int source)
{
	char pTemp[4];
	unsigned int result = 0;
	unsigned int size = 0;

	if(this->SDStatus == uSD_AVAILABLE)
	{
		size = sprintf(pTemp, "%d", source);

		if( size > 0)
		{
			this->WriteFile(pTemp, size);

			result = size;
		}
	}

	return result;
}

uint32_t uSDInstance::Println(char *source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = 0;

	if(this->SDStatus == uSD_AVAILABLE)
	{
		pTemp = (char *) pvPortMalloc(strlen(source) + 2);

		if (pTemp != NULL)
		{
			strcpy(pTemp, source);
			strcat(pTemp, "\n");

			size = strlen(pTemp);

			this->WriteFile(pTemp, size);

			result = size;

			vPortFree(pTemp);
		}
	}

	return result;
}

uint32_t uSDInstance::Println(const char *source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = 0;

	if(this->SDStatus == uSD_AVAILABLE)
	{
		pTemp = (char *) pvPortMalloc(strlen(source) + 2);

		if (pTemp != NULL)
		{
			strcpy(pTemp, source);
			strcat(pTemp, "\n");

			size = strlen(pTemp);

			this->WriteFile(pTemp, size);

			result = size;

			vPortFree(pTemp);
		}
	}

	return result;
}

uint32_t uSDInstance::Println(int source)
{
	char pTemp[6];
	unsigned int result = 0;
	unsigned int size = 0;

	if(this->SDStatus == uSD_AVAILABLE)
	{
		size = sprintf(pTemp, "%d\n", source);

		if(size > 0)
		{
			this->WriteFile(pTemp, size);

			result = size;
		}
	}
	return result;
}

uint8_t uSDInstance::ReadFile()
{
	return 0;
}

uint8_t uSDInstance::CreateFolder()
{
	return 0;
}

uint8_t uSDInstance::DeleteFolder()
{
	return 0;
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}


/**
* @brief This function handles DMA2 Stream3 global interrupt.
*/
void DMA2_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream3_IRQn 0 */

  /* USER CODE END DMA2_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdio_rx);
  /* USER CODE BEGIN DMA2_Stream3_IRQn 1 */

  /* USER CODE END DMA2_Stream3_IRQn 1 */
}

/**
* @brief This function handles DMA2 Stream6 global interrupt.
*/
void DMA2_Stream6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream6_IRQn 0 */

  /* USER CODE END DMA2_Stream6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdio_tx);
  /* USER CODE BEGIN DMA2_Stream6_IRQn 1 */

  /* USER CODE END DMA2_Stream6_IRQn 1 */
}


/* ST microelectronics HAL code **********************************/
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hsd->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspInit 0 */

  /* USER CODE END SDIO_MspInit 0 */
    /* Peripheral clock enable */
    __SDIO_CLK_ENABLE();

    /**SDIO GPIO Configuration
    PC8     ------> SDIO_D0
    PC9     ------> SDIO_D1
    PC10     ------> SDIO_D2
    PC11     ------> SDIO_D3
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Peripheral DMA init*/

    hdma_sdio_rx.Instance = DMA2_Stream3;
    hdma_sdio_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_sdio_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sdio_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio_rx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio_rx.Init.Mode = DMA_PFCTRL;
    hdma_sdio_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_sdio_rx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_sdio_rx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_sdio_rx.Init.MemBurst = DMA_MBURST_INC4;
    hdma_sdio_rx.Init.PeriphBurst = DMA_PBURST_INC4;
    HAL_DMA_Init(&hdma_sdio_rx);

    __HAL_LINKDMA(hsd,hdmarx,hdma_sdio_rx);

    hdma_sdio_tx.Instance = DMA2_Stream6;
    hdma_sdio_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_sdio_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_sdio_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sdio_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sdio_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sdio_tx.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sdio_tx.Init.Mode = DMA_PFCTRL;
    hdma_sdio_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_sdio_tx.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
    hdma_sdio_tx.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
    hdma_sdio_tx.Init.MemBurst = DMA_MBURST_INC4;
    hdma_sdio_tx.Init.PeriphBurst = DMA_PBURST_INC4;
    HAL_DMA_Init(&hdma_sdio_tx);

    __HAL_LINKDMA(hsd,hdmatx,hdma_sdio_tx);

  /* USER CODE BEGIN SDIO_MspInit 1 */

  /* USER CODE END SDIO_MspInit 1 */
  }

}

void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{

  if(hsd->Instance==SDIO)
  {
  /* USER CODE BEGIN SDIO_MspDeInit 0 */

  /* USER CODE END SDIO_MspDeInit 0 */
    /* Peripheral clock disable */
    __SDIO_CLK_DISABLE();

    /**SDIO GPIO Configuration
    PC8     ------> SDIO_D0
    PC9     ------> SDIO_D1
    PC10     ------> SDIO_D2
    PC11     ------> SDIO_D3
    PC12     ------> SDIO_CK
    PD2     ------> SDIO_CMD
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(hsd->hdmarx);
    HAL_DMA_DeInit(hsd->hdmatx);
  }
  /* USER CODE BEGIN SDIO_MspDeInit 1 */

  /* USER CODE END SDIO_MspDeInit 1 */

}

