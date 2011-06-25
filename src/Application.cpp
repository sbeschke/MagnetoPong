#include "Application.h"
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <iostream>
#include "Player.h"
#include "MouseInputDevice.h"
#include "KinectInputDevice.h"
#include "OnScreenMessage.h"
#include "TGString.h"
#include "Ball.h"
#include <exception>
#include <stdlib.h>
#include "BoostBar.h"


Application* Application::myself;
int Application::detail;
int Application::x_res;
int Application::y_res;

void PlayerCallback::playerRecognized(int nr)
{
	Application* app = Application::get();
	if(app->players[Application::PLAYER_RIGHT] == 0) {
		Application::get()->osmRight.setMessage("Welcome. Please form a PSI to calibrate.", 5.0f);
	}
	else if(app->players[Application::PLAYER_LEFT] == 0) {
		Application::get()->osmLeft.setMessage("Welcome. Please form a PSI to calibrate.", 5.0f);
	}

}

void PlayerCallback::calibrationStart(int nr)
{
	Application* app = Application::get();
	if(app->players[Application::PLAYER_RIGHT] == 0) {
		Application::get()->osmRight.setMessage("Calibrating...");
	}
	else if(app->players[Application::PLAYER_LEFT] == 0) {
		Application::get()->osmLeft.setMessage("Calibrating...");
	}
	else {
		Application::get()->osmCenter.setMessage("Too many players, please go away!", 5.0f);
	}
}

void PlayerCallback::calibrationFailed(int nr)
{
	Application* app = Application::get();
	if(app->players[Application::PLAYER_RIGHT] == 0) {
		Application::get()->osmRight.setMessage("Calibration failed", 2.0f);
	}
	else if(app->players[Application::PLAYER_LEFT] == 0) {
		Application::get()->osmLeft.setMessage("Calibration failed", 2.0f);
	}
}

void PlayerCallback::playerCalibrated(int nr)
{
	Application::get()->osmRight.hide();
	Application::get()->osmLeft.hide();
	Application* app = Application::get();
	unsigned int playerSlot = Application::PLAYER_RIGHT;
	if(app->players[Application::PLAYER_RIGHT] != 0)
	{
		playerSlot = Application::PLAYER_LEFT;
	}
	if(app->players[Application::PLAYER_LEFT] != 0)
	{
		return;
	}

	KinectInputDevice* device = new KinectInputDevice(nr, playerSlot == Application::PLAYER_LEFT);
	Player* player = new Player(app, device);
	player->setNumber(nr);
	player->getBat()->setColor(playerColors[playerSlot]);

	if(playerSlot == Application::PLAYER_LEFT) {
		std::cout << "You play LEFT!" << std::endl;
	}
	if(playerSlot == Application::PLAYER_RIGHT) {
		std::cout << "You play RIGHT!" << std::endl;
	}

	app->addPlayer(player, playerSlot);
}

void PlayerCallback::playerLost(int nr)
{
	Application* app = Application::get();
	for(int playerSlot = 0; playerSlot < app->players.size(); playerSlot++)
	{
		Player* player = app->players[playerSlot];
		if(player != 0 && player->getNumber() == nr)
		{
			std::cout << "Lost player on side " << playerSlot << std::endl;
			app->remPlayer(playerSlot);
		}
	}
}

