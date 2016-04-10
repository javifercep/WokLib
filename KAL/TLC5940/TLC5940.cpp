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

  GPIO.Mode(TLC_DCPRG, OUTPUT_PULLDOWN);
  GPIO.Mode(TLC_VPRG, OUTPUT_PULLDOWN);
  GPIO.Mode(TLC_BLANK, OUTPUT_PULLUP);
  GPIO.Mode(TLC_XLAT, OUTPUT_PULLUP);

  GPIO.Write(TLC_DCPRG, LOW);
  GPIO.Write(TLC_VPRG, LOW);
  GPIO.Write(TLC_BLANK, HIGH);
  GPIO.Write(TLC_XLAT, LOW);

  PWM.Config(TLC_GSCLK,TLC_GSCLK_PERIOD, TLC_GSCLK_PERIOD >> 1, PWM_POL_STD);
}
