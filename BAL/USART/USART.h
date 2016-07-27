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
#include "stm32f2xx_hal.h"

/* Exported define ------------------------------------------------------------*/
#define USART_MODULE_1	0
#define USART_MODULE_2	1

#define USART_BUFFER_SIZE	2047
/* Exported typedef ------------------------------------------------------------*/
/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class UsartInstance {
private:
	UART_HandleTypeDef huart;
	DMA_HandleTypeDef hdma_usart_tx;
public:
	/**
	 * @brief Memory container to store the last read message
	 */
	char CurrentChar;
	/**
	 *@brief Read Queue. The read CurrentChar values are queued on this
	 *		 variable.
	 */
	Queue USARTRxQueue;

	UsartInstance(void); 			/**< Instance constructor */
	~UsartInstance(void);			/**< Instance destructor */
	/**
	 * @brief Initializes the selected USART module
	 * @param module USART_MODULE_X
	 * @param baudrate indicates the baud rate in baud/s
	 * @return 0 if OK, negative value otherwise
	 */
	int Initialization(unsigned char module, unsigned int baudrate);
	/**
	 * @brief Deinitializes the selected USART module
	 */
	void Deinitialization();
	/**
	 * @brief Configurates the module
	 * @param command TBD
	 * @param arg TBD
	 */
	void Configuration(unsigned int command, void* arg);
	/**
	 *@brief Returns the number of available read bytes by the USART
	 *		 interface
	 *@return number of available bytes on the receive buffer
	 */
	unsigned int Available(void);
	/**
	 * @brief Send the buffer source through the USART interface
	 * @param source pointer to data to be sent
	 * @param size number of bytes to be sent
	 * @return number of the real sent bytes
	 */
	unsigned int Write(char *source, unsigned int size);
	/**
	 * @brief Read the received data from USART to the buffer destination
	 * @param destination pointer to data to store received data
	 * @param size number of bytes to be read
	 * @return number of real read bytes
	 */
	unsigned int Read(char *destination, unsigned int size);
	/**
	 * @brief Sent a string data through USART interface
	 * @param source string data to be sent
	 * @return number of real sent data
	 */
	unsigned int Print(char* source);
	/**
	 * @brief Sent an integer in ASCII format through USART interface
	 * @param source integer data to be sent
	 * @return number of real sent data
	 */
	unsigned int Print(int source);
	/**
	 * @brief Sent a string data through USART interface
	 * @note The character new line is sent at the end of the string
	 * @param source string data to be sent
	 * @return number of real sent data
	 */
	unsigned int Println(char * source);
	/**
	 * @brief Sent an integer in ASCII format through USART interface
	 * @note The character new line is sent at the end of the string
	 * @param source integer data to be sent
	 * @return number of real sent data
	 */
	unsigned int Println(int source);
};

extern UsartInstance USARTObj1;
extern UsartInstance USARTObj2;

#endif /* USART_H_ */
