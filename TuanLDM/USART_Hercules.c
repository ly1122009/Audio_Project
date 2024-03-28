#include "USART_Hercules.h"

volatile uint8_t USART_StringDataSend_aa[30] = "Start state";

void Init_USART(void){
/*-------------------- Init UsART ---------------------------*/
	USART_DeInit(USART1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//Enable RCC for USART_1
	
	/* Configure Interrupt for USART_1 */
	NVIC_InitTypeDef init_NVIC_UARTx;
	init_NVIC_UARTx.NVIC_IRQChannel = USART1_IRQn;	//Choose Interrupt of USART_1 to do object
	init_NVIC_UARTx.NVIC_IRQChannelPreemptionPriority = 0;	//main Priority
	init_NVIC_UARTx.NVIC_IRQChannelSubPriority = 0;	//sub Priority
	init_NVIC_UARTx.NVIC_IRQChannelCmd = ENABLE;	//Enable
	NVIC_Init(&init_NVIC_UARTx);	//Init NVIC for USART_1 with above specifications
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* Init USART_1 */
	USART_InitTypeDef init_USARTx;
	init_USARTx.USART_BaudRate = 9600;
	init_USARTx.USART_WordLength = USART_WordLength_8b;
	init_USARTx.USART_Parity = USART_Parity_No;
	init_USARTx.USART_StopBits = USART_StopBits_1;
	init_USARTx.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	init_USARTx.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &init_USARTx);
	USART_Cmd(USART1, ENABLE);
}

void USART_sendDataString(volatile uint8_t* p_Data){
	uint8_t i = 0;
	while (*(p_Data + i) != '\0'){	//NULL = '\0'
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == 0){}
		USART_SendData(USART1, *(p_Data + i));
		i++;
	}
}

