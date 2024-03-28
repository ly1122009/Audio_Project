/*
** ###################################################################
**     Processor:           STM32F411E DISCOVERY
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 06/03/2024 - 19:58:27
**
**     Abstract:
**         Build ButtonControl.h for Stm32f411e Discovery
**
** ###################################################################
*/
#ifndef _BUTTONCONTROL_H_
#define _BUTTONCONTROL_H_

#define ALL_LED (GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12)
#define TURN_ON_LED GPIO_SetBits(GPIOD, ALL_LED)
#define TURN_OFF_LED GPIO_ResetBits(GPIOD, ALL_LED)

/** 
* This function using EXTI4 of PORTA (PA4) 
* @brief  Init EXTI4 to use the button control 
*/
void Button_init(void);

/* Interrupt Fucntion: Blink led by using button PA4 */
void EXTI4_IRQHandler(void);

#endif
