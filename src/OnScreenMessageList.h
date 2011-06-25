/*
 * OnScreenMessageList.h
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#ifndef ONSCREENMESSAGELIST_H_
#define ONSCREENMESSAGELIST_H_

#include "OnScreenMessage.h"
#include <list>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>


class OnScreenMessageList {
public:
	OnScreenMessageList(void);
	OnScreenMessageList(CL_Pointf textPos, CL_FontDescription font, CL_Colorf color);
	virtual ~OnScreenMessageList();

	void add(const OnScreenMessage& message);
	void tick(float secs);
	void draw();

private:
	std::list<OnScreenMessage> messages;
	CL_Pointf textPos;

	CL_Colorf color;
	CL_Font_System fontSystem;

};

#endif /* ONSCREENMESSAGELIST_H_ */
