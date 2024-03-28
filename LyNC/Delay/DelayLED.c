/*
** ###################################################################
**     Processor:           STM32F411E DISCOVERY
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 06/03/2024 - 19:58:27
**
**     Abstract:
**         Build DelayLED.c for Stm32f411e Discovery
**
** ###################################################################
*/
#include "stm32f4xx.h"                  // Device header
#include "DelayLED.h"


#define SYS_CLOCK						100000000
#define DELAY_1SECOND 				1000
#define TRUE 		 		  				1
#define VALUE_INIT_0  				0
#define TIM_PRESCALER_84MHZ (8400 - 1)
#define TIM_PERIOD_MS 			(1000 - 1)

/* Variable using count cycle TIM2 */
volatile int msTick = VALUE_INIT_0;

/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void)
{
	/* Check interrupt flag TIM2, if it's RESET value -> Clear it */
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		msTick++;
	}
}

/* 
* Init Timer for Delay_ms function 
* This function just work coreclly at 100Mhz (STM32F411E) 
* This function using TIM2 and using interrupt 
*/
void Init_timerDelay(void)
{
	/* Enable RCC for TIM2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	/* Init TIM2 */
	TIM_TimeBaseInitTypeDef initTimer;
	initTimer.TIM_CounterMode = TIM_CounterMode_Up;
	initTimer.TIM_Prescaler = ((SYS_CLOCK / 1000000) - 1);
	initTimer.TIM_Period = 1000 - 1;
	TIM_TimeBaseInit(TIM2, &initTimer); 
	
	/* Init NVIC for TIM2 */
	NVIC_InitTypeDef initNVIC_Timer;
	initNVIC_Timer.NVIC_IRQChannel = TIM2_IRQn;
	initNVIC_Timer.NVIC_IRQChannelCmd = ENABLE;
	initNVIC_Timer.NVIC_IRQChannelPreemptionPriority = 0;
	initNVIC_Timer.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&initNVIC_Timer);
	
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
	
	/* Enable TIM2 */
	TIM_Cmd(TIM2, ENABLE);
}

/* Delay_ms Function */
void Delay_ms(int p_Time_ms)
{
	volatile int startTick = msTick;
	/* (msTick - startTick) is the value count of timer */
	while ( (msTick - startTick) < p_Time_ms ){}
}


