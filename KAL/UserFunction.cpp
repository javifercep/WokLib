/**
 ******************************************************************************
 * @file    UserFunction.cPP
 * @brief   This file contains Kodillo API.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "ESP8266/ESP8266.h"
#include "TLC5940/TLC5940.h"
#include "stdlib.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
osThreadId UserTaskID;

/* Private function prototypes -----------------------------------------------*/
static void UserTask(void const * argument);

/* Create a new task reference */
ExtendedNewTask(UserTask, osPriorityNormal, 0, 1024)

void UserFunctionSetup(void)
{
  UserTaskID = RTOS.CreateTask(TaskRef(UserTask), NULL);
}

static void UserTask(void const * argument)
{
  char command;
  char dummy;
  char ConfigMode;
  char NewESPdata;
  char Test[6] = "Test\n";
  char CommandBuffer[16];
  char ESPRxBuffer[64];
  char ESPTxBuffer[64];
  unsigned int size;
  unsigned int ESPSize;

  memset(CommandBuffer, 0, 16);
  memset(ESPRxBuffer, 0, 64);
  memset(ESPTxBuffer, 0, 64);

  NewESPdata = 0;
  ConfigMode = 0;

  ESP8266.Initialization();
  TLC5940.Initialization();

  /* Initialize board LEDs for debug purpose */
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  /* Set the initial value of the board LEDs */
  LEDS.Off(LED3);
  LEDS.Off(LED4);

  /* Infinite loop */
  for (;;)
  {
    /* USB to UART converter */
    size = USBObj.Available();
    if (size > 3)
    {
      USBObj.Read(&command, 1);
      USBObj.Read(&dummy, 1);
      size = USBObj.Available();
      USBObj.Read(CommandBuffer, size);

      switch (command)
      {
        case 'c':
          /* Read the message from USB interface */

          if (strcmp(CommandBuffer, "EnableESP\n") == 0)
          {
            ESP8266.StartConfigMode();
            LEDS.On(LED3);
            ConfigMode = 1;
          }
          else if (strcmp(CommandBuffer, "DisableESP\n") == 0)
          {
            ESP8266.StopConfigMode();
            LEDS.Off(LED3);
            ConfigMode = 0;
          }
          else
          {
            USBObj.Println("Incorrect command");
          }
          break;
        case 'e':
          /* Read the message from USB interface */
          size = USBObj.Available();
          memcpy(ESPTxBuffer, CommandBuffer, size);
          NewESPdata = 1;
          break;
        case 't':
          USBObj.Println(Test);
          break;
        case '1':
          TLC5940.WriteLEDData(1, atoi(CommandBuffer));
          break;
        case '2':
          TLC5940.WriteLEDData(2, atoi(CommandBuffer));
          break;
        case '3':
          TLC5940.WriteLEDData(3, atoi(CommandBuffer));
          break;
        case '4':
          TLC5940.WriteLEDData(4, atoi(CommandBuffer));
          break;
        case '5':
          TLC5940.WriteLEDData(5, atoi(CommandBuffer));
          break;
        case '6':
          TLC5940.WriteLEDData(6, atoi(CommandBuffer));
          break;
        case '7':
          TLC5940.WriteLEDData(7, atoi(CommandBuffer));
          break;
        case '8':
          TLC5940.WriteLEDData(8, atoi(CommandBuffer));
          break;
        default:
          break;
      }
      memset(CommandBuffer, 0, 16);
    }

    if (ConfigMode)
    {
      if (NewESPdata)
      {
        ESP8266.ConfigWrite(ESPTxBuffer, size);
        NewESPdata = 0;
      }

      ESPSize = 0;
      ESP8266.ConfigRead(ESPRxBuffer, &ESPSize);
      if (ESPSize > 0)
      {
        USBObj.Write(ESPRxBuffer, ESPSize);
      }
    }
    else
    {
      ESPSize = ESP8266.Available();
      if (ESPSize > 0)
      {
        ESP8266.Read(ESPRxBuffer, ESPSize);
        if (strcmp(ESPRxBuffer, "Breakfast!\n") == 0)
        {
          LEDS.On(LED4);
          ESP8266.Println("Yeeeeeeah!");
        }
        else
        {
          LEDS.Off(LED4);
        }
        USBObj.Write(ESPRxBuffer, ESPSize);
      }
    }

    osDelay(50);
  }
}

