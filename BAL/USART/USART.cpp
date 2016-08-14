/**
  ******************************************************************************
  * @file    USART.cpp
  * @brief   This file contains USART API.
  *******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "USART/USART.h"
#include "BAPI.h"

#include <stdio.h>
#include <string.h>

/* Exported variables --------------------------------------------------------*/
UsartInstance USARTObj1;

#if NUMBER_OF_USART > 1
UsartInstance USARTObj2;
#endif

/* Private variables ---------------------------------------------------------*/
osMutexDef(USART1TxMutex);
osMutexDef(USART1RxMutex);

#if NUMBER_OF_USART > 1
osMutexDef(USART2TxMutex);
osMutexDef(USART2RxMutex);
#endif

/* Private function prototypes -----------------------------------------------*/
#ifdef __cplusplus
 extern "C" {
#endif

/* STM32Cube HAL function prototypes */
void USART1_IRQHandler(void);
void DMA2_Stream7_IRQHandler(void);

void USART2_IRQHandler(void);
void DMA1_Stream6_IRQHandler(void);

void UART4_IRQHandler(void);
void DMA1_Stream2_IRQHandler(void);


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
		    this->USARTTxMutexHandle = osMutexCreate(osMutex(USART1TxMutex));
		    this->USARTRxMutexHandle = osMutexCreate(osMutex(USART1RxMutex));

			this->huart.Instance = USART_USED_1;
			break;

#if NUMBER_OF_USART > 1
		case USART_MODULE_2:
            this->USARTTxMutexHandle = osMutexCreate(osMutex(USART2TxMutex));
            this->USARTRxMutexHandle = osMutexCreate(osMutex(USART2RxMutex));

			this->huart.Instance = USART_USED_2;
			break;
#endif
		default:
			ret = -1;
			break;
	}

	if (ret == 0)
	{
	  if (this->huart.Instance == USART1)
	  {
	    __DMA2_CLK_ENABLE();

        HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

	    this->hdma_usart_tx.Instance = DMA2_Stream7;
	    this->hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;
	  }
	  else if(this->huart.Instance == USART2)
	  {
	    __DMA1_CLK_ENABLE();

        HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

	    this->hdma_usart_tx.Instance = DMA1_Stream6;
	    this->hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;
	  }
	  else if(this->huart.Instance == UART4)
	  {
	    __DMA1_CLK_ENABLE();

        HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

	    this->hdma_usart_tx.Instance = DMA1_Stream2;
	    this->hdma_usart_tx.Init.Channel = DMA_CHANNEL_4;
	  }
	  else
	  {

	  }

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

    osMutexWait(this->USARTTxMutexHandle, 0);
	HAL_UART_Transmit_DMA(&(this->huart), pTemp, size);
	osMutexRelease (this->USARTTxMutexHandle);

	return size;
}

unsigned int UsartInstance::Read(char *destination, unsigned int size)
{
	unsigned char *pTemp = (unsigned char *)destination;
	unsigned int result = size;

	osMutexWait(this->USARTRxMutexHandle, 0);
	if (result > this->USARTRxQueue.Available())
	{
		result = this->USARTRxQueue.Available();
	}

	this->USARTRxQueue.ReadToArray(pTemp, result);
	osMutexWait(this->USARTRxMutexHandle, 0);

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
	if (huart->Instance == USARTObj1.huart.Instance)
	{
		USARTObj1.USARTRxQueue.Write(USARTObj1.CurrentChar);
		HAL_UART_Receive_IT(huart, (uint8_t *)&(USARTObj1.CurrentChar), 1);
	}

	if (huart->Instance == USARTObj2.huart.Instance)
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
  if (USARTObj1.huart.Instance == USART1)
  {
    HAL_UART_IRQHandler(&(USARTObj1.huart));
  }

  if (USARTObj2.huart.Instance == USART1)
  {
    HAL_UART_IRQHandler(&(USARTObj2.huart));
  }
}

/**
* @brief This function handles DMA2 Stream7 global interrupt.
*/
void DMA2_Stream7_IRQHandler(void)
{
  if (USARTObj1.hdma_usart_tx.Instance == DMA2_Stream7)
  {
    HAL_DMA_IRQHandler(&(USARTObj1.hdma_usart_tx));
  }

  if (USARTObj2.hdma_usart_tx.Instance == DMA2_Stream7)
  {
    HAL_DMA_IRQHandler(&(USARTObj2.hdma_usart_tx));
  }
}

