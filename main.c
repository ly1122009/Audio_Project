#include "main.h"



USB_OTG_CORE_HANDLE		USB_OTG_Core;
USBH_HOST				      USB_Host;
RCC_ClocksTypeDef		  RCC_Clocks;
volatile int			    enum_done = 0;
volatile uint32_t i = 0;
volatile uint32_t j = 0;

TaskHandle_t TASK_0 = NULL;
TaskHandle_t TASK_1 = NULL;
TaskHandle_t TASK_2 = NULL;
TaskHandle_t TASK_3 = NULL;
TaskHandle_t TASK_4 = NULL;
TaskHandle_t TASK_5 = NULL;
TaskHandle_t TASK_6 = NULL;

//--------------------------------------------------------------------------------------------------------

int main(){
	/* Init LED */
	Init_LED();
	
	/* Init USART */
	Init_USART();
	
	/* Init TIM2 to use Delay function */
	Init_timerDelay();
	
	/* Button Init */
	Button_init();
	
	/* Init I3G42450D (Motion sensor)*/
	if (I3G4250D_Init() == I3G4250D_Result_Error)
	{
		while(1);
	}
	
	/* Task of Audio Project */
	xTaskCreate(Task0_Init, "TASK_0", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
	xTaskCreate(Task1_Led, "TASK_1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  xTaskCreate(Task2_SenSor, "TASK_2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(Task3_USB, "TASK_3", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(Task4_Button, "TASK_4", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	xTaskCreate(Task5_Audio, "TASK_5", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	xTaskCreate(Task6_Alarm, "TASK_6", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
	
	/*start FREERTOS scheduler*/
  vTaskStartScheduler();
	
	while(1){}	
}

static void Task0_Init(void *pvParameters){
	/* Initial Audio */
	InitializeAudio(Audio44100HzSettings);
	SetAudioVolume(soundVolume);
	
	/* Send ""send massenge to PC “Start state” (UART) */
	USART_sendDataString(USART_StringDataSend_aa);
	
	/* Link led during 2s */
	while (VariableMode.IntialCount_u8 < INITIAL_COUNT){
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(DELAY_200MS);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		vTaskDelay(DELAY_200MS);
		VariableMode.IntialCount_u8++;
	}
	
	/* End Task 0 */
	vTaskDelete(TASK_0);
}

/* Task1_Led */
static void Task1_Led(void *pvParameters){
	while(1){
		if ((VariableMode.StartStop_bit == 1) && (VariableMode.Pause_bit == 0)){	//Playing Song
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			vTaskDelay(DELAY_500MS);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			vTaskDelay(DELAY_500MS);
		}
		else if ((VariableMode.StartStop_bit == 1) && (VariableMode.Pause_bit == 1)){	//No Play any Song
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			vTaskDelay(DELAY_1000MS);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
			vTaskDelay(DELAY_1000MS);
		}
	}
}

/* Task Sensor */
static void Task2_SenSor(void *pvParameters){
	while(1){
		USER_GetMotionSensor();
		vTaskDelay(50);
	}
}

/* Task USB */
void Task3_USB(void *pvParameters){
	while(1){
		/* Test button -> get data from usb and command by button and motion sensor */
		if (VariableMode.StartStop_bit != 0){
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			vTaskDelay(500);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			vTaskDelay(500);
		}
		if (VariableMode.Skip_u8 != 0){
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			vTaskDelay(500);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			vTaskDelay(500);
		}
		if (VariableMode.Pause_bit != 0){
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			vTaskDelay(500);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			vTaskDelay(500);
		}
		
		if ((USER_MotionSensor.ChangeValueX_2bit != 0) ||
				(USER_MotionSensor.ChangeValueY_2bit != 0) ||
				(USER_MotionSensor.ChangeValueZ_2bit != 0)){
					
			/* process requirement */
					
			/* Reset requirement */
			USER_MotionSensor.ChangeValueX_2bit &= ~3;
			USER_MotionSensor.ChangeValueY_2bit &= ~3;
			USER_MotionSensor.ChangeValueZ_2bit &= ~3;
		}
			
		vTaskDelay(10);
	}
}

/* Task Button */
void Task4_Button(void *pvParameters){
	while(1){
		USER_GetStateButton();
		vTaskDelay(10);
	}
}

/* Task Audio */
void Task5_Audio(void *pvParameters){
	while(1){
		if (VariableMode.StartStop_bit != 0){
			if (VariableMode.Pause_bit == 0){
				/* Run Music */

			}
		}
		vTaskDelay(1);
	}
}

/* Task Alarm */
void Task6_Alarm(void *pvParameters){
	while(1){
		
		/*  Speak “Peak” when button is pressed */
		if (timeButton < 3000){	//press button
			/* "Peak" */
			for(i = 0; i < sizeof(beep_sound); i++){	//Length of "Beep" sound is 512 byte 
				OutputAudioSample(beep_sound[i]);
				if ((timeButton == 3000) && (i > 200)){	//i>200 ensure to generate "Beep" sound
					break;
				}
			}
		}
		
		/* (USB is not plug) && (button is pressed)  ->  the audio speak “the USB doesn’t plug” */
		if ((VariableMode.RejectUSB_bit != 0) && (timeButton < 3000)){
			for(i = 0; i < sizeof(error_sound); i++){
				OutputAudioSample(error_sound[i]);
			}
		}
	
		vTaskDelay(1);
	}
}


