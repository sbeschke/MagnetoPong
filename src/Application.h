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
	static Application* myself;

public:

	Sound *soundPlayer;

	PlayerCallback playerCallback;

	static int detail;
	static int x_res;
	static int y_res;
	static bool fullscreen;
	static int  fullscreenmonitor;

	int gamestatus;

	const static int GS_MENUE = 0;
	const static int GS_PONG  = 1;
	const static int GS_SQUASH = 2;

	const static int ANZ_BALS_DEMO = 8;
	const static int SCORE_TO_WIN = 11;

	const static unsigned int PLAYER_LEFT = 0;
	const static unsigned int PLAYER_RIGHT = 1;

	static Application* get(void) {return myself;}


	EntitySet entities;
	std::vector<Player*> players;
	int playersActive;

	OpenNi kinect;

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
	void domsetup();

	void run(void);
	void runPong(float timediff);

	void on_window_close()
	{
		quit = true;
	}

	void addEntity(Entity* entity);
	void remEntity(Entity* entity);

	void addPlayer(Player* player, int playerSlot);
	void remPlayer(int playerSlot);
	bool checkBall(Ball* ball);

	void ballOut(Ball* ball, int playerSlot);
	void ballGone(Ball* ball);

	void clearBalls(void);
	void makeBall(void);

	bool inMatch;
	float timeToMatch;
	void startMatch(void);
	void endMatch(void);

	float timeToSpawnBall;
	bool spawnBall;
	void doSpawnBall(void);

	void playersChanged(void);
	void prepareMatch(void);

	void drawScores(int s1, int s2);
	void doEsterEgg(int playerNr, int egg);
};

#endif // APPLICATION_H_