Application::Application(void)
{

	CL_FontDescription font_desc;
	font_desc.set_typeface_name("Verdana");
	font_desc.set_height(60);
	CL_FontDescription huge_font_desc;
	CL_FontDescription font_desc2 = font_desc;
	font_desc2.set_height(50);
	huge_font_desc.set_typeface_name("Verdana");
	huge_font_desc.set_height(200);
	huge_font_desc.set_weight(5);

	osmCenter = OnScreenMessage(CL_Pointf(x_res / 2, (float)y_res * 0.75f), font_desc2, CL_Colorf::darkslateblue);
	osmShout  = OnScreenMessage(CL_Pointf(x_res / 2, (float)y_res * 0.25f), font_desc2, CL_Colorf::deeppink);
	osmHuge   = OnScreenMessage(CL_Pointf(x_res / 2, (float)y_res * 0.5f),
			huge_font_desc, CL_Colorf::deeppink);
	osmLeft = OnScreenMessage(CL_Pointf(x_res / 4, y_res / 2), font_desc,
			playerColors[PLAYER_LEFT]);
	osmRight = OnScreenMessage(CL_Pointf(x_res * 3 / 4, y_res / 2),
			font_desc, playerColors[PLAYER_RIGHT]);

	spawnBall = false;
	timeToSpawnBall = 0.0f;
	inMatch = false;
	timeToMatch = 0.0f;
	player = new Sound();
	std::map<std::string,std::string> effects;

	//effects["on"]="effects/ltsaberon01.wav";
	effects["collision"]="effects/sch.ogg";
	effects["point"]="effects/ping.ogg";
	effects["win"]="effects/aus.ogg";
	effects["fight"]="effects/fight.ogg";
	effects["boost"]="effects/ohjea.ogg";
	player->loadeffects(effects);

}

