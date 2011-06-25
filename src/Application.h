#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <vector>
#include <set>

#include "OpenNi.h"
#include "Player.h"
#include "Entity.h"
#include "OnScreenMessageList.h"

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

	OnScreenMessageList osmCenter;

	CL_GraphicContext& getGC(void)
	{
		return graphicContext;
	}

	void run(void);

	void on_window_close()
	{
		quit = true;
	}

	void addEntity(Entity* entity);
	void remEntity(Entity* entity);

	void addPlayer(int num);
};

#endif // APPLICATION_H_
