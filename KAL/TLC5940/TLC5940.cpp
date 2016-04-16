/**
 ******************************************************************************
 * @file    ESP8266.cpp
 * @brief   This file contains ESP8266 API.
 *******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "TLC5940/TLC5940.h"

#include <stdio.h>
#include <string.h>

/* Private defines  ----------------------------------------------------------*/
#define NUMBER_OF_TLC_OUTS  16
/* Global variables ----------------------------------------------------------*/
TLC5940Instance TLC5940;

/* Private variables ---------------------------------------------------------*/

osMutexId TLC5940MutexHandle;
osMessageQId TLC5940TxTaskQueueHandle;
osMessageQId TLC5940RxTaskQueueHandle;

/* Private function prototypes -----------------------------------------------*/

/* Create a new task reference */

/* definition and creation of ESP8266 Queues */
osMessageQDef(TLC5940TxTaskQueue, 64, uint8_t);
osMessageQDef(TLC5940RxTaskQueue, 64, uint8_t);


/* Private function **********************************************************/
/**
 * @brief  Initializes Tibuboard LEDs and Buttons.
 * @param  None
 * @retval None
 */
TLC5940Instance::TLC5940Instance(void)
{

}

TLC5940Instance::~TLC5940Instance(void)
{

}

void TLC5940Instance::Initialization()
{
  TLC5940TxTaskQueueHandle = osMessageCreate(osMessageQ(TLC5940TxTaskQueue), NULL);
  TLC5940RxTaskQueueHandle = osMessageCreate(osMessageQ(TLC5940RxTaskQueue), NULL);

  memset(this->TLCLocalData->TLCDCData, 0, 12);
  memset(this->TLCLocalData->TLCGSData, 0, 24);

  GPIO.Mode(TLC_DCPRG, OUTPUT_PULLDOWN);
  GPIO.Mode(TLC_VPRG, OUTPUT_PULLDOWN);
  GPIO.Mode(TLC_BLANK, OUTPUT_PULLUP);
  GPIO.Mode(TLC_XLAT, OUTPUT_PULLUP);

  GPIO.Write(TLC_DCPRG, LOW);
  GPIO.Write(TLC_VPRG, LOW);
  GPIO.Write(TLC_BLANK, HIGH);
  GPIO.Write(TLC_XLAT, LOW);

  PWM.Config(TLC_GSCLK,TLC_GSCLK_PERIOD, TLC_GSCLK_PERIOD >> 1, PWM_POL_STD);
  SPIInst.Initialization(TLC_SPI);
}

void TLC5940Instance::Enable(void)
{
  GPIO.Write(TLC_BLANK, LOW);
}

void TLC5940Instance::Disable(void)
{
  GPIO.Write(TLC_BLANK, HIGH);
}

void TLC5940Instance::WriteGSData(TLCDataInstance *data)
{
  uint8_t FlushReadBuffer[24];

  this->TLCLocalData = data;
  SPIInst.Write((char *)this->TLCLocalData->TLCGSData, 24);

  while (SPIInst.Available() == 0);
  SPIInst.Read((char *)FlushReadBuffer, SPIInst.Available());

  GPIO.Write(TLC_XLAT, HIGH);
  osDelay(1);
  GPIO.Write(TLC_XLAT, LOW);
}

void TLC5940Instance::WriteDCData(TLCDataInstance *data)
{
  uint8_t FlushReadBuffer[12];

  this->TLCLocalData = data;

  GPIO.Write(TLC_DCPRG, LOW);
  GPIO.Write(TLC_VPRG, HIGH);

  SPIInst.Write((char*)this->TLCLocalData->TLCDCData, 12);
  while (SPIInst.Available() == 0);
  SPIInst.Read((char*)FlushReadBuffer, SPIInst.Available());

  GPIO.Write(TLC_VPRG, LOW);

}

void TLC5940Instance::WriteLEDData(int LEDNumber, int LEDShine)
{
  if (LEDNumber % 2 == 0)
  {
    this->TLCLocalData->TLCGSData[NUMBER_OF_TLC_OUTS - LEDNumber] = (uint8_t)(LEDShine >> 4);
    this->TLCLocalData->TLCGSData[NUMBER_OF_TLC_OUTS - LEDNumber - 1] |= (uint8_t)(LEDShine << 4) & 0xF0;
  }
  else
  {
    this->TLCLocalData->TLCGSData[NUMBER_OF_TLC_OUTS - LEDNumber] |= (uint8_t)(LEDShine >> 8) & 0x0F;
    this->TLCLocalData->TLCGSData[NUMBER_OF_TLC_OUTS - LEDNumber - 1] = (uint8_t)LEDShine;
  }

  this->WriteGSData(this->TLCLocalData);
}

void TLC5940Instance::StoreDCData(void)
{

}
