	Requirement				
		1. Use the STM32F4 discovery board				
		2. Module hardware use in the project				
		- UART			-> print the log while running			
		- BUTTON		-> play/stop the music, skip/pause the song			
		- LED			-> show the status of playing song. status program			
		- AUDIO			-> output the audio			
		- USB OTG		-> read the song			
		- Motion sensor	-> change the volume			
		3. Use the IDE KEIL C and the periperal standard library				
		4. The project use the RTOS to implement							
					
	User story				
		1. At the startup 2s:				
			- Blink all the LED every 0.2s				
			- Send the message to PC "Startup state"				
			- Read the data from motion sensor				
			- Read the data from USB				
			- Send the initial sound to audio				
		2. Running state:				
			- Press the Button one time for start/stop				
			- Press the button twice to skip the song				
			- Press the button 3 times to pause the song				
			- Hold the button for 3s to reject the USB				
		3. The motion sensor for increase/decrease the volume				
			- the Y axis is for incease/decrease the volume				
			- The X axis (shaking) for next/previous song				
			- The Z axis is for running the song faster/normal				
			4. The log file will be written into the USB as file log				
		5. The LED is blink while running				
			- 1s if doesnt play any song				
			- 0.5s if playing the song				
		6. Audio				
			- if the USB doesnt plug in, and button press, the audio "the USB doesnt plug" is speak				
			- Output the audio from USB				
			- Speak the sound Peak when button press
	
	Role:
		ChungVB:
			- Setup I2S Audio
			- Setup FreeRTOS
		TaiNT:
			- Setup USB (Not finish)
		TuanLDM:
			- Setup USART
			- Responsible for coding following requirement based on module which was Setup by colleagues
		LyNC (Team lead): 
			- Setup Standard Library for STM32F411E
			- Setup GPIO Led, Button
			- Setup SPI Motion Sensor
			- Review source code and support team to test and fix bug.
			- Check and re-edit the source to clean code.	
				