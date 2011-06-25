#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/core.h>
#include <vector>
#include <set>

#include "OpenNi.h"
#include "Player.h"
#include "Entity.h"

class PlayerCallback : public OpenNiPlayerCallback
{
public:
	void playerRecognized(int nr);
	void playerCalibrated(int nr);
	void playerLost(int nr);
};

const CL_Colorf playerColors[] = {
			CL_Colorf::orange,
			CL_Colorf::blue
	};


class Application
{
private:
	bool quit;
	CL_GraphicContext graphicContext;

public:

	PlayerCallback playerCallback;

	static Application* myself;
	static int detail;
	static int x_res;
	static int y_res;

	const static unsigned int PLAYER_LEFT = 0;
	const static unsigned int PLAYER_RIGHT = 1;

	static Application* get(void) {
		return myself;
	}


	EntitySet entities;
	std::vector<Player*> players;

	CL_GraphicContext gc;

	OpenNi kinect;

	CL_GraphicContext& getGC(void)
	{
		return graphicContext;
	}

	void run(void);


	void draw_sunset(CL_GraphicContext &gc)
	{
		CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		CL_Colorf yellow(255/255.0f, 234/255.0f, 117/255.0f);
		CL_Colorf blue(13/255.0f, 75/255.0f, 74/255.0f);
		CL_Colorf lightblue(16/255.0f, 91/255.0f, 90/255.0f);

		// Draw top of sunset
		CL_Gradient gradient1(CL_Colorf::black, red);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,0,640,160), gradient1);

		// Draw second part of sunset
		CL_Gradient gradient2(red, yellow);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,160,640,240), gradient2);

		// Draw the sun
		CL_Draw::circle(gc, CL_Pointf(320, 240), 15, CL_Colorf::white);

		// Draw the ground
		CL_Draw::fill(gc, CL_Rectf(0, 240, 640, 480), blue);

		// Draw some distance lines
		for(int y = 241, ydelta = 2; y < 480; y += ydelta, ydelta += ydelta)
		{
			CL_Draw::line(gc, 0, y, 640, y, lightblue);
		}
	}

	void on_window_close()
	{
		quit = true;
	}

	void addEntity(Entity* entity);
	void remEntity(Entity* entity);

	void addPlayer(int num);
};

#endif // APPLICATION_H_
