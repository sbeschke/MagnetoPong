/*
 * Sound.cpp
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */

#include "Sound.h"
#include "ClanLib/core.h"
#include <iostream>


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
		if(CL_FileHelp::file_exists(it->second.c_str()))
		{
		CL_SoundBuffer* tempbuffer = new CL_SoundBuffer(it->second);
		this->effects[it->first]= tempbuffer;
		}
		else
		{
			std::cout << "File not found:"<< it->first<< std::endl;
		}
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
	else
	{
		std::cout << "Effect not found:"<< name << std::endl;
	}

}
