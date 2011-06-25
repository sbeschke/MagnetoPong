#include "Application.h"
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <iostream>
#include "Player.h"
#include "MouseInputDevice.h"
#include "KinectInputDevice.h"


Application* Application::myself;
int Application::detail;
int Application::x_res;
int Application::y_res;

void PlayerCallback::playerRecognized(int nr)
{

}

void PlayerCallback::playerCalibrated(int nr)
{
	Application* app = Application::get();
	unsigned int playerSlot = Application::PLAYER_LEFT;
	if(app->players[Application::PLAYER_LEFT] != 0) {
		playerSlot = Application::PLAYER_RIGHT;
	}
	if(app->players[Application::PLAYER_RIGHT]) {
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

	app->players[playerSlot] = player;
}

void PlayerCallback::playerLost(int nr)
{
	Application* app = Application::get();
	for(int playerSlot = 0; playerSlot < app->players.size(); playerSlot++) {
		Player* player = app->players[playerSlot];
		if(player != 0 && player->getNumber() == nr) {
			std::cout << "Lost player on side " << playerSlot << std::endl;
			//delete player;
			app->players[playerSlot = 0];
		}
	}
}

void Application::run(void)
{
	quit = false;
	Application::myself = this;

	players.resize(2);
	players[PLAYER_LEFT] = 0;
	players[PLAYER_RIGHT] = 0;

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
	font_desc.set_typeface_name("tahoma");
	font_desc.set_height(30);
	CL_Font_System font(gc, font_desc);



	Ball ball(this,Vec2d(Application::x_res, Application::y_res));
	ball.initializePosition();
	ball.setCharge(1);
	addEntity(&ball);

	Ball ball2(this,Vec2d(Application::x_res, Application::y_res));
	ball2.setPosition(Vec2d((x_res/2)-50, y_res/2));
	ball2.setCharge(-1);
	addEntity(&ball2);

	while (!quit)
	{
		kinect.update();

		int timediff = CL_System::get_time() - start ;
		start = CL_System::get_time();


		if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
			quit = true;


		for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++) {
			(*it)->updateforces(entities,timediff);
		}

		gc.clear(CL_Colorf::white);
		for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++) {
			(*it)->updateposition(timediff);
			(*it)->draw();
		}

		for(std::vector<Player*>::iterator it = players.begin();
				it != players.end(); it++) {
			Player* pl = *it;
			if(pl != 0) {
				pl->processInput();
				kinect.drawPlayer(pl->getNumber());
			}
		}



		/*for(int i=0; i < 5; i++)
		{
		   kinect.drawPlayer(i);
		}*/
		//draw_sunset(gc);

		//boat_sprite.draw(gc, 70, 252);

		//font.draw_text(gc, 146, 50, "A quiet evening in the pacific...");



		//player1.getBat()->draw();
		//std::ostringstream oss;
		//font.draw_text(gc, 146, 50, oss.str());
		//boat_sprite.update();
		window.flip();
		CL_KeepAlive::process();
		//CL_System::sleep(10);
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

void Application::addPlayer(int num)
{

}
