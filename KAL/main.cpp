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

  /* It includes the RTOS initiialization, then no more code is needed from this
   * point */
  GPIO.Mode(PIN0, OUTPUT_PULLUP);
  GPIO.Mode(PIN1, OUTPUT_PULLUP);
  GPIO.Mode(PIN2, OUTPUT_PULLUP);
  GPIO.Mode(PIN4, OUTPUT_PULLUP);
  GPIO.Mode(PIN7, OUTPUT_PULLUP);
  GPIO.Mode(PIN8, OUTPUT_PULLUP);

  GPIO.Mode(PIN3, OUTPUT_PULLUP);
  GPIO.Mode(PIN5, OUTPUT_PULLUP);
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  GPIO.Write(PIN0, HIGH);
  GPIO.Write(PIN1, LOW);
  GPIO.Write(PIN2, HIGH);
  GPIO.Write(PIN4, LOW);
  GPIO.Write(PIN7, HIGH);
  GPIO.Write(PIN8, LOW);

  GPIO.Write(PIN3, HIGH);
  GPIO.Write(PIN5, LOW);
  LEDS.On(LED3);
  LEDS.Off(LED4);

  RTOS.Initialization();

  /* Infinite loop */
  while (1)
  {
  }
}

