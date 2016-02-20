/**
  ******************************************************************************
  * @file    USART.h
  * @brief   This file contains USART API.
  *******************************************************************************
  */

#ifndef USART_H_
#define USART_H_

/* Includes ------------------------------------------------------------------*/
#include "TOOLS/BufferFunctions.h"
/* Exported define ------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class UsartInstance {
public:
	char CurrentChar;
	Queue USARTRxQueue;
	UsartInstance(void);
	~UsartInstance(void);
	void Initialization(void);
	void Configuration(unsigned int command, void* arg);
	unsigned int Available(void);
	unsigned int Write(char *source, unsigned int size);
	unsigned int Read(char *destination, unsigned int size);
	unsigned int Print(char* source);
	unsigned int Print(int source);
	unsigned int Println(char * source);
	unsigned int Println(int source);
};

extern UsartInstance USART;

#endif /* USART_H_ */
