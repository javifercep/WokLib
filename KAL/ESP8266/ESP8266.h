/**
  ******************************************************************************
  * @file    ESP8266.h
  * @brief   This file contains USART API.
  *******************************************************************************
  */

#ifndef ESP8266_H_
#define ESP8266_H_

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"

/* Exported define ------------------------------------------------------------*/
#ifdef KRAKOSKI_BOARD
#define ESP_CE			PIN7
#define ESP_RST			PINRST_ESP
#define ESP_GPIO0		PINA4
#define ESP_GPIO2		PIN4
#endif

#ifdef NOODLE_BOARD
#define ESP_CE          PIN7
#define ESP_RST         PIN8
#define ESP_GPIO0       PIN6
#define ESP_GPIO2       PIN5
#endif

#define ESP_USART		USART_MODULE_1
#define USARTInst		USARTObj1
#define ESP_BAUDRATE	115200

/* Exported typedef ------------------------------------------------------------*/

/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class ESP8266Instance {
public:
	ESP8266Instance(void);
	~ESP8266Instance(void);
	void Initialization(void);
	void StartConfigMode(void);
	void StopConfigMode(void);
	void ConfigWrite(char *pdata, unsigned int size);
	void ConfigRead(char *pdata, unsigned int *size);
	unsigned int Available(void);
	unsigned int Write(char *source, unsigned int size);
	unsigned int Read(char *destination, unsigned int size);
	unsigned int Print(char* source);
	unsigned int Print(int source);
	unsigned int Println(char * source);
	unsigned int Println(int source);
};

extern ESP8266Instance ESP8266;

#endif /* USART_H_ */
