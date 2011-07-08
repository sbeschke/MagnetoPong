/*
 * OnScreenMessage.h
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#ifndef ONSCREENMESSAGE_H_
#define ONSCREENMESSAGE_H_

#include <string>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

class OnScreenMessage {
public:
	OnScreenMessage() {}
	OnScreenMessage(CL_Pointf textPos, CL_FontDescription font, CL_Colorf color);
	~OnScreenMessage();

	void setMessage(const std::string message);
	void setMessage(const std::string message, float timeout);

	void setPos(CL_Pointf textPos);

	void tick(float secs);
	void draw(void);
	void hide(void);

private:
	bool show;
	std::string message;
	bool hasTimeout;
	float timeout;

	CL_Pointf textPos;

	CL_Colorf color;
	CL_Font_System fontSystem;

};

#endif /* ONSCREENMESSAGE_H_ */
