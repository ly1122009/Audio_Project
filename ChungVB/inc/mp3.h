/*
* File name: mp3.h
* Content: handle the songs
*/

#ifndef _MP3_H_
#define _MP3_H_

#include "main.h"
#include "core_cm4.h"
#include "stm32f4xx_conf.h"
#include "mp3dec.h"
#include "Audio.h"
#include <string.h>
#include "ff.h"

// Private function prototypes
 void AudioCallback(void *context, int buffer);
 uint32_t Mp3ReadId3V2Tag(FIL* pInFile, char* pszArtist,
		uint32_t unArtistSize, char* pszTitle, uint32_t unTitleSize);
 void play_mp3(char* filename);
FRESULT play_directory (const char* path, unsigned char seek);

#endif	/*_MP3_H_*/
