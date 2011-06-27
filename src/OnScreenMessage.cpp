/*
 * OnScreenMessage.cpp
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#include "OnScreenMessage.h"
#include <string>
#include "Application.h"

OnScreenMessage::OnScreenMessage(CL_Pointf textPos, CL_FontDescription font, CL_Colorf color)
: textPos(textPos), color(color), show(false), timeout(0.0f), hasTimeout(false)
{
	fontSystem = CL_Font_System(Application::get()->getGC(), font);
}

OnScreenMessage::~OnScreenMessage()
{
}

void OnScreenMessage::setMessage(const std::string message)
{
	show = true;
	this->message = message;
	hasTimeout = false;
}

void OnScreenMessage::setMessage(const std::string message, float timeout)
{
	show = true;
	this->message = message;
	this->timeout = timeout;
	hasTimeout = true;
}

void OnScreenMessage::tick(float secs)
{
	if(!hasTimeout) return;
	timeout -= secs;
	if(timeout <= 0.0f) {
		show = false;
	}
}

void OnScreenMessage::hide(void)
{
	show = false;
}

void OnScreenMessage::draw(void)
{
	if(show)
	{
		CL_Size size = fontSystem.get_text_size(Application::get()->getGC(), message);

		fontSystem.draw_text(Application::get()->getGC(),
				textPos.x - (size.width/2), textPos.y + (size.height/2),
				message, color);
	}
}
