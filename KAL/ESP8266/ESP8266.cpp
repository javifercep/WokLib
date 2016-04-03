/**
 ******************************************************************************
 * @file    ESP8266.cpp
 * @brief   This file contains ESP8266 API.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "ESP8266/ESP8266.h"

#include <stdio.h>
#include <string.h>

/* Global variables ----------------------------------------------------------*/
ESP8266Instance ESP8266;

/* Private variables ---------------------------------------------------------*/
osThreadId ESP8266ConfigTaskID;

osMutexId USBMutexHandle;
osMessageQId ESP8266TxTaskQueueHandle;
osMessageQId ESP8266RxTaskQueueHandle;

/* Private function prototypes -----------------------------------------------*/
static void ESP8266ConfigTask(void const * argument);

/* Create a new task reference */
NewTask(ESP8266ConfigTask);

/* definition and creation of ESP8266 Queues */
osMessageQDef(ESP8266TxTaskQueue, 64, uint8_t);
osMessageQDef(ESP8266RxTaskQueue, 64, uint8_t);


/* Private function **********************************************************/
/**
 * @brief  Initializes Tibuboard LEDs and Buttons.
 * @param  None
 * @retval None
 */
ESP8266Instance::ESP8266Instance(void)
{

}

ESP8266Instance::~ESP8266Instance(void)
{

}

void ESP8266Instance::Initialization()
{
  ESP8266TxTaskQueueHandle = osMessageCreate(osMessageQ(ESP8266TxTaskQueue), NULL);
  ESP8266RxTaskQueueHandle = osMessageCreate(osMessageQ(ESP8266RxTaskQueue), NULL);
  /* Set the ESP8266 reset to low to disable the ESP */
  GPIO.Mode(ESP_RST, OUTPUT_OPENDRAIN);
  GPIO.Write(ESP_RST, LOW);

  /* Set the GPIO0, GPIO2 and CE pins in order to enter in normal boot */
  GPIO.Mode(ESP_GPIO0, INPUT_PULLUP);
  GPIO.Mode(ESP_GPIO2, INPUT_PULLUP);
  GPIO.Mode(ESP_CE, OUTPUT_PULLUP);
  GPIO.Write(ESP_CE, HIGH);

  /* Release the reset to initialize the ESP */
  GPIO.Write(ESP_RST, HIGH);

  /* Wait for ESP initialization */
  HAL_Delay(1000);
  /* Initialize USART module */
  USARTInst.Initialization(ESP_USART, ESP_BAUDRATE);

}

void ESP8266Instance::StartConfigMode(void)
{
  ESP8266ConfigTaskID = RTOS.CreateTask(TaskRef(ESP8266ConfigTask), NULL);
}

void ESP8266Instance::StopConfigMode(void)
{
  RTOS.DeleteTask(ESP8266ConfigTaskID);
}

void ESP8266Instance::ConfigWrite(char *pdata, unsigned int size)
{
  unsigned int ii;
  uint8_t *pTemp = (uint8_t *)pdata;

  for (ii = 0; ii < size; ii++)
  {
    osMessagePut(ESP8266RxTaskQueueHandle, pTemp[ii], 0);
  }
}

void ESP8266Instance::ConfigRead(char *pdata, unsigned int *size)
{
  osEvent QueueResult;
  uint8_t *pTemp = (uint8_t *) pdata;
  uint32_t MsgSize = 0;

  do
  {
    QueueResult = osMessageGet(ESP8266TxTaskQueueHandle, 0);
    if (QueueResult.status == osEventMessage)
    {
      *pTemp = (char)QueueResult.value.v;
      pTemp++;
      MsgSize++;
    }
  }while (QueueResult.status == osEventMessage);

  *size = MsgSize;
}

unsigned int ESP8266Instance::Available(void)
{
  return USARTInst.Available();
}

unsigned int ESP8266Instance::Write(char *source, unsigned int size)
{
  char *pTemp = source;

  USARTInst.Write(pTemp, size);

  return size;
}

unsigned int ESP8266Instance::Read(char *destination, unsigned int size)
{
  char *pTemp = destination;
  unsigned int result = size;

  if (result > USARTInst.Available())
  {
    result = USARTInst.Available();
  }

  USARTInst.Read(pTemp, result);

  return result;
}

unsigned int ESP8266Instance::Print(char* source)
{
  char *pTemp;
  unsigned int result = 0;
  unsigned int size = strlen(source);

  pTemp = (char*) pvPortMalloc(strlen(source));

  if (pTemp != NULL)
  {
    strcpy(pTemp, source);

    this->Write(pTemp, size);

    result = size;

    vPortFree(pTemp);
  }

  return result;
}

unsigned int ESP8266Instance::Print(int source)
{
  char pTemp[4];
  unsigned int result = 0;
  unsigned int size = 0;

  size = sprintf(pTemp, "%d", source);

  if (size > 0)
  {
    this->Write(pTemp, size);

    result = size;

  }

  return result;
}

unsigned int ESP8266Instance::Println(char* source)
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

unsigned int ESP8266Instance::Println(int source)
{
  char pTemp[6];
  unsigned int result = 0;
  unsigned int size = 0;

  size = sprintf(pTemp, "%d\n", source);

  if (size > 0)
  {
    this->Write(pTemp, size);

    result = size;
  }

  return result;
}

static void ESP8266ConfigTask(void const * argument)
{
  osEvent QueueResult;
  char Question1[64];
  char Question2[64];
  unsigned int size;
  unsigned int ii;

  /* Infinite loop */
  for (;;)
  {
    ii = 0;
    do
    {
      QueueResult = osMessageGet(ESP8266RxTaskQueueHandle, 0);
      if (QueueResult.status == osEventMessage)
      {
        Question1[ii] = (char)QueueResult.value.v;
        ii++;
      }
    }while (QueueResult.status == osEventMessage);

    if (ii > 0)
    {
      USARTInst.Write(Question1, ii);
    }

    size = USARTInst.Available();
    if (size > 0)
    {
      USARTInst.Read(Question2, size);

      for (ii = 0; ii < size; ii++)
      {
        osMessagePut(ESP8266TxTaskQueueHandle, Question2[ii],0);
      }
    }

    osDelay(10);
  }
}