void Application::run(void)
{
	quit = false;
	Application::myself = this;

	players.resize(2);
	players[PLAYER_LEFT] = 0;
	players[PLAYER_RIGHT] = 0;
	playersActive = 0;

	kinect.setPlayerCallback(&playerCallback);

	unsigned int start =  CL_System::get_time();
	CL_DisplayWindowDescription window_desc;
	window_desc.set_size(CL_Size(Application::x_res, Application::y_res), true);
	window_desc.set_title("MagnetoPong!!!11einself");
	CL_DisplayWindow window(window_desc);

	CL_Slot slot_quit = window.sig_window_close().connect(this, &Application::on_window_close);

	graphicContext = window.get_gc();
	gc = graphicContext;
	CL_InputDevice keyboard = window.get_ic().get_keyboard();
	CL_InputDevice mouse = window.get_ic().get_mouse(0);

	CL_ResourceManager resources("resources.xml");

	CL_Sprite boat_sprite(gc, "Boat", &resources);

	CL_FontDescription font_desc;
	font_desc.set_typeface_name("Verdana");
	font_desc.set_height(80);
	CL_Font_System font(gc, font_desc);

	CL_FontDescription scoreFont_desc;
	scoreFont_desc.set_typeface_name("Verdana");
	scoreFont_desc.set_height(80);
	CL_Font_System scoreFont(gc, scoreFont_desc);

	BoostBar boostbarPL(PLAYER_LEFT);
	boostbarPL.setMaxValue(BOOSTRELOADTIME);
	BoostBar boostbarPR(PLAYER_RIGHT);
	boostbarPR.setMaxValue(BOOSTRELOADTIME);


	playersChanged();
	clearBalls();

	while (!quit)
	{

		kinect.update();

		int timediff = CL_System::get_time() - start ;
		start = CL_System::get_time();


		if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)	quit = true;

		if(keyboard.get_keycode(CL_KEY_SPACE) == true && playersActive < 2)
		{
			int playerSlot = PLAYER_RIGHT;
			if(players[Application::PLAYER_RIGHT] != 0)
			{
				playerSlot = Application::PLAYER_LEFT;
			}
			if(players[Application::PLAYER_LEFT] != 0)
			{
				break;
			}

			MouseInputDevice* device = new MouseInputDevice(&mouse);
			Player* player = new Player(this, device);
			addPlayer(player, playerSlot);
		}

		bool collision = false;
		for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++) {
			collision = collision || (*it)->updateforces(entities,timediff);
		}
		if(collision)
		{
		   if(playersActive) player->effect("collision");
		}

		if(spawnBall)
		{
			timeToSpawnBall -= timediff;
			if(timeToSpawnBall <= 0.0f)
			{
				//player->effect("on");
				doSpawnBall();
			}
		}

		osmCenter.tick((float)timediff / 1000.0f);
		osmShout.tick((float)timediff / 1000.0f);
		osmHuge.tick((float)timediff / 1000.0f);
		osmLeft.tick((float)timediff / 1000.0f);
		osmRight.tick((float)timediff / 1000.0f);

		gc.clear(CL_Colorf::white);

		for(std::vector<Player*>::iterator it = players.begin();
				it != players.end(); it++)
		{
			Player* pl = *it;
			if(pl != 0)
			{
				pl->processInput();
				kinect.drawPlayer(pl->getNumber());
			}
		}

		for(EntitySet::iterator it = entities.begin(); it != entities.end();)
		{
			EntitySet::iterator next = it;
			next++;
			(*it)->updateposition(timediff);
			(*it)->draw();

			if(Ball* ball = dynamic_cast<Ball*>(*it))
			{
				if(checkBall(ball))
				{
					remEntity(ball);
					delete ball;
				}
				if(playersActive == 2)
            {
				   if(players[PLAYER_LEFT]->getKick())
               {
				      ball->setCharge(ball->getCharge()*-1);
               }
				   if(players[PLAYER_RIGHT]->getKick())
               {
                  ball->setCharge(ball->getCharge()*-1);
               }
            }
			}
			it = next;
		}

		osmCenter.draw();
		osmShout.draw();
		osmLeft.draw();
		osmRight.draw();
		osmHuge.draw();

		if(playersActive == 2)
		{
			// draw scores
			std::ostringstream scoreLeftTxtStrm;
			scoreLeftTxtStrm << players[PLAYER_LEFT]->getScore() << " : "
					<< players[PLAYER_RIGHT]->getScore();
			std::string scoreLeftTxt = scoreLeftTxtStrm.str();
			CL_Size scoreSize = scoreFont.get_text_size(Application::get()->gc, scoreLeftTxt);
			CL_Pointf scoreLeftPos((x_res - scoreSize.width) / 2, scoreSize.height);
			scoreFont.draw_text(gc, scoreLeftPos, scoreLeftTxt, CL_Colorf::black);
			if(!inMatch)
			{
				clearBalls();
				timeToMatch -= timediff;
				if(timeToMatch <= 0.0f)
				{
					startMatch();
				}
			}
			boostbarPL.setValue(players[PLAYER_LEFT]->getBat()->getBoostctr());
			boostbarPR.setValue(players[PLAYER_RIGHT]->getBat()->getBoostctr());
			boostbarPL.draw();
			boostbarPR.draw();

		}

//		TGString s = TGString("b1(") + ball.getPosition().x + "|" + ball.getPosition().y + ") b2(" + ball2.getPosition().x + "|" + ball2.getPosition().y + ")";
	//	font.draw_text(Application::myself->gc, 10, 20, s.c_str(), CL_Colorf::black);

		window.flip();
		CL_KeepAlive::process();
	}
}

void Application::addEntity(Entity* entity)
{
	entities.insert(entity);
}

void Application::remEntity(Entity* entity)
{
	entities.erase(entity);
}

void Application::addPlayer(Player* player, int playerSlot)
{
	if(players[playerSlot] != 0)
	{
		remPlayer(playerSlot);
	}
	players[playerSlot] = player;
	playersActive++;

	playersChanged();
}

void Application::remPlayer(int playerSlot)
{
	//delete player;
	Player* player = players[playerSlot];
	player->quit();
	players[playerSlot] = 0;
	playersActive--;

	if(playerSlot == PLAYER_LEFT) {
		osmLeft.setMessage("Player OUT", 5.0f);
	}
	if(playerSlot == PLAYER_RIGHT) {
		osmRight.setMessage("Player OUT", 5.0f);
	}

	endMatch();
	playersChanged();
}

