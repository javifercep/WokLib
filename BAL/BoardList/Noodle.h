/**
  ******************************************************************************
  * @file    Noodle.h
  * @brief   This file contains Noodle board description.
  *******************************************************************************
  */

#ifndef NOODLE_H_
#define NOODLE_H_

/* Exported define ------------------------------------------------------------*/
/* GPIO *******************/
#define NUMBER_OF_GPIO					20

#define PIN1							0
#define PIN1_PIN						GPIO_PIN_8
#define PIN1_PORT						GPIOA

#define PIN2							1
#define PIN2_PIN						GPIO_PIN_10
#define PIN2_PORT						GPIOA

#define PIN3							2
#define PIN3_PIN						GPIO_PIN_9
#define PIN3_PORT						GPIOA

#define PIN5							3
#define PIN5_PIN						GPIO_PIN_3
#define PIN5_PORT						GPIOB

#define PIN6							4
#define PIN6_PIN						GPIO_PIN_7
#define PIN6_PORT						GPIOA

#define PIN7							5
#define PIN7_PIN						GPIO_PIN_4
#define PIN7_PORT						GPIOB

#define PIN8							6
#define PIN8_PIN						GPIO_PIN_15
#define PIN8_PORT						GPIOA

#define PIN10							7
#define PIN10_PIN						GPIO_PIN_8
#define PIN10_PORT						GPIOB

#define PIN11							8
#define PIN11_PIN						GPIO_PIN_9
#define PIN11_PORT						GPIOB

#define PIN13							9
#define PIN13_PIN						GPIO_PIN_4
#define PIN13_PORT						GPIOA

#define PIN15                           10
#define PIN15_PIN                       GPIO_PIN_6
#define PIN15_PORT                      GPIOA

#define PIN16                           11
#define PIN16_PIN                       GPIO_PIN_6
#define PIN16_PORT                      GPIOC

#define PIN17                           12
#define PIN17_PIN                       GPIO_PIN_4
#define PIN17_PORT                      GPIOC

#define PIN18                           13
#define PIN18_PIN                       GPIO_PIN_7
#define PIN18_PORT                      GPIOB

#define PIN20                           14
#define PIN20_PIN                       GPIO_PIN_6
#define PIN20_PORT                      GPIOB

#define PIN21                           15
#define PIN21_PIN                       GPIO_PIN_13
#define PIN21_PORT                      GPIOC

#define PIN23                           16
#define PIN23_PIN                       GPIO_PIN_14
#define PIN23_PORT                      GPIOC

#define PIN24                           17
#define PIN24_PIN                       GPIO_PIN_1
#define PIN24_PORT                      GPIOC

#define PIN26                           18
#define PIN26_PIN                       GPIO_PIN_2
#define PIN26_PORT                      GPIOA

#define PIN27                           19
#define PIN27_PIN                       GPIO_PIN_5
#define PIN27_PORT                      GPIOC

#define PIN_PORT_ARRAY                  {PIN1_PORT,  PIN2_PORT,  PIN3_PORT,\
                                         PIN5_PORT,  PIN6_PORT,  PIN7_PORT,\
                                         PIN8_PORT,  PIN10_PORT, PIN11_PORT,\
                                         PIN13_PORT, PIN15_PORT, PIN16_PORT,\
                                         PIN17_PORT, PIN18_PORT, PIN20_PORT,\
                                         PIN21_PORT, PIN23_PORT, PIN24_PORT,\
                                         PIN26_PORT, PIN27_PORT}

#define PIN_PIN_ARRAY                   {PIN1_PIN,  PIN2_PIN,  PIN3_PIN,\
                                         PIN5_PIN,  PIN6_PIN,  PIN7_PIN,\
                                         PIN8_PIN,  PIN10_PIN, PIN11_PIN,\
                                         PIN13_PIN, PIN15_PIN, PIN16_PIN,\
                                         PIN17_PIN, PIN18_PIN, PIN20_PIN,\
                                         PIN21_PIN, PIN23_PIN, PIN24_PIN,\
                                         PIN26_PIN, PIN27_PIN}

/* LEDS ***********/
#define NUMBER_OF_LEDS					4

#define LED1							0
#define LED1_PIN						GPIO_PIN_7
#define LED1_PORT						GPIOC

#define LED2							1
#define LED2_PIN						GPIO_PIN_6
#define LED2_PORT						GPIOC

#define LED3							2
#define LED3_PIN						GPIO_PIN_7
#define LED3_PORT						GPIOB

#define LED4							3
#define LED4_PIN						GPIO_PIN_6
#define LED4_PORT						GPIOB

#define LED_PORT_ARRAY                  {LED1_PORT, LED2_PORT,\
                                         LED3_PORT, LED4_PORT}

#define LED_PIN_ARRAY                   {LED1_PIN, LED2_PIN,\
                                         LED3_PIN, LED4_PIN}

/* ADC **********************************************/
#define NUMBER_OF_AN_INPUTS				5

#define A1								0
#define AN1_PIN							GPIO_PIN_1
#define AN1_PORT						GPIOC

#define A2								1
#define AN2_PIN							GPIO_PIN_2
#define AN2_PORT						GPIOA

#define A3								2
#define AN3_PIN							GPIO_PIN_6
#define AN3_PORT						GPIOA

#define A4								3
#define AN4_PIN							GPIO_PIN_4
#define AN4_PORT						GPIOC

