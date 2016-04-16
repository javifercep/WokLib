/**
  ******************************************************************************
  * @file    USART.cpp
  * @brief   This file contains USART API.
  *******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "Krakoski.h"
#include "SPI/SPI.h"
#include "RTOS/RTOS.h"
#include "stm32f2xx.h"

#include <stdio.h>
#include <string.h>

/* Private defines    --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
SPIInstance SPIObj1;
SPIInstance SPIObj2;

/* Private variables ---------------------------------------------------------*/
static SPI_HandleTypeDef *hspi1;
static SPI_HandleTypeDef *hspi2;
static DMA_HandleTypeDef *hdma_hspi1_rx;
static DMA_HandleTypeDef *hdma_hspi1_tx;
static DMA_HandleTypeDef *hdma_hspi2_rx;
static DMA_HandleTypeDef *hdma_hspi2_tx;

osMutexId SPI1TxMutexHandle;
osMutexId SPI1RxMutexHandle;

osMutexDef(SPI1TxMutex);
osMutexDef(SPI1RxMutex);

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif
/* STM32Cube HAL function prototypes */
void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);

#if NUMBER_OF_SPI > 1
void DMA1_Stream3_IRQHandler(void);
void DMA1_Stream4_IRQHandler(void);
#endif

#ifdef __cplusplus
}
#endif

/* USART Class description */
SPIInstance::SPIInstance(void)
{

}

SPIInstance::~SPIInstance(void)
{

}

int SPIInstance::Initialization(unsigned char module)
{
	int ret = 0;

	this->SPIRxQueue.Alloc(SPI_BUFFER_SIZE);

	switch (module)
	{
		case SPI_MODULE_1:
		    SPI1TxMutexHandle = osMutexCreate(osMutex(SPI1TxMutex));
		    SPI1RxMutexHandle = osMutexCreate(osMutex(SPI1RxMutex));

			__DMA2_CLK_ENABLE();

            /* DMA2_Stream2_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 1, 0);
            HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
            /* DMA2_Stream3_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 2, 0);
            HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

			hspi1 = &(this->hspi);
			hdma_hspi1_rx = &(this->hdma_hspi_rx);
			hdma_hspi1_tx = &(this->hdma_hspi_tx);

			this->hspi.Instance = SPI1;

		    this->hdma_hspi_rx.Instance = DMA2_Stream2;
		    this->hdma_hspi_rx.Init.Channel = DMA_CHANNEL_3;
            this->hdma_hspi_tx.Instance = DMA2_Stream3;
            this->hdma_hspi_tx.Init.Channel = DMA_CHANNEL_3;

			break;
#if NUMBER_OF_SPI > 1
		case SPI_MODULE_2:
            __DMA1_CLK_ENABLE();

            /* DMA1_Stream3_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 1, 0);
            HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);
            /* DMA1_Stream4_IRQn interrupt configuration */
            HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 2, 0);
            HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

            hspi2 = &(this->hspi);
            hdma_hspi2_rx = &(this->hdma_hspi_rx);
            hdma_hspi2_tx = &(this->hdma_hspi_tx);

            this->hspi.Instance = SPI1;

            this->hdma_hspi_rx.Instance = DMA1_Stream3;
            this->hdma_hspi_rx.Init.Channel = DMA_CHANNEL_0;
            this->hdma_hspi_tx.Instance = DMA1_Stream4;
            this->hdma_hspi_tx.Init.Channel = DMA_CHANNEL_0;
			break;
#endif
		default:
			ret = -1;
			break;
	}

	if (ret == 0)
	{
		this->hspi.Init.Mode = SPI_MODE_MASTER;
		this->hspi.Init.Direction = SPI_DIRECTION_2LINES;
		this->hspi.Init.DataSize= SPI_DATASIZE_8BIT;
		this->hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
		this->hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
		this->hspi.Init.NSS = SPI_NSS_SOFT;
		this->hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
		this->hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
		this->hspi.Init.TIMode = SPI_TIMODE_DISABLE;
		this->hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
		this->hspi.Init.CRCPolynomial = 10;

		HAL_SPI_Init(&(this->hspi));

		this->hdma_hspi_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	    this->hdma_hspi_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	    this->hdma_hspi_rx.Init.MemInc = DMA_MINC_ENABLE;
	    this->hdma_hspi_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    this->hdma_hspi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	    this->hdma_hspi_rx.Init.Mode = DMA_NORMAL;
	    this->hdma_hspi_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	    this->hdma_hspi_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    HAL_DMA_Init(&(this->hdma_hspi_rx));

	    __HAL_LINKDMA(&hspi,hdmarx,hdma_hspi_rx);

	    this->hdma_hspi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	    this->hdma_hspi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	    this->hdma_hspi_tx.Init.MemInc = DMA_MINC_ENABLE;
	    this->hdma_hspi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    this->hdma_hspi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	    this->hdma_hspi_tx.Init.Mode = DMA_NORMAL;
	    this->hdma_hspi_tx.Init.Priority = DMA_PRIORITY_HIGH;
	    this->hdma_hspi_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    HAL_DMA_Init(&(this->hdma_hspi_tx));

	    __HAL_LINKDMA(&hspi,hdmatx,hdma_hspi_tx);

	}

	return ret;
}

void Deinitialization()
{

}

void SPIInstance::Configuration(unsigned int command, void* arg)
{
  switch (command)
  {
    default:
      break;
  }
}

unsigned int SPIInstance::Available(void)
{
	return SPIRxQueue.Available(); //UserRxSize;
}

unsigned int SPIInstance::Write(char *source, unsigned int size)
{
	uint8_t *pTemp = (uint8_t *)source;

	/* Wait for an active transfer */
	while (this->TransferSize != 0);
	this->TransferSize = size;
    osMutexWait(SPI1TxMutexHandle, 0);
    HAL_SPI_TransmitReceive_DMA(&(this->hspi), pTemp, this->SPI_RXTemp_Buf, size);
	osMutexRelease (SPI1TxMutexHandle);

	return size;
}

unsigned int SPIInstance::Read(char *destination, unsigned int size)
{
	unsigned char *pTemp = (unsigned char *)destination;
	unsigned int result = size;

	osMutexWait(SPI1RxMutexHandle, 0);
	if (result > this->SPIRxQueue.Available())
	{
		result = this->SPIRxQueue.Available();
	}

	this->SPIRxQueue.ReadToArray(pTemp, result);
	osMutexWait(SPI1RxMutexHandle, 0);

	return result;
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	if (hspi->Instance == SPI1)
	{
		SPIObj1.SPIRxQueue.WriteFromArray(SPIObj1.SPI_RXTemp_Buf, SPIObj1.TransferSize);
		SPIObj1.TransferSize = 0;
	}

	if (hspi->Instance == SPI1)
	{
        SPIObj2.SPIRxQueue.WriteFromArray(SPIObj2.SPI_RXTemp_Buf, SPIObj2.TransferSize);
        SPIObj2.TransferSize = 0;
	}
}


/* STM32Cube HAL function **********************************************/

/**
* @brief This function handles DMA2 Stream2 global interrupt.
*/
void DMA2_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_hspi1_rx);
}

/**
* @brief This function handles DMA2 Stream3 global interrupt.
*/
void DMA2_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_hspi1_tx);
}

/**
* @brief This function handles DMA1 stream3 global interrupt.
*/
void DMA1_Stream3_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_hspi2_rx);
}

/**
* @brief This function handles DMA1 stream4 global interrupt.
*/
void DMA1_Stream4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_hspi2_tx);
}


