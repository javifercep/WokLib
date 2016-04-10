/**
  ******************************************************************************
  * @file    TLC5940.h
  * @brief   This file contains TLC5040 Library.
  *******************************************************************************
  */

#ifndef TLC5940_H_
#define TLC5940_H_

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"

/* Exported define ------------------------------------------------------------*/
#define TLC_GSCLK_PERIOD    20 /* = 2 us */

#define TLC_DCPRG	        PIN2
#define TLC_VPRG	        PIN3

#define TLC_GSCLK	        PWM4
#define TLC_BLANK	        PIN10
#define TLC_XLAT	        PIN8

#define TLC_SPI		        USART_MODULE_1
#define SPIInst		        USARTObj1


/* Exported typedef ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class TLC5940Instance {
private:
	//SPIInstance *SPIInst;
public:
	TLC5940Instance(void);
	~TLC5940Instance(void);
	void Initialization(void);
};

extern TLC5940Instance TLC5940;

#endif /* TLC5940_H_ */
