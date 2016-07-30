/**
  ******************************************************************************
  * @file    ADC.h
  * @brief   This file contains ADC API for the analog inputs
  * 	     available on board.
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USD_H
#define __USD_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h" /* defines SD_Driver as external */

/* Exported defines	  --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
	uSD_ERROR 		= -1,
	uSD_AVAILABLE 	= 0,
	uSD_BUSY		= 2
}SDStates;
/* Exported variables --------------------------------------------------------*/
/* Exported class-------------------------------------------------------------*/
class uSDInstance {
private:
	SDStates SDStatus;     /* Return value for SD */
	char  	 SDPath[4];   /* SD logical drive path */
	FATFS 	 DiskFatFs; 	  /* File system object for User logical drive */
	FIL   	 FileInstance; /* File object */

public:
	uSDInstance(void);
	~uSDInstance(void);
	void Initialization(void);
	uint8_t MountSD();
	uint8_t UnMountSD();
	uint8_t CreateFile(const TCHAR* path);
	uint8_t DeleteFile();
	uint8_t OpenFile(const TCHAR* path);
	uint8_t CloseFile();
	uint32_t WriteFile(const void *buff, uint32_t Len);
	uint32_t Print(char* source);
	uint32_t Print(const char* source);
	uint32_t Print(int source);
	uint32_t Println(char* source);
	uint32_t Println(const char* source);
	uint32_t Println(int source);
	uint8_t ReadFile();
	uint8_t CreateFolder();
	uint8_t DeleteFolder();
};

/* Exported variables	  --------------------------------------------------------*/
extern uSDInstance uSD;


#endif /*__ADC_H */


