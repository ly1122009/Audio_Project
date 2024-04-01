# Audio Project on STM32F411VET6 discovery board

Use STM32F411VET6 discovery board to play music from USB

## Table of Contents

1. [About the Project](#about-the-project)
1. [User story](#User-story)
1. [Role](#Role)
1. [Getting Started](#getting-started)
    1. [Building](#building)
1. [Versioning](#versioning)
1. [Further Reading](#further-reading)

## About the Project

1. Module hardware use in the project				
	- UART			-> print the log while running			
	- BUTTON		-> play/stop the music, skip/pause the song			
	- LED			-> show the status of playing song. status program			
	- AUDIO			-> output the audio			
	- USB OTG		-> read the song			
	- Motion sensor	-> change the volume			
2. Use the IDE KEIL C and the periperal standard library				
3. The project use the RTOS to implement

**[Back to top](#table-of-contents)**

## User story
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
4. The log file will be written into the USB as a file log				
5. The LED is blink while running				
	- 1s if doesn't play any song				
	- 0.5s if playing the song				
6. Audio				
	- if the USB doesn't plug in, and the button pressed, the audio "the USB doesn't plug" is speak				
	- Output the audio from USB				
	- Speak the sound Beep when the button press

**[Back to top](#table-of-contents)**

## User story

LyNC: (It's me) 

	- Setup Standard Library for STM32F411VET6

	- Setup GPIO LEDs, Button

	- Setup SPI Motion Sensor

	- Setup FreeRTOS

	- Support team to make file main.c, main.h

ChungVB:

	- Setup I2S Audio

TaiNT:

	- Setup USB (Not finish)

TuanLDM:

	- Setup USART
	- Responsible for coding following requirements based on the module which was set by colleagues

		+ Initial Module

		+ Task 0: Initial
			. Initial sound to audio
			. Send the message to PC "Startup state" (PC -> Using Hercules software)				
			. Read the data from the motion sensor				
			. Read the data from USB
			. Blink all the LEDs every 0.2s
            
		+ Task 1: Using Led to display actions
			. (Start == 1) && (Pause == 0) -> Blink led every 0.5s
			. (Start == 1) && (Pause == 1) -> Blink led every 1.0s
            
		+ Task 2: Get data from the Motion Sensor
			. At a time, only one signal X, Y, or Z with the largest change is received
			. Once the signal is received, it will be temporarily locked for 2 seconds. After this time, the signal can be received again

		+ Task 3: USB

		+ Task 4: Get signal from Button
			. Press a time: 	start/stop
			. Press 2 times:	skip the song
			. Press 3 times: 	pause the song
			. Hold 3s: 			reject the USB
				-> Interval of 2 times of press is 0.7s
		+ Task 5: Audio
				
		+ Task 6: Alarm
			. Speak the sound "Peak" when the button is pressed. if the USB doesn't plug in, and the button pressed, the audio "the USB doesn't plug" is speak
**[Back to top](#table-of-contents)**

## Getting Started

1. ST-Link v2 Programmer
2. Keil C v5
3. KIT STM32F411VET6 DISCOVERY
4. USB-host cable
5. Loudspeaker

Clone the repo as follows:
git clone https://github.com/ly1122009/Audio_Project.git

### Getting the Source


This project is [hosted on GitHub](https://github.com/ly1122009/Audio_Project). You can clone this project directly using this command:
```
git clone https://github.com/ly1122009/Audio_Project.git

```

### Building

Use Keil C v5 -> build-> flash to board

**[Back to top](#table-of-contents)**


## Versioning

This project uses [Original Versioning](https://vedder.se/2012/12/stm32f4-discovery-usb-host-and-mp3-player/). For a list of available versions, see the [repository tag list](https://github.com/vanbwodonk/STM32F4_USB_MP3).


## Further Reading

. https://github.com/mfauzi/STM32F4/tree/master/STM32F4%20Standard%20Peripheral%20Library
. https://www.st.com/resource/en/application_note/an3997-audio-playback-and-recording-using-the-stm32f4discovery-stmicroelectronics.pdf

**[Back to top](#table-of-contents)**