// return true if ball is out
bool Application::checkBall(Ball* ball)
{
	bool ballOut = false;
	Vec2d pos = ball->getPosition();

	if(pos.x < 0)
	{
		this->ballOut(ball, PLAYER_RIGHT);
		ballOut = true;
	}
	else if(pos.x >= x_res)
	{
		this->ballOut(ball, PLAYER_LEFT);
		ballOut = true;
	}
	else if(!(pos.y >= 0 && pos.y < y_res))
	{
		ballGone(ball);
		ballOut = true;
	}

	return ballOut;
}

void Application::ballOut(Ball* ball, int playerSlot) {
	if(playersActive == 2) {
		player->effect("point");
		players[playerSlot]->incrementScore();

		if(players[playerSlot]->getScore() >= SCORE_TO_WIN) {
			player->effect("win");
			endMatch();
			if(playerSlot == PLAYER_RIGHT) {
				osmHuge.setMessage("Right WINS", 3.0f);
			}
			else if(playerSlot == PLAYER_LEFT) {
				osmHuge.setMessage("Left WINS", 3.0f);
			}
		}
		else {
			if(playerSlot == PLAYER_RIGHT) {
				osmShout.setMessage("Right Scores", 2.0f);
			}
			else if(playerSlot == PLAYER_LEFT) {
				osmShout.setMessage("Left Scores", 2.0f);
			}
			spawnBall = true;
			timeToSpawnBall = 3000.0f;
		}
	}
	else
	{
		if(entities.size() <= ANZ_BALS_DEMO)
		{
			makeBall();
		}
	}
}
void Application::ballGone(Ball* ball) {
	makeBall();
}

void Application::clearBalls(void) {
	for(EntitySet::iterator it = entities.begin(); it != entities.end();) {
		EntitySet::iterator next = it;
		next++;
		if(Ball* ball = dynamic_cast<Ball*>(*it)) {
			remEntity(ball);
			delete ball;
		}
		it = next;
	}

}

void Application::makeBall(void)
{
	Ball* b1 = new Ball(this,Vec2d(Application::x_res, Application::y_res));
	b1->initializePosition();
	int ch = rand() % 2;
	b1->setCharge(ch ? 1.0f : -1.0f);
	addEntity(b1);

}

void Application::startMatch(void)
{
	inMatch = true;
	osmShout.setMessage("FIGHT", 3.0f);
	player->effect("fight");
	std::ostringstream centerText;
	centerText << "Score " << SCORE_TO_WIN << " points to win";
	osmCenter.setMessage(centerText.str(), 3.0f);
	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); it++) {
		if(*it != 0) {
			(*it)->setScore(0);
		}
	}
	makeBall();
}

void Application::endMatch(void)
{
	prepareMatch();
}

void Application::doSpawnBall(void)
{
	switch(playersActive) {
		case 0:
		case 1:{
			makeBall();
			spawnBall = true;
			timeToSpawnBall = 3000.0f;
			break;
		}
		case 2: {
			makeBall();
			spawnBall = false;
			break;
		}
		default: throw std::exception(); break;
		}
}

void Application::prepareMatch(void)
{
	spawnBall = false;
	inMatch = false;
	timeToMatch = 5000.0f;
	osmCenter.setMessage("Get ready...", 3.0f);
}

void Application::playersChanged(void)
{
	switch(playersActive) {
		case 0:
			osmCenter.setMessage("Stand in front of camera to play MagnetoPong!");
			spawnBall = true;
			timeToSpawnBall = 3000.0f;
			break;
		case 1:{
			osmCenter.setMessage("Waiting for player 2 – Stand in front of camera to play MagnetoPong!");
//			spawnBall = true;
//			timeToSpawnBall = 3000.0f;
			break;
		}
		case 2: {
			prepareMatch();
			break;
		}
		default: throw std::exception(); break;
	}
}
