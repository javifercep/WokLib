/**
  ******************************************************************************
  * @file    main.cPP
  * @brief   This file contains Kodillo API.
  *******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "UserFunction.h"
/* Private variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

BoardInstance Board;

int main(void)
{
  /* Board and KAPI initialization. */
  Board.Initialization();

  UserFunctionSetup();

  RTOS.Initialization();

  /* Infinite loop */
  while (1)
  {
  }
}

