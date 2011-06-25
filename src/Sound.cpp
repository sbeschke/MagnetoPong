/*
 * Sound.cpp
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */

#include "Sound.h"


Sound::~Sound()
{

}

Sound::Sound()
{
	output = CL_SoundOutput(44100);
}
void Sound::loadeffects(std::map<std::string, std::string> &effects)
{
	std::map<std::string,std::string>::iterator it = effects.begin();
	for(;it != effects.end();it++)
	{
		CL_SoundBuffer* tempbuffer = new CL_SoundBuffer(it->second);
		this->effects[it->first]= tempbuffer;
	}

}
void Sound::effect(std::string name)
{
	if(effects.find(name) != effects.end())
	{
	   if(name == "collision") effects[name]->set_volume(0.3);
	   else                    effects[name]->set_volume(1);

	   effects[name]->play();
	}

}
