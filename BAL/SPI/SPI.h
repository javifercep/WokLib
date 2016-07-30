/**
  ******************************************************************************
  * @file    SPI.h
  * @brief   This file contains SPI API.
  *******************************************************************************
  */

#ifndef SPI_H_
#define SPI_H_

/* Includes ------------------------------------------------------------------*/
#include "RTOS/RTOS.h"
#include "TOOLS/BufferFunctions.h"
#include "stm32f2xx_hal.h"

/* Exported define ------------------------------------------------------------*/
#define SPI_MODULE_1  0
#define SPI_MODULE_2  1

#define SPI_BUFFER_SIZE	2047
/* Exported typedef ------------------------------------------------------------*/
/* Exported class ------------------------------------------------------------*/

/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class SPIInstance {
  private:
    osMutexId SPITxMutexHandle;
    osMutexId SPIRxMutexHandle;
  public:
    SPI_HandleTypeDef hspi;
    DMA_HandleTypeDef hdma_hspi_rx;
    DMA_HandleTypeDef hdma_hspi_tx;

	/**
	 *@brief Read Queue. The read CurrentChar values are queued on this
	 *		 variable.
	 */
	Queue SPIRxQueue;
    uint8_t SPI_RXTemp_Buf[SPI_BUFFER_SIZE];
    uint16_t TransferSize;

	SPIInstance(void); 			/**< Instance constructor */
	~SPIInstance(void);			/**< Instance destructor */
	/**
	 * @brief Initializes the selected SPI module
	 * @param module SPI_MODULE_X
	 * @return 0 if OK, negative value otherwise
	 */
	int Initialization(unsigned char module);
	/**
	 * @brief Deinitializes the selected SPI module
	 */
	void Deinitialization();
	/**
	 * @brief Configurates the module
	 * @param command TBD
	 * @param arg TBD
	 */
	void Configuration(unsigned int command, void* arg);
	/**
	 *@brief Returns the number of available read bytes by the SPI
	 *		 interface
	 *@return number of available bytes on the receive buffer
	 */
	unsigned int Available(void);
	/**
	 * @brief Send the buffer source through the SPI interface
	 * @param source pointer to data to be sent
	 * @param size number of bytes to be sent
	 * @return number of the real sent bytes
	 */
	unsigned int Write(char *source, unsigned int size);
	/**
	 * @brief Read the received data from SPI to the buffer destination
	 * @param destination pointer to data to store received data
	 * @param size number of bytes to be read
	 * @return number of real read bytes
	 */
	unsigned int Read(char *destination, unsigned int size);
};

extern SPIInstance SPIObj1;

#endif /* SPI_H_ */
