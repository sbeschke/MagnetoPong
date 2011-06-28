/*
 * Sound.h
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */
#ifndef SOUND_H_
#define SOUND_H_

#include <string>
#include <map>
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#include <ClanLib/core.h>

//Hashmap for the effects
typedef std::map<std::string, CL_SoundBuffer*> EffectMap;

class Sound
{
public:
	virtual ~Sound();
	Sound();
	void domLoad(CL_DomElement config);
	void setmusic(std::string filename);
	void play();
	void effect(std::string name);
	void loadeffects(std::map<std::string,std::string> &effects);


private:
	EffectMap effects;

	CL_SoundBuffer_Session music;
	CL_SetupSound  setup_sound;
	CL_SetupMikMod setup_mikmod;
	CL_SetupVorbis setup_vorbis;
	CL_SoundOutput output;


};

#endif /* SOUND_H_ */
