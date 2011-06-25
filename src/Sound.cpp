/*
 * Sound.cpp
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */

#include "Sound.h"


Sound::~Sound() {


}

Sound::Sound() {

	CL_SetupSound setup_sound;
	CL_SetupMikMod setup_mikmod;
	CL_SetupVorbis setup_vorbis;
	CL_SoundOutput output(44100);
	CL_SoundBuffer vorbis("music/Earth.ogg");
	vorbis.play(true);

}
