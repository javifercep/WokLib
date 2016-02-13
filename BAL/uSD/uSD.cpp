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
	  hsd.Init.ClockDiv = 4;
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
