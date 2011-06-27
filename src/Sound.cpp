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
	for(EffectMap::iterator it = this->effects.begin(); it != this->effects.end(); it++)
	{
		delete it->second;
	}
	this->effects.clear();

}

Sound::Sound()
{
	output = CL_SoundOutput(44100);
}

void Sound::loadeffects(std::map<std::string, std::string> &effects)
{
	for(EffectMap::iterator it = this->effects.begin(); it != this->effects.end(); it++)
	{
		delete it->second;
	}
	this->effects.clear();

	for(std::map<std::string,std::string>::iterator it = effects.begin();it != effects.end();it++)
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

void Sound::setmusic(std::string filename)
{
	this->music.stop();

	if(CL_FileHelp::file_exists(filename))
	{
		CL_SoundBuffer tempbuffer(filename);
		this->music = tempbuffer.prepare();
	}
	else
	{
		std::cout << "setmusic:File not found:"<< filename<< std::endl;
	}
}

void Sound::play()
{
	music.set_looping(true);
	music.play();
}
