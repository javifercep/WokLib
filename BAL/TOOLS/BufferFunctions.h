/**
  ******************************************************************************
  * @file    BufferFunctions.h
  * @author  Javier Fernández Cepeda
  * @brief   The buffer functions tool helps users to manage Circular FIFO buffers.
  *******************************************************************************
  * Copyright (c) 2015, Javier Fernandez. All rights reserved.
  *******************************************************************************
  *
  * @addtogroup Tools
  * @{
  *
  *	@addtogroup Buffer_Tools
  *	@{
*/

#ifndef BUFFERFUNCTIONS_H_
#define BUFFERFUNCTIONS_H_

/* Includes ------------------------------------------------------------------*/

 /* Exported define ------------------------------------------------------------*/
#define QBUF_EMPTY 		0x01 /*!< Frame buffer is empty */
#define QBUF_NOTEMPTY 	0x00 /*!< Frame buffer is not empty */
#define QBUF_FULL  		0x01 /*!< Frame buffer is full */
#define QBUF_NOTFULL	0x00 /*!< Frame buffer is not full */

#define QUEUE_EMPTY		0x01 /*!< Queue is empty */
#define QUEUE_NOTEMPTY	0x00 /*!< Queue is not empty */
#define QUEUE_FULL	 	0x01 /*!< Queue is full */
#define QUEUE_NOTFULL	0x00 /*!< Queue is not full */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Exported classs	 ------------------------------------------------------- */

class Queue {
private:
	unsigned int size;
	unsigned int count;
	unsigned int start;

public:
	unsigned char *Data;

	Queue(void);
	~Queue(void);
	unsigned int 	Alloc 			(unsigned int size);
	unsigned int 	Free 			(void);
	unsigned char 	Read 			(void);
	unsigned char 	Write 			(unsigned char data);
	unsigned int 	WriteFromArray	(unsigned char *pdata, unsigned int size);
	unsigned int 	ReadToArray		(unsigned char *pdata, unsigned int size);
	unsigned char 	IsFull			(void);
	unsigned char 	IsEmpty			(void);
	unsigned int 	Available		(void);

};

class QBuffer {
private:
	unsigned int size;
	unsigned int count;
	unsigned int start;
	Queue		 *QueueList;

public:
	QBuffer(void);
	~QBuffer(void);
	unsigned int 	Alloc 		(unsigned int size);
	unsigned int 	Free 		(void);
	unsigned int 	Read		(unsigned char *pdata, unsigned int size);
	unsigned int 	Write		(unsigned char *pdata, unsigned int size);
	unsigned char 	IsFull		(void);
	unsigned char 	IsEmpty		(void);
	unsigned int 	Available	(void);

};

/**
 * @}
 */
 /**
 * @}
 */

#endif /* GENERALFUNCTIONS_H_ */
