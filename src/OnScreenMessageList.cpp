/*
 * OnScreenMessageList.cpp
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#include "OnScreenMessageList.h"
#include "Application.h"

OnScreenMessageList::OnScreenMessageList() {
	CL_FontDescription font_desc;
	font_desc.set_typeface_name("tahoma");
	font_desc.set_height(30);
	fontSystem = CL_Font_System(Application::get()->gc, font_desc);
}

OnScreenMessageList::~OnScreenMessageList() {

}

void OnScreenMessageList::add(const OnScreenMessage& message)
{
	messages.push_back(message);
}

void OnScreenMessageList::tick(float secs)
{
	for(std::list<OnScreenMessage>::iterator it = messages.begin(); it != messages.end(); it++) {
		it->reduceTimeout(secs);
		if(it->timedOut()) {
			messages.erase(it);
		}
	}
}

void OnScreenMessageList::draw(void)
{
	for(std::list<OnScreenMessage>::iterator it = messages.begin(); it != messages.end(); it++) {
		fontSystem.draw_text(Application::get()->gc, 146, 50, it->getMessage());
	}
}
