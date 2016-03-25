/**
  ******************************************************************************
  * @file    USART.cpp
  * @brief   This file contains USART API.
  *******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "Krakoski.h"
#include "USART/USART.h"
#include "FreeRTOS.h"
#include "stm32f2xx.h"

#include <stdio.h>
#include <string.h>

/* Exported variables --------------------------------------------------------*/
UsartInstance USARTObj1;

#if NUMBER_OF_USART > 1
UsartInstance USARTObj2;
#endif

/* Private variables ---------------------------------------------------------*/
static UART_HandleTypeDef *huart1 = NULL;
static DMA_HandleTypeDef *hdma_usart1_tx = NULL;

#if NUMBER_OF_USART > 1
static UART_HandleTypeDef *huart2 = NULL;
static DMA_HandleTypeDef *hdma_usart2_tx = NULL;
#endif



/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif
/* STM32Cube HAL function prototypes */
void USART1_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);

#if NUMBER_OF_USART > 1
void USART2_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);
#endif

#ifdef __cplusplus
}
#endif

/* USART Class description */
UsartInstance::UsartInstance(void)
{

}

UsartInstance::~UsartInstance(void)
{

}

int UsartInstance::Initialization(unsigned char module, unsigned int baudrate)
{
	int ret = 0;

	this->USARTRxQueue.Alloc(USART_BUFFER_SIZE);

	switch (module)
	{
		case USART_MODULE_1:
			__DMA2_CLK_ENABLE();

			HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
			HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

			huart1 = &(this->huart);
			hdma_usart1_tx = &(this->hdma_usart_tx);

			this->huart.Instance = USART1;

		    this->hdma_usart_tx.Instance = DMA2_Stream7;
		    this->hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;

			break;
#if NUMBER_OF_USART > 1
		case USART_MODULE_2:
			__DMA1_CLK_ENABLE();

			HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 2, 0);
			HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

			huart2 = &(this->huart);
			hdma_usart2_tx = &(this->hdma_usart_tx);

			this->hdma_usart_tx.Instance = DMA1_Stream6;
			this->hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;

			this->huart.Instance = USART2;
			break;
#endif
		default:
			ret = -1;
			break;
	}

	if (ret == 0)
	{
		this->huart.Init.BaudRate = baudrate;
		this->huart.Init.WordLength = UART_WORDLENGTH_8B;
		this->huart.Init.StopBits = UART_STOPBITS_1;
		this->huart.Init.Parity = UART_PARITY_NONE;
		this->huart.Init.Mode = UART_MODE_TX_RX;
		this->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		this->huart.Init.OverSampling = UART_OVERSAMPLING_16;
		HAL_UART_Init(&(this->huart));

		this->hdma_usart_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
		this->hdma_usart_tx.Init.PeriphInc = DMA_PINC_DISABLE;
		this->hdma_usart_tx.Init.MemInc = DMA_MINC_ENABLE;
		this->hdma_usart_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		this->hdma_usart_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		this->hdma_usart_tx.Init.Mode = DMA_NORMAL;
		this->hdma_usart_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
		this->hdma_usart_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	    HAL_DMA_Init(&(this->hdma_usart_tx));

	    __HAL_LINKDMA(&huart,hdmatx,hdma_usart_tx);

		HAL_UART_Receive_IT(&(this->huart), (uint8_t *)&(this->CurrentChar), 1);
	}

	return ret;
}

void Deinitialization()
{

}

void UsartInstance::Configuration(unsigned int command, void* arg)
{

}

unsigned int UsartInstance::Available(void)
{
	return USARTRxQueue.Available(); //UserRxSize;
}

unsigned int UsartInstance::Write(char *source, unsigned int size)
{
	uint8_t *pTemp = (uint8_t *)source;

	HAL_UART_Transmit_DMA(&(this->huart), pTemp, size);

	return size;
}

unsigned int UsartInstance::Read(char *destination, unsigned int size)
{
	unsigned char *pTemp = (unsigned char *)destination;
	unsigned int result = size;

	if (result > this->USARTRxQueue.Available())
	{
		result = this->USARTRxQueue.Available();
	}

	this->USARTRxQueue.ReadToArray(pTemp, result);

	return result;
}

unsigned int UsartInstance::Print(char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = strlen(source);

	pTemp = (char* )pvPortMalloc(strlen(source));

	if(pTemp != NULL)
	{
		strcpy(pTemp, source);

		this->Write(pTemp, size);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int UsartInstance::Print(int source)
{
	char pTemp[4];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d", source);

	if( size > 0)
	{
		this->Write(pTemp, size);

		result = size;

	}

	return result;
}

unsigned int UsartInstance::Println(char* source)
{
	char *pTemp;
	unsigned int result = 0;
	unsigned int size = 0;

	pTemp = (char *) pvPortMalloc(strlen(source) + 2);

	if (pTemp != NULL)
	{
		strcpy(pTemp, source);
		strcat(pTemp, "\n");

		size = strlen(pTemp);

		this->Write(pTemp, size);

		result = size;

		vPortFree(pTemp);
	}

	return result;
}

unsigned int UsartInstance::Println(int source)
{
	char pTemp[6];
	unsigned int result = 0;
	unsigned int size = 0;

	size = sprintf(pTemp, "%d\n", source);

	if(size > 0)
	{
		this->Write(pTemp, size);

		result = size;
	}

	return result;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		USARTObj1.USARTRxQueue.Write(USARTObj1.CurrentChar);
		HAL_UART_Receive_IT(huart, (uint8_t *)&(USARTObj1.CurrentChar), 1);
	}

	if (huart->Instance == USART2)
	{
		USARTObj2.USARTRxQueue.Write(USARTObj2.CurrentChar);
		HAL_UART_Receive_IT(huart, (uint8_t *)&(USARTObj2.CurrentChar), 1);
	}

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	__HAL_UART_CLEAR_PEFLAG(huart);
}


/* STM32Cube HAL function **********************************************/
/**
* @brief This function handles USART1 global interrupt.
*/
void USART1_IRQHandler(void)
{
  HAL_UART_IRQHandler(huart1);
}

/**
* @brief This function handles DMA2 Stream7 global interrupt.
*/
void DMA2_Stream7_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_usart1_tx);
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(huart2);
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  HAL_DMA_IRQHandler(hdma_usart2_tx);
}