/**
* @brief This function handles USART2 global interrupt.
*/
void USART2_IRQHandler(void)
{
  if (USARTObj1.huart.Instance == USART2)
  {
    HAL_UART_IRQHandler(&(USARTObj1.huart));
  }

  if (USARTObj2.huart.Instance == USART2)
  {
    HAL_UART_IRQHandler(&(USARTObj2.huart));
  }
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream6_IRQHandler(void)
{
  if (USARTObj1.hdma_usart_tx.Instance == DMA1_Stream6)
  {
    HAL_DMA_IRQHandler(&(USARTObj1.hdma_usart_tx));
  }

  if (USARTObj2.hdma_usart_tx.Instance == DMA1_Stream6)
  {
    HAL_DMA_IRQHandler(&(USARTObj2.hdma_usart_tx));
  }

}

/**
* @brief This function handles USART2 global interrupt.
*/
void UART4_IRQHandler(void)
{
  if (USARTObj1.huart.Instance == UART4)
  {
    HAL_UART_IRQHandler(&(USARTObj1.huart));
  }

  if (USARTObj2.huart.Instance == UART4)
  {
    HAL_UART_IRQHandler(&(USARTObj2.huart));
  }
}

/**
* @brief This function handles DMA1 stream6 global interrupt.
*/
void DMA1_Stream2_IRQHandler(void)
{
  if (USARTObj1.hdma_usart_tx.Instance == DMA1_Stream2)
  {
    HAL_DMA_IRQHandler(&(USARTObj1.hdma_usart_tx));
  }

  if (USARTObj2.hdma_usart_tx.Instance == DMA1_Stream2)
  {
    HAL_DMA_IRQHandler(&(USARTObj2.hdma_usart_tx));
  }
}

/* ST microelectronics HAL code **********************************/

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  if (huart->Instance == USART1)
  {
    /* Peripheral clock enable */
    __USART1_CLK_ENABLE();

    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;

    /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(USART1_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  }
  else if(huart->Instance==USART2)
  {
    /* Peripheral clock enable */
    __USART2_CLK_ENABLE();

    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;

  /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(USART2_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  }
  else if(huart->Instance==UART4)
  {
    /* Peripheral clock enable */
    __UART4_CLK_ENABLE();

    GPIO_InitStruct.Alternate = GPIO_AF8_UART4;

  /* Peripheral interrupt init*/
    HAL_NVIC_SetPriority(UART4_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
  }

  if (huart->Instance == USART_USED_1)
  {
    GPIO_InitStruct.Pin = USARTTX1_PIN;
    HAL_GPIO_Init(USARTTX1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USARTRX1_PIN;
    HAL_GPIO_Init(USARTRX1_PORT, &GPIO_InitStruct);
  }
#if NUMBER_OF_USART > 1
  else if (huart->Instance == USART_USED_2)
  {
    GPIO_InitStruct.Pin = USARTTX2_PIN;
    HAL_GPIO_Init(USARTTX1_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = USARTRX2_PIN;
    HAL_GPIO_Init(USARTRX1_PORT, &GPIO_InitStruct);
  }
#endif
  else
  {

  }

}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==USART1)
  {
    /* Peripheral clock disable */
    __USART1_CLK_DISABLE();

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(huart->hdmatx);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  }
  else if(huart->Instance==USART2)
  {
    /* Peripheral clock disable */
    __USART2_CLK_DISABLE();

    /* Peripheral DMA DeInit*/
    HAL_DMA_DeInit(huart->hdmatx);

    /* Peripheral interrupt DeInit*/
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  }

  if (huart->Instance == USART_USED_1)
  {
    HAL_GPIO_DeInit(USARTTX1_PORT, USARTTX1_PIN);
    HAL_GPIO_DeInit(USARTRX1_PORT, USARTRX1_PIN);
  }
#if NUMBER_OF_USART > 1
  else if (huart->Instance == USART_USED_2)
  {
    HAL_GPIO_DeInit(USARTTX2_PORT, USARTTX2_PIN);
    HAL_GPIO_DeInit(USARTRX2_PORT, USARTRX2_PIN);
  }
#endif
  else
  {

  }

}
