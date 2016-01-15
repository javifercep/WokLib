/**
  ******************************************************************************
  * @file    RTOS.h
  * @brief   This file contains RTOS API for the management of the User tasks
  *******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTOS_H
#define __RTOS_H

/* Includes ------------------------------------------------------------------*/

/* Exported defines	  --------------------------------------------------------*/
/* Standard configuration of the GPIO */

/* Exported types ------------------------------------------------------------*/

/* Exported class		  --------------------------------------------------------*/
/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class RTOSInstance {

public:
	RTOSInstance(void);
	~RTOSInstance(void);
	void Initialization(void);
};

/* Exported variables	  --------------------------------------------------------*/
extern RTOSInstance RTOS;

#endif

