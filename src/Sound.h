/*
 * Sound.h
 *
 *  Created on: Jun 25, 2011
 *      Author: waynix
 */
#include <string>
#include <map>
#include <ClanLib/sound.h>
#include <ClanLib/vorbis.h>
#include <ClanLib/mikmod.h>
#ifndef SOUND_H_
#define SOUND_H_

class Sound {
public:
	virtual ~Sound();
	Sound();
	void setmusik(std::string filename);
	void play();
	void loadeffects(std::map<std::string,std::string> effects);
private:
	std::map<std::string,CL_SoundBuffer_Session*> effects;
	CL_SoundBuffer_Session musik;


};

#endif /* SOUND_H_ */
