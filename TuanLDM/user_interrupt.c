#include "user_interrupt.h"

volatile uint32_t msTick = 0;
volatile uint8_t pressButton = 0;
volatile uint16_t timeButton = 3000;
volatile uint8_t stateButton = 0; 
volatile uint16_t timeMotionSensor_u16 = 0;

ModeMain_t VariableMode;




/* Interrupt for TIM2 Fucntion */
void TIM2_IRQHandler(void)
{
	/* Check interrupt flag TIM2, if it's RESET value -> Clear it */
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		/* Clear Flag Interrupt */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		
		/* Active */
		/* Timer */
		msTick++;
		
		/* Time of Motion Sensor update data */
		if (timeMotionSensor_u16 > 0){
			timeMotionSensor_u16--;
		}
		
		/* Check button */
		if (stateButton != 0){	//press button
			if (timeButton > 0){
				timeButton--;
			}
			else if (timeButton == 0){
				VariableMode.RejectUSB_bit ^= 1;
				timeButton = 3000;
				//while (stateButton != 0){}	//wait release button
			}
			
		}
		else{	//release button
			/*  */
			if (timeButton < 2980){
				pressButton++;
				if (pressButton > 3){
					pressButton = 3;
				}
				/* press button will be reset on function get button */
			}
			
			/* Reset time Button */
			timeButton = 3000;
			stateButton = 0;	//Ensure not Error Signal
		}
	}
}

/* Interrupt for Button Fucntion */
void EXTI0_IRQHandler(void)
{
	/* Check and clear flag interrupt EXTI4 */
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		/* Clear Flag */
		EXTI_ClearITPendingBit(EXTI_Line0);
		
		/* Active */
		stateButton ^= 1;
	}
}
