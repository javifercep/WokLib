/**
  ******************************************************************************
  * @file    Krakoski.h
  * @brief   This file contains krakoski board description.
  *******************************************************************************
  */

#ifndef KRAKOSKI_H_
#define KRAKOSKI_H_

/* Exported define ------------------------------------------------------------*/
/* GPIO *******************/
#define NUMBER_OF_GPIO					25

#define PIN0							0
#define PIN0_PIN						GPIO_PIN_2
#define PIN0_PORT						GPIOA

#define PIN1							1
#define PIN1_PIN						GPIO_PIN_3
#define PIN1_PORT						GPIOA

#define PIN2							2
#define PIN2_PIN						GPIO_PIN_7
#define PIN2_PORT						GPIOC

#define PIN3							3
#define PIN3_PIN						GPIO_PIN_4
#define PIN3_PORT						GPIOB

#define PIN4							4
#define PIN4_PIN                        GPIO_PIN_13
#define PIN4_PORT						GPIOC

#define PIN5							5
#define PIN5_PIN						GPIO_PIN_5
#define PIN5_PORT						GPIOB

#define PIN6							6
#define PIN6_PIN						GPIO_PIN_11
#define PIN6_PORT						GPIOB

#define PIN7							7
#define PIN7_PIN						GPIO_PIN_1
#define PIN7_PORT						GPIOA

#define PIN8							8
#define PIN8_PIN						GPIO_PIN_15
#define PIN8_PORT						GPIOA

#define PIN9							9
#define PIN9_PIN						GPIO_PIN_10
#define PIN9_PORT						GPIOB

#define PIN10							10
#define PIN10_PIN						GPIO_PIN_2
#define PIN10_PORT						GPIOB

#define PIN11							11
#define PIN11_PIN						GPIO_PIN_6
#define PIN11_PORT						GPIOA

#define PIN12							12
#define PIN12_PIN						GPIO_PIN_7
#define PIN12_PORT						GPIOA

#define PIN13							13
#define PIN13_PIN						GPIO_PIN_5
#define PIN13_PORT						GPIOA

#define PINSDA							14
#define PINSDA_PIN						GPIO_PIN_9
#define PINSDA_PORT						GPIOB

#define PINSCL							15
#define PINSCL_PIN						GPIO_PIN_8
#define PINSCL_PORT						GPIOB

#define PINWKUP							16
#define PINWKUP_PIN						GPIO_PIN_0
#define PINWKUP_PORT					GPIOA

#define PINDAC							17
#define PINDAC_PIN						GPIO_PIN_4
#define PINDAC_PORT						GPIOA

#define PINA1							18
#define PINA1_PIN						GPIO_PIN_2
#define PINA1_PORT						GPIOC

#define PINA2							19
#define PINA2_PIN						GPIO_PIN_3
#define PINA2_PORT						GPIOC

#define PINA3							20
#define PINA3_PIN						GPIO_PIN_4
#define PINA3_PORT						GPIOC

#define PINA4							21
#define PINA4_PIN						GPIO_PIN_5
#define PINA4_PORT						GPIOC

#define PINA5							22
#define PINA5_PIN						GPIO_PIN_0
#define PINA5_PORT						GPIOB

#define PINA6							23
#define PINA6_PIN						GPIO_PIN_1
#define PINA6_PORT						GPIOB

#define PINRST_ESP						24
#define PINRST_ESP_PIN					GPIO_PIN_15
#define PINRST_ESP_PORT					GPIOC

#define PIN_PORT_ARRAY                  {PIN0_PORT,   PIN1_PORT,    PIN2_PORT,\
                                         PIN3_PORT,   PIN4_PORT,    PIN5_PORT,\
                                         PIN6_PORT,   PIN7_PORT,    PIN8_PORT,\
                                         PIN9_PORT,   PIN10_PORT,   PIN11_PORT,\
                                         PIN12_PORT,  PIN13_PORT,   PINSDA_PORT,\
                                         PINSCL_PORT, PINWKUP_PORT, PINDAC_PORT,\
                                         PINA1_PORT,  PINA2_PORT,   PINA3_PORT,\
                                         PINA4_PORT,  PINA5_PORT,   PINA6_PORT,\
                                         PINRST_ESP_PORT}

#define PIN_PIN_ARRAY                   {PIN0_PIN,   PIN1_PIN,    PIN2_PIN,\
                                         PIN3_PIN,   PIN4_PIN,    PIN5_PIN,\
                                         PIN6_PIN,   PIN7_PIN,    PIN8_PIN,\
                                         PIN9_PIN,   PIN10_PIN,   PIN11_PIN,\
                                         PIN12_PIN,  PIN13_PIN,   PINSDA_PIN,\
                                         PINSCL_PIN, PINWKUP_PIN, PINDAC_PIN,\
                                         PINA1_PIN,  PINA2_PIN,   PINA3_PIN,\
                                         PINA4_PIN,  PINA5_PIN,   PINA6_PIN,\
                                         PINRST_ESP_PIN}

/* LEDS ***********/
#define NUMBER_OF_LEDS					4

#define LED1							0
#define LED1_PIN						GPIO_PIN_4
#define LED1_PORT						GPIOB

#define LED2							1
#define LED2_PIN						GPIO_PIN_5
#define LED2_PORT						GPIOB

