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

#define TLC_SPI		        SPI_MODULE_1
#define SPIInst		        SPIObj1


/* Exported typedef ------------------------------------------------------------*/
typedef struct
{
    uint8_t TLCGSData[24];
    uint8_t TLCDCData[12];
}TLCDataInstance;

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class TLC5940Instance {
private:
    TLCDataInstance *TLCLocalData;
public:
	TLC5940Instance(void);
	~TLC5940Instance(void);
	void Initialization(void);
	void Enable(void);
	void Disable(void);
	void WriteGSData(TLCDataInstance *data);
	void WriteDCData(TLCDataInstance *data);
	void WriteLEDData(int LEDNumber, int LEDShine);
	void StoreDCData(void);
};

extern TLC5940Instance TLC5940;

#endif /* TLC5940_H_ */
