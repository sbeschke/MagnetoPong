/*
 * OnScreenMessageList.cpp
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#include "OnScreenMessageList.h"
#include "Application.h"

OnScreenMessageList::OnScreenMessageList(void)
{

}

OnScreenMessageList::OnScreenMessageList(CL_Pointf textPos, CL_FontDescription font, CL_Colorf color)
: textPos(textPos), color(color)
{
	fontSystem = CL_Font_System(Application::get()->gc, font);
}

OnScreenMessageList::~OnScreenMessageList() {

}

void OnScreenMessageList::add(const OnScreenMessage& message)
{
	messages.push_back(message);
}

void OnScreenMessageList::tick(float secs)
{
	for(std::list<OnScreenMessage>::iterator it = messages.begin(); it != messages.end();) {
		std::list<OnScreenMessage>::iterator next = it;
		next++;
		it->reduceTimeout(secs);
		if(it->timedOut()) {
			messages.erase(it);
		}
		it = next;
	}
}

void OnScreenMessageList::draw(void)
{
	for(std::list<OnScreenMessage>::iterator it = messages.begin(); it != messages.end(); it++) {
		CL_Size size = fontSystem.get_text_size(Application::get()->gc, it->getMessage());

		fontSystem.draw_text(Application::get()->gc,
				textPos.x - (size.width/2), textPos.y - (size.height/2),
				it->getMessage(), color);
	}
}
