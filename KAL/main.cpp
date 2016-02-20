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

  /* Set the ESP8266 reset to low to disable the ESP */
  GPIO.Mode(PINRST_ESP, OUTPUT_OPENDRAIN);
  GPIO.Write(PINRST_ESP, LOW);

  /* Set the GPIO0, GPIO2 and CE pins in order to enter in normal boot */
  GPIO.Mode(PINA4, INPUT_PULLUP);
  GPIO.Mode(PIN4, INPUT_PULLUP);
  GPIO.Mode(PIN7, OUTPUT_PULLUP);
  GPIO.Write(PIN7, HIGH);

  /* Release the reset to initialize the ESP */
  GPIO.Write(PINRST_ESP, HIGH);

  /* Initialize board LEDs for debug purpose */
  GPIO.Mode(PIN3, OUTPUT_PULLUP);
  GPIO.Mode(PIN5, OUTPUT_PULLUP);
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  /* Set the initial value of the board LEDs */
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

