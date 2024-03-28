/*
** ###################################################################
**     Processor:           STM32F411E DISCOVERY
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 06/04/2024 - 19:58:27
**
**     Abstract:
**         Build ButtonControl.c for Stm32f411e Discovery
**
** ###################################################################
*/
#include "stm32f4xx.h"                  // Device header
#include "ButtonControl.h"

#define LED_ON 1
#define LED_OFF 0

/* Using show Led state */
volatile int ledState = LED_OFF;
/** 
* This function using EXTI4 of PORTA (PA4) 
* @brief  Init EXTI4 to use the button control 
*/
void Button_init(void)
{
		/* Enable RCC for Port A */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* Enable RCC for EXTI */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	/* Init GPIO input for PA4 */
	GPIO_InitTypeDef initGPIO_4;
	initGPIO_4.GPIO_Mode = GPIO_Mode_IN;  
	initGPIO_4.GPIO_Pin = GPIO_Pin_4;
	initGPIO_4.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &initGPIO_4);									
	
	/* Connect pin PA4 to EXTI4 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4);	
	
	/* Init EXTI for PA4 */
	EXTI_InitTypeDef initEXTI_4;
	initEXTI_4.EXTI_Line = EXTI_Line4;
	initEXTI_4.EXTI_Mode = EXTI_Mode_Interrupt;
	initEXTI_4.EXTI_Trigger = EXTI_Trigger_Rising;
	initEXTI_4.EXTI_LineCmd = ENABLE;
	EXTI_Init(&initEXTI_4);
	
	/* Init NVIC for EXTI of PA4*/
	NVIC_InitTypeDef initNVIC_4;
	initNVIC_4.NVIC_IRQChannel = EXTI4_IRQn;
	initNVIC_4.NVIC_IRQChannelPreemptionPriority = 0;
	initNVIC_4.NVIC_IRQChannelSubPriority = 0;
	initNVIC_4.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&initNVIC_4);
}

void EXTI4_IRQHandler(void)
{
	/* Check and clear flag interrupt EXTI4 */
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line4);
		if (ledState == LED_OFF)
		{
			TURN_ON_LED;
			ledState = LED_ON;
		}
		else if (ledState == LED_ON)
		{
			TURN_OFF_LED;
			ledState = LED_OFF;
		}
		else
		{
		}
	}
}
