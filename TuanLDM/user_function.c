#include "user_function.h"

MotionSensor_t USER_MotionSensor;

/* Absolutely value*/
uint16_t USER_ABS16b(signed short l_Input_s16){
	if (l_Input_s16 >= 0){
		return l_Input_s16;
	}
	else {
		return (l_Input_s16*(-1));
	}
}

/* Delay_ms Function */
void USER_DelayMs(int p_Time_ms)
{
	volatile int startTick = msTick;
	/* (msTick - startTick) is the value count of timer */
	while ( (msTick - startTick) < p_Time_ms ){}
}

/* Get state button */
void USER_GetStateButton(void){
	if (timeButton == 3000){
		if (pressButton != 0){
			USER_DelayMs(700);	//max interval of 2 times press button
			if (pressButton == 1){
				VariableMode.StartStop_bit ^= 1;
			}
			else if (pressButton == 2){
				VariableMode.Skip_u8++;
			}
			else if (pressButton == 3){
				VariableMode.Pause_bit ^= 1;
			}
			pressButton = 0;
			stateButton = 0;	//Ensure not Error Signal
		}
	}
}


/* process motion sensor */
void USER_GetMotionSensor(void){
	signed short f_DeltaX_s16 = 0;
	signed short f_DeltaY_s16 = 0;
	signed short f_DeltaZ_s16 = 0;
	
	if (timeMotionSensor_u16 == 0){
		I3G4250D_Read(&I3G4250D_Data);

		f_DeltaX_s16 = (I3G4250D_Data.X)*HS_AXIS_X;	/* sensitivity of per Axis is not the same */
		f_DeltaY_s16 = (I3G4250D_Data.Y)*HS_AXIS_Y;	/* sensitivity of per Axis is not the same */
		f_DeltaZ_s16 = (I3G4250D_Data.Z + 15)*HS_AXIS_Z;	/* sensitivity of per Axis is not the same */
	
		if ((USER_ABS16b(f_DeltaX_s16) > HS_AXIS_COMPARE) ||
				(USER_ABS16b(f_DeltaY_s16) > HS_AXIS_COMPARE) || 
				(USER_ABS16b(f_DeltaZ_s16) > HS_AXIS_COMPARE)){
			if ((USER_ABS16b(f_DeltaX_s16) >= USER_ABS16b(f_DeltaY_s16)) && 
					(USER_ABS16b(f_DeltaX_s16) >= USER_ABS16b(f_DeltaZ_s16))){
				if (f_DeltaX_s16 >= 0){
					USER_MotionSensor.ChangeValueX_2bit |= 1u;		// = 01
				}
				else{
					USER_MotionSensor.ChangeValueX_2bit |= 2u;		// = 10
				}
			}
			else if ((USER_ABS16b(f_DeltaY_s16) >= USER_ABS16b(f_DeltaX_s16)) && 
							(USER_ABS16b(f_DeltaY_s16) >= USER_ABS16b(f_DeltaZ_s16))){
				if (f_DeltaY_s16 >= 0){
					USER_MotionSensor.ChangeValueY_2bit |= 1u;		// = 01
				}
				else{
					USER_MotionSensor.ChangeValueY_2bit |= 2u;		// = 10
				}
			}
			else if ((USER_ABS16b(f_DeltaZ_s16) >= USER_ABS16b(f_DeltaX_s16)) && 
							(USER_ABS16b(f_DeltaZ_s16) >= USER_ABS16b(f_DeltaY_s16))){
				if (f_DeltaZ_s16 >= 0){
					USER_MotionSensor.ChangeValueZ_2bit |= 1u;		// = 01
				}
				else{
					USER_MotionSensor.ChangeValueZ_2bit |= 2u;		// = 10
				}
			}
			timeMotionSensor_u16 = 2000;	//2s update date once
		}
	}
}


/* */
void USER_SoundError(const volatile uint8_t *ptr){
	for (unsigned short i=0; i<(512); i++){
		//readSound1_aa[i] = error_sound[i];
		OutputAudioSample(error_sound[*ptr + i]);
	}
}
