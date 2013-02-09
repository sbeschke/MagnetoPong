#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <vector>
#include <set>
#include <map>

#include "OpenNi.h"
#include "Player.h"
#include "Entity.h"
#include "OnScreenMessage.h"
#include "Sound.h"

class Ball;
class Menu;
class Pong;
class Demo;
class Squash;

class PlayerCallback : public OpenNiPlayerCallback
{
public:
	void playerRecognized(int nr);
	void calibrationStart(int nr);
	void calibrationFailed(int nr);
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
	CL_InputDevice keyboard;
	CL_InputDevice mouse;
	static Application* myself;
	Menu* dasMenu;
	Pong* pong;
	Demo* demo;
	Squash* squash;
	CL_DisplayWindow window;

public:
	int gamestatus;

	const static int GS_DEMO   = 0;
	const static int GS_MENU   = 1;
   const static int GS_PONG   = 2;
   const static int GS_SQUASH = 3;

	Sound *soundPlayer;

	PlayerCallback playerCallback;

	static int detail;
	static int x_res;
	static int y_res;
	static bool fullscreen;
	static int  fullscreenmonitor;

	static bool enableEasterEggs;
	static int scoreToWin;

	const static unsigned int PLAYER_LEFT = 0;
	const static unsigned int PLAYER_RIGHT = 1;

	static Application* get(void) {return myself;}


	OpenNi kinect;
	std::vector<Player*> players;
	int playersActive;

	OnScreenMessage osmCenter;
	OnScreenMessage osmShout;
	OnScreenMessage osmHuge;
	OnScreenMessage osmLeft;
	OnScreenMessage osmRight;

	CL_GraphicContext& getGC(void)
	{
		return graphicContext;
	}

	Application(void);

	void setRes(int x, int y);
	void domsetup();

	void run(void);
	void switchTo(int status);
	void runMenu(float timediff);

	void on_window_close()
	{
		quit = true;
	}

	void addPlayer(Player* player, int playerSlot);
	void remPlayer(int playerSlot);

	void playersChanged(void);
};

#endif // APPLICATION_H_
