/**
  ******************************************************************************
  * @file    BufferFunctions.c
  * @author  Javier Fernández Cepeda
  * @brief   The buffer functions tool helps users to manage Circular FIFO buffers.

  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "BufferFunctions.h"
#include "stm32f2xx_hal_def.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/******* QBuffer ******************************************************/

/**
  * @brief  	Initializes frame container.
  * @param[in]  pContainer: pointer on the frame Container
  * @param[in]  Size: size of the frame Container
  * @retval Allocated size
  */
QBuffer::QBuffer()
{

}

QBuffer::~QBuffer(void)
{
	unsigned int ii;

	for (ii = 0; ii < this->count; ii++)
	{
		vPortFree(&(this->QueueList->Data[(this->start + ii) % this->size]));
	}
	vPortFree(this->QueueList);
	this->QueueList = NULL;
	this->size = 0;
	this->start = 0;
	this->count = 0;
}

unsigned int QBuffer::Alloc(unsigned int size)
{
	this->size = 0;
	this->start = 0;
	this->count = 0;
	this->QueueList = (Queue*)pvPortMalloc(sizeof(Queue)*size);

	if(this->QueueList != NULL)
	{
		this->size = size;
	}

	return this->size;
}

unsigned int QBuffer::Free(void)
{
	unsigned int SizeTemp = this->size;
	unsigned int ii;

	for (ii = 0; ii < this->count; ii++)
	{
		vPortFree(&(this->QueueList->Data[(this->start + ii) % this->size]));
	}
	vPortFree(this->QueueList);
	this->QueueList = NULL;
	this->size = 0;
	this->start = 0;
	this->count = 0;

	return SizeTemp;
}

unsigned int QBuffer::Read(unsigned char *pdata, unsigned int size)
{
    unsigned int SizeTemp;
    unsigned char *pTemp = pdata;

    this->QueueList[this->start].ReadToArray(pTemp, size);

    /*Frees memory reserved during write function*/
    SizeTemp = this->QueueList[this->start].Free();

    this->start = (this->start + 1) % this->size; //update start pointer
    this->count--; //Update data count

    return SizeTemp;
}

unsigned int QBuffer::Write(unsigned char *pdata, unsigned int size)
{
    unsigned int WrittenData = 0;
    unsigned char *pTemp = pdata;
    unsigned int end = (this->start + this->count) % this->size;

    /*Reserves memory to save pData vector*/
    if (this->QueueList[end].Alloc(size) == size)
    {
    	WrittenData = this->QueueList[end].WriteFromArray(pTemp, size);

    	/*OVERWRITE SUPPORTED*/
    	if(this->count == this->size)
    	{
    		this->start = (this->start + 1) % this->size;
    	}
    	else
    	{
    		this->count++;
    	}
    }

    return WrittenData;
}



/******* Queue ******************************************************/
/**
  * @brief  	Initializes frame container.
  * @param[in]  pContainer: pointer on the frame Container
  * @param[in]  Size: size of the frame Container
  * @retval Allocated size
  */
Queue::Queue()
{

}

Queue::~Queue(void)
{
	vPortFree(this->Data);
	this->Data = NULL;
	this->size = 0;
	this->start = 0;
	this->count = 0;
}

unsigned int Queue::Alloc(unsigned int size)
{
	this->size = 0;
	this->start = 0;
	this->count = 0;
	this->Data = (unsigned char *)pvPortMalloc(sizeof(unsigned char)*size);

	if(this->Data != NULL)
	{
		this->size = size;
	}

	return this->size;
}

unsigned int Queue::Free(void)
{
	unsigned int SizeTemp = this->size;

	vPortFree(this->Data);
	this->Data = NULL;
	this->size = 0;
	this->start = 0;
	this->count = 0;

	return SizeTemp;
}

unsigned char Queue::Read(void)
{
	unsigned char temp;

	temp = this->Data[this->start]; 			  //get oldest data in the Container
	this->start = (this->start + 1) % this->size; //update start pointer
	this->count--;						  		  //Update data count

	return temp;
}

unsigned char Queue::Write(unsigned char data)
{
	unsigned int end = (this->start + this->count) % this->size;
	unsigned char isWrittenCorrectly = 1;

	this->Data[end] = data;

	/*OVERWRITE SUPPORTED*/
	if(this->count == this->size)
	{
		this->start=(this->start + 1) % this->size;
		isWrittenCorrectly = 0;
	}
	else
	{
		this->count++;
	}

	return isWrittenCorrectly;
}

unsigned int Queue::ReadToArray(unsigned char *pdata, unsigned int size)
{
    unsigned int CopiedData, ii;

    if(size < this->count)
    {
    	CopiedData = size;
    }
    else
    {
    	CopiedData = this->count;
    }

    for(ii = 0; ii < CopiedData; ii++)
    {
    	pdata[ii] = this->Data[this->start]; 		//get oldest data in the Container
    	this->start=(this->start + 1) % this->size; //update start pointer
    }

    this->count -= CopiedData;	//Update data count

    return CopiedData;
}

unsigned int Queue::WriteFromArray(unsigned char *pdata, unsigned int size)
{
    unsigned int end = (this->start + this->count) % this->size;
    unsigned int CopiedData, ii;

    if(size < this->size - this->count)
    {
    	CopiedData = size;
    }
    else
    {
    	CopiedData = this->size - this->count;
    }

    for(ii = 0; ii < CopiedData; ii++)
    {
    	this->Data[end] = pdata[ii];
    	end = (end + 1) % this->size;
    }

    this->count += CopiedData;

    return CopiedData;
}

