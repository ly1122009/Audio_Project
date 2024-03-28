/*
** ###################################################################
**     Processor:           STM32F411E DISCOVERY
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 06/03/2024 - 19:58:27
**
**     Abstract:
**         Build DelayLED.h for Stm32f411e Discovery
**
** ###################################################################
*/
#ifndef _DELAYLED_H_
#define _DELAYLED_H_

/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void);

/* 
* Init Timer for Delay_ms function 
* This function just work coreclly at 72Mhz (stm32f103c8t6).
* This function using TIM2 and using interrupt 
*/
void Init_timerDelay(void);

/* Delay_ms Function */
void Delay_ms(int p_Time_ms);

#endif


