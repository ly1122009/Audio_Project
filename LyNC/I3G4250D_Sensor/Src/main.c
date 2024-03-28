#include "stm32f4xx.h"
#include "ModuleI3G4250D.h"

I3G4250D_Output_uint8_t I3G4250D_Data;

void Delay_temp(void);
void Delay_temp(void)
{
	volatile int i = 0;
	for (i = 0; i < 500; i++);
}


int main(void)
{
	if (I3G4250D_Init() == I3G4250D_Result_Error)
	{
		while(1);
	}
	
  while (1)
  {
	Delay_temp();
	I3G4250D_Read(&I3G4250D_Data);
  }
}
