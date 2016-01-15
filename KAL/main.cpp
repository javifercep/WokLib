/**
  ******************************************************************************
  * @file    main.cPP
  * @brief   This file contains Kodillo API.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
/* Private variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


BoardInstance Board;


int main(void)
{

  /* Board and KAPI initialization. */
  Board.Initialization();

  /* It includes the RTOS inicialization, then no more code is needed from this
   * point */
  GPIO.Mode(LED1, OUTPUT_PULLUP);
  GPIO.Mode(LED2, OUTPUT_PULLUP);
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  GPIO.Write(LED1, HIGH);
  GPIO.Write(LED2, LOW);
  LEDS.On(LED3);
  LEDS.Off(LED4);

  RTOS.Initialization();

  /* Infinite loop */
  while (1)
  {
  }
}

