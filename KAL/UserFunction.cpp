/**
 ******************************************************************************
 * @file    UserFunction.cPP
 * @brief   This file contains Kodillo API.
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "BAPI.h"
#include "ESP8266/ESP8266.h"
#include "string.h"

/* Private variables ---------------------------------------------------------*/
osThreadId UserTaskID;

/* Private function prototypes -----------------------------------------------*/
static void UserTask(void const * argument);

/* Create a new task reference */
ExtendedNewTask(UserTask, osPriorityNormal ,0, 1024)

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

  /* Initialize board LEDs for debug purpose */
  LEDS.Initialization(LED3);
  LEDS.Initialization(LED4);

  GPIO.Mode(PIN0, INPUT_PULLUP);
  GPIO.Mode(PIN1, OUTPUT_OPENDRAIN);
  GPIO.Write(PIN1, LOW);

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

      switch (command)
      {
        case 'c':
          /* Read the message from USB interface */
          USBObj.Read(CommandBuffer, USBObj.Available());

          if (strcmp(CommandBuffer, "EnableESP\n") == 0)
          {
            ESP8266.StartConfigMode();
            LEDS.On(LED3);
            ConfigMode = 1;
          }
          else if(strcmp(CommandBuffer, "DisableESP\n") == 0)
          {
            ESP8266.StopConfigMode();
            LEDS.Off(LED3);
            ConfigMode = 0;
          }
          else
          {
            USBObj.Println("Incorrect command");
          }
          memset(CommandBuffer, 0, 16);
          break;
        case 'e':
          /* Read the message from USB interface */
          size = USBObj.Available();
          USBObj.Read(ESPTxBuffer, size);
          NewESPdata = 1;
          break;
        case 't':
          USBObj.Read(CommandBuffer, USBObj.Available());
          USBObj.Println(Test);
          memset(CommandBuffer, 0, 16);
          break;
        default:
          break;
      }
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
    osDelay(100);
  }
}

