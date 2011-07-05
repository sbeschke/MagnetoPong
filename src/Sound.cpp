/*
 * Sound.cpp
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */

#include "Sound.h"
#include "ClanLib/core.h"
#include <iostream>

Sound::Sound()
{
	output = CL_SoundOutput(44100);
	soundsOn = true;
}
//---------------------------------------------------------------------------
Sound::~Sound()
{
	for(EffectMap::iterator it = this->effects.begin(); it != this->effects.end(); it++)
	{
		delete it->second;
	}
	this->effects.clear();
}

//---------------------------------------------------------------------------

void Sound::domLoad(CL_DomElement config)
{
	CL_DomElement domeffects = config.named_item("effects").to_element();
	CL_DomNode dom_iterator= domeffects.get_first_child();
	std::map<std::string,std::string> effects;
	while(!dom_iterator.is_null())
	{
		//dereferencing the dom node
		CL_DomElement current = dom_iterator.to_element();
		CL_String name = current.get_attribute("name");
		CL_String path = current.get_text();
		effects[name]=path;
		dom_iterator = dom_iterator.get_next_sibling();
	}
	this->loadeffects(effects);

}
//---------------------------------------------------------------------------

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
		this->effects[it->first] = tempbuffer;
		}
		else
		{
			std::cout << "File not found:"<< it->first<< std::endl;
		}
	}

}
//---------------------------------------------------------------------------

void Sound::effect(std::string name)
{
	if(effects.find(name) != effects.end())
	{
	   if(name == "collision") effects[name]->set_volume(0.3);
	   else                    effects[name]->set_volume(1);

	   if(soundsOn) effects[name]->play();
	}
	else
	{
		std::cout << "Effect not found:"<< name << std::endl;
	}

}
//---------------------------------------------------------------------------

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
//---------------------------------------------------------------------------

void Sound::play()
{
	music.set_looping(true);
	if(soundsOn) music.play();
}
//---------------------------------------------------------------------------

void Sound::setActive(bool active)
{
   soundsOn = active;
   if(!soundsOn)
   {
      music.stop();
   }
}