#define A5								4
#define AN5_PIN							GPIO_PIN_5
#define AN5_PORT						GPIOC

#define AN_PORT_ARRAY                  {AN1_PORT, AN2_PORT,\
                                        AN3_PORT, AN4_PORT,\
                                        AN5_PORT}

#define AN_PIN_ARRAY                   {AN1_PIN, AN2_PIN, AN3_PIN,\
                                        AN4_PIN, AN5_PIN}

/* PWM defines ************/
#define NUMBER_OF_TIMER_USED            2

#define TIMER_INSTANCE_1                0
#define TIMER_INSTANCE_2                1

#define TIMER_USED_1                    TIM3
#define TIMER_USED_2                    TIM4

#define TIMER_USED_ARRAYS               {TIM3, TIM4}

#define ATTACHED_OUT_TO_TIMER_1         2
#define ATTACHED_OUT_TO_TIMER_2         2

#define ATTACHED_OUT_PER_TIMER_ARRAY    {ATTACHED_OUT_TO_TIMER_1, ATTACHED_OUT_TO_TIMER_2}

#define OUT_TO_TIMER_MAPPING_1_ARRAY    {TIM_CHANNEL_1, TIM_CHANNEL_2}
#define OUT_TO_TIMER_MAPPING_2_ARRAY    {TIM_CHANNEL_1, TIM_CHANNEL_2}

#define NUMBER_OF_PWM                   4

#define PWM1                            0
#define PWM1_PIN                        GPIO_PIN_7
#define PWM1_PORT                       GPIOC
#define PWM1_TIM_INSTANCE               TIMER_INSTANCE_1
#define PWM1_TIM_CHANNEL                TIM_CHANNEL_2

#define PWM2                            1
#define PWM2_PIN                        GPIO_PIN_6
#define PWM2_PORT                       GPIOC
#define PWM2_TIM_INSTANCE               TIMER_INSTANCE_1
#define PWM2_TIM_CHANNEL                TIM_CHANNEL_1

#define PWM3                            2
#define PWM3_PIN                        GPIO_PIN_7
#define PWM3_PORT                       GPIOB
#define PWM3_TIM_INSTANCE               TIMER_INSTANCE_2
#define PWM3_TIM_CHANNEL                TIM_CHANNEL_2

#define PWM4                            3
#define PWM4_PIN                        GPIO_PIN_6
#define PWM4_PORT                       GPIOB
#define PWM4_TIM_INSTANCE               TIMER_INSTANCE_2
#define PWM4_TIM_CHANNEL                TIM_CHANNEL_1

#define PWM_PORT_ARRAY                  {PWM1_PORT, PWM2_PORT,\
                                         PWM3_PORT, PWM4_PORT}

#define PWM_PIN_ARRAY                   {PWM1_PIN, PWM2_PIN,\
                                         PWM3_PIN, PWM4_PIN}

#define PWM_INSTANCE_ARRAY              {PWM1_TIM_INSTANCE, PWM2_TIM_INSTANCE,\
                                         PWM3_TIM_INSTANCE, PWM4_TIM_INSTANCE}

#define PWM_TIM_CHANNEL_ARRAY           {PWM1_TIM_CHANNEL, PWM2_TIM_CHANNEL,\
                                         PWM3_TIM_CHANNEL, PWM4_TIM_CHANNEL}

/* USART defines ********/
#define NUMBER_OF_USART					2

#define DFLT_USART_BAUDRATE				115200

#define USART_USED_1                    UART4
#define USART_USED_2                    USART1

#define USARTTX1_PIN                    GPIO_PIN_0
#define USARTTX1_PORT                   GPIOA

#define USARTRX1_PIN                    GPIO_PIN_1
#define USARTRX1_PORT                   GPIOA

#define USARTCK2_PIN                    GPIO_PIN_8
#define USARTCK2_PORT                   GPIOA

#define USARTTX2_PIN                    GPIO_PIN_9
#define USARTTX2_PORT                   GPIOA

#define USARTRX2_PIN                    GPIO_PIN_10
#define USARTRX2_PORT                   GPIOA
/* SPI defines ********/
#define NUMBER_OF_SPI                   1

#define SPI_USED_1                      SPI1

#define SPICLK1_PIN                     GPIO_PIN_3
#define SPICLK1_PORT                    GPIOB

#define SPIMOSI1_PIN                    GPIO_PIN_7
#define SPIMOSI1_PORT                   GPIOA

#define SPIMISO1_PIN                    GPIO_PIN_4
#define SPIMISO1_PORT                   GPIOB

#define SPINSS1                         PIN8

/* USB defines ********/
#define USB_HS_SPEED

#define NUMBER_OF_USB_CLASS				1

#if NUMBER_OF_USB_CLASS > 0
#define USB_CDC_CLASS					1
#endif
#if NUMBER_OF_USB_CLASS > 1
#define USB_MSD_CLASS					2
#endif
#if NUMBER_OF_USB_CLASS > 2
#define USB_DFU_CLASS					3
#endif

/* RTOS defines ********/
#define RTOS_SUPPORTED					1

#define NUMBER_USER_TASKS				10

/* uSD defines *******/
#define SD_SUPPORTED                    1

#define SD_CD_PIN                       GPIO_PIN_2
#define SD_CD_PORT                      GPIOB

#endif
