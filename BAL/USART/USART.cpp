/**
  ******************************************************************************
  * @file    USART.cpp
  * @brief   This file contains USART API.
  *******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "USART/USART.h"
#include "FreeRTOS.h"
#include "stm32f2xx_hal.h"

#include <stdio.h>
#include <string.h>

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart2_tx;

UsartInstance USART;

/* Private function prototypes -----------------------------------------------*/
void USART1_IRQHandler(void);

/**
  * @brief  Initializes Tibuboard LEDs and Buttons.
  * @param  None
  * @retval None
  */
UsartInstance::UsartInstance(void)
{

}

UsartInstance::~UsartInstance(void)
{

}

void UsartInstance::Initialization(void)
{

	this->USARTRxQueue.Alloc(2047);

	__DMA2_CLK_ENABLE();

	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart1);

	HAL_UART_Receive_IT(&huart1, (uint8_t *)&(this->CurrentChar), 1);

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

	HAL_UART_Transmit_DMA(&huart1, pTemp, size);

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
	USART.USARTRxQueue.Write(USART.CurrentChar);
	HAL_UART_Receive_IT(huart, (uint8_t *)&(USART.CurrentChar), 1);
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	__HAL_UART_CLEAR_PEFLAG(huart);
}

