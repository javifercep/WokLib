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
#include "FreeRTOS.h"
#include "cmsis_os.h"

/* Exported defines	  --------------------------------------------------------*/
#define DEFAULT_STACK_SIZE  256

#define NewTask(TaskFunction)                                       osThreadDef(TaskFunction, TaskFunction, osPriorityNormal, 0, DEFAULT_STACK_SIZE);
#define MultipleNewTask(TaskFunction, Instances)                    osThreadDef(TaskFunction, TaskFunction, osPriorityNormal, Instances, DEFAULT_STACK_SIZE);
#define ExtendedNewTask(TaskFunction, Priority ,Instances, Size)    osThreadDef(TaskFunction, TaskFunction, Priority, Instances, Size);

#define TaskRef(TaskFunction)                                        osThread(TaskFunction)

/* Exported types ------------------------------------------------------------*/

/* Exported class		  --------------------------------------------------------*/
/**
 *@brief Main board instance. This class offer global board functions
 *       such as initializations.
 */
class RTOSInstance
{
  public:
    RTOSInstance(void);
    ~RTOSInstance(void);
    void
    Initialization(void);
    osThreadId CreateTask(const osThreadDef_t *thread_def, void *argument);
    osStatus DeleteTask(osThreadId TaskID);
};

/* Exported variables	  --------------------------------------------------------*/
extern RTOSInstance RTOS;

#endif