#define LED3							2
#define LED3_PIN						GPIO_PIN_11
#define LED3_PORT						GPIOB

#define LED4							3
#define LED4_PIN						GPIO_PIN_10
#define LED4_PORT						GPIOB

#define LED_PORT_ARRAY                  {LED1_PORT, LED2_PORT,\
                                         LED3_PORT, LED4_PORT}

#define LED_PIN_ARRAY                   {LED1_PIN, LED2_PIN,\
                                         LED3_PIN, LED4_PIN}

/* ADC **********************************************/
#define NUMBER_OF_AN_INPUTS				6

#define A1								2
#define AN1_PIN							GPIO_PIN_2
#define AN1_PORT						GPIOC

#define A2								3
#define AN2_PIN							GPIO_PIN_3
#define AN2_PORT						GPIOC

#define A3								4
#define AN3_PIN							GPIO_PIN_4
#define AN3_PORT						GPIOC

#define A4								5
#define AN4_PIN							GPIO_PIN_5
#define AN4_PORT						GPIOC

#define A5								0
#define AN5_PIN							GPIO_PIN_0
#define AN5_PORT						GPIOB

#define A6								1
#define AN6_PIN							GPIO_PIN_1
#define AN6_PORT						GPIOB

#define AN_PORT_ARRAY                  {AN1_PORT, AN2_PORT,\
                                        AN3_PORT, AN4_PORT,\
                                        AN5_PORT, AN6_PORT}

#define AN_PIN_ARRAY                   {AN1_PIN, AN2_PIN, AN3_PIN,\
                                        AN4_PIN, AN5_PIN, AN6_PIN}

/* PWM defines ************/

/* Initialization parameters */
#define NUMBER_OF_TIMER_USED            2

#define TIMER_INSTANCE_1                0
#define TIMER_INSTANCE_2                1

#define TIMER_USED_1                    TIM2
#define TIMER_USED_2                    TIM3

#define TIMER_USED_ARRAYS               {TIM2, TIM3}

#define ATTACHED_OUT_TO_TIMER_1         2
#define ATTACHED_OUT_TO_TIMER_2         2

#define ATTACHED_OUT_PER_TIMER_ARRAY    {ATTACHED_OUT_TO_TIMER_1, ATTACHED_OUT_TO_TIMER_2}

#define OUT_TO_TIMER_MAPPING_1_ARRAY    {TIM_CHANNEL_3, TIM_CHANNEL_4}
#define OUT_TO_TIMER_MAPPING_2_ARRAY    {TIM_CHANNEL_1, TIM_CHANNEL_2}

#define NUMBER_OF_PWM                   4

#define PWM1                            0
#define PWM1_PIN                        GPIO_PIN_4
#define PWM1_PORT                       GPIOB
#define PWM1_TIM_INSTANCE               TIMER_INSTANCE_2
#define PWM1_TIM_CHANNEL                TIM_CHANNEL_1

#define PWM2                            1
#define PWM2_PIN                        GPIO_PIN_5
#define PWM2_PORT                       GPIOB
#define PWM2_TIM_INSTANCE               TIMER_INSTANCE_2
#define PWM2_TIM_CHANNEL                TIM_CHANNEL_2

#define PWM3                            2
#define PWM3_PIN                        GPIO_PIN_11
#define PWM3_PORT                       GPIOB
#define PWM3_TIM_INSTANCE               TIMER_INSTANCE_1
#define PWM3_TIM_CHANNEL                TIM_CHANNEL_4

#define PWM4                            3
#define PWM4_PIN                        GPIO_PIN_10
#define PWM4_PORT                       GPIOB
#define PWM4_TIM_INSTANCE               TIMER_INSTANCE_1
#define PWM4_TIM_CHANNEL                TIM_CHANNEL_3

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

#define USART_USED_1                    USART1
#define USART_USED_2                    USART2

#define USARTTX1_PIN                    GPIO_PIN_6
#define USARTTX1_PORT                   GPIOB

#define USARTRX1_PIN                    GPIO_PIN_7
#define USARTRX1_PORT                   GPIOB

#define USARTTX2_PIN                    GPIO_PIN_2
#define USARTTX2_PORT                   GPIOA

#define USARTRX2_PIN                    GPIO_PIN_3
#define USARTRX2_PORT                   GPIOA

/* SPI defines ********/
#define NUMBER_OF_SPI                   2

#define SPI_USED_1                      SPI1
#define SPI_USED_2                      SPI2

#define SPICLK1_PIN                     GPIO_PIN_5
#define SPICLK1_PORT                    GPIOA

#define SPIMOSI1_PIN                    GPIO_PIN_7
#define SPIMOSI1_PORT                   GPIOA

#define SPIMISO1_PIN                    GPIO_PIN_6
#define SPIMISO1_PORT                   GPIOA

#define SPINSS1                         PIN10

#define SPICLK2_PIN                     GPIO_PIN_13
#define SPICLK2_PORT                    GPIOC

#define SPIMOSI2_PIN                    GPIO_PIN_15
#define SPIMOSI2_PORT                   GPIOC

#define SPIMISO2_PIN                    GPIO_PIN_14
#define SPIMISO2_PORT                   GPIOC

#define SPINSS2                         PIN7

/* USB defines ********/
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

#define SD_CD_PIN                       GPIO_PIN_1
#define SD_CD_PORT                      GPIOC

#endif
