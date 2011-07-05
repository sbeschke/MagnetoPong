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
#include "RGBWindow.h"
#include "DepthWindow.h"
#include "MenuButton.h"
#include "Menu.h"
#include "Pong.h"
#include "Demo.h"
#include "Squash.h"


Application* Application::myself;
int Application::detail;
int Application::x_res;
int Application::y_res;
bool Application::fullscreen;
int Application::fullscreenmonitor;

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
//---------------------------------------------------------------------------

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
//---------------------------------------------------------------------------

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
//---------------------------------------------------------------------------

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
	Player* player = new Player(app, device, playerSlot);
	player->setNumber(nr);
	player->getBat()->setColor(playerColors[playerSlot]);

	if(playerSlot == Application::PLAYER_LEFT) {
		std::cout << "You play LEFT!" << std::endl;
	}
	if(playerSlot == Application::PLAYER_RIGHT) {
		std::cout << "You play RIGHT!" << std::endl;
	}

	app->addPlayer(player, playerSlot);
	Application::get()->soundPlayer->effect("playeron");
}
//---------------------------------------------------------------------------

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
		Application::get()->soundPlayer->effect("playeroff");
	}
}
//---------------------------------------------------------------------------
void Application::domsetup()
{
	CL_String filename = "";
	if(CL_FileHelp::file_exists("configs/magnetopong.xml"))
	{
		filename = "configs/magnetopong.xml";
	}
	else if(CL_FileHelp::file_exists("~/.magnetopong/config.xml"))
	{
		filename = "~/.magnetopong.xml";
	}
	else if(CL_FileHelp::file_exists("/etc/magnetopong.xml"))
	{
		filename = "/etc/magnetopong.xml";
	}
	else
	{
		CL_Console::write_line("Could not find magnetopong.xml");

	}
	if(filename.length() > 0)try
	{
		CL_File file(filename);
		CL_String ns_magnetopong = "http://magnetopong.org/config";
		CL_DomDocument document(file);
		CL_DomNode root = document.named_item_ns(ns_magnetopong,"config");
		CL_DomElement display = root.named_item("display").to_element();
		//CL_DomElement display = Application::domconfig.named_item("display").to_element();
		Application::x_res = display.get_child_int("width",Application::x_res);
		Application::y_res = display.get_child_int("height",Application::y_res);
		Application::fullscreen = display.get_child_bool("fullscreen",Application::fullscreen);
		Application::fullscreenmonitor = display.get_child_bool("fullscreenmonitor",Application::fullscreenmonitor);

		CL_DomElement sound = root.named_item("sound").to_element();
		this->soundPlayer->domLoad(sound);

		file.close();
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("DOM Error: " + exception.get_message_and_stack_trace());
		console.display_close_message();
	}
}
//---------------------------------------------------------------------------

Application::Application(void)
{
   Application::myself = this;

   gamestatus = GS_DEMO;

   srand(time(NULL));

	soundPlayer = new Sound();
	pong   = new Pong(this);
	demo   = new Demo(this);
	squash = new Squash(this);

	domsetup();

	CL_FontDescription font_desc;
	font_desc.set_typeface_name("Verdana");
	font_desc.set_height(60);

	CL_FontDescription font_desc2 = font_desc;
   font_desc2.set_height(50);

	CL_FontDescription huge_font_desc;
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
}
//---------------------------------------------------------------------------

void Application::run(void)
{
	quit = false;

	players.resize(2);
	players[PLAYER_LEFT]  = 0;
	players[PLAYER_RIGHT] = 0;
	playersActive = 0;

	kinect.setPlayerCallback(&playerCallback);

	RGBWindow   vwindow(&kinect);
	DepthWindow dwindow(&kinect, 500, 3000, 0.1, true);

	unsigned int start = CL_System::get_time();

	CL_DisplayWindowDescription window_desc;
	window_desc.set_size(CL_Size(Application::x_res,Application::y_res), true);
	window_desc.set_fullscreen(Application::fullscreen,0);
	window_desc.set_title("MagnetoPong!!!11einself");

	CL_DisplayWindow window(window_desc);

	CL_Slot slot_quit = window.sig_window_close().connect(this, &Application::on_window_close);

	graphicContext = window.get_gc();
	keyboard = window.get_ic().get_keyboard();
	mouse    = window.get_ic().get_mouse(0);

	dasMenu = new Menu();

	playersChanged();

	//---------------------------------------------------------------------------
	while (!quit)//schleife-schleife-schleife-schleife-schleife-schleife-schleife ;)
	{
		int timediff = CL_System::get_time() - start ;
		start = CL_System::get_time();

		kinect.update(timediff);

      //--Beenden-----------------------
      if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
      {
         while(keyboard.get_keycode(CL_KEY_ESCAPE));

         if(gamestatus != GS_DEMO) switchTo(GS_MENU);
         else quit = true;
      }

		//--Leertaste aktiviert Maussteuerung
		if(keyboard.get_keycode(CL_KEY_SPACE) == true && playersActive < 2)
		{
		   while(keyboard.get_keycode(CL_KEY_SPACE));
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
			Player* player = new Player(this, device, playerSlot);
			addPlayer(player, playerSlot);
		}

		graphicContext.clear(CL_Colorf::white); //Fenster mit Weiß löschen

		//--Spielmodus
		switch(gamestatus)
		{
		case GS_DEMO:   demo->run(timediff);   break;
		case GS_MENU:   runMenu(timediff);     break;
		case GS_PONG:   pong->run(timediff);   break;
		case GS_SQUASH: squash->run(timediff); break;
		}

		//--Textausgabe
      osmCenter.tick((float)timediff / 1000.0f);
      osmShout.tick((float)timediff / 1000.0f);
      osmHuge.tick((float)timediff / 1000.0f);
      osmLeft.tick((float)timediff / 1000.0f);
      osmRight.tick((float)timediff / 1000.0f);

      osmCenter.draw();
      osmShout.draw();
      osmLeft.draw();
      osmRight.draw();
      osmHuge.draw();

		window.flip();

		vwindow.refresh(timediff);
		dwindow.refresh(timediff);

		CL_KeepAlive::process();
	}
}
//---------------------------------------------------------------------------

void Application::switchTo(int status)
{
   osmCenter.hide();
   osmShout.hide();
   osmLeft.hide();
   osmRight.hide();
   osmHuge.hide();

   switch(status)
   {
   case GS_DEMO:
      {
      }
      break;
   case GS_MENU:
      {
      }
      break;
   case GS_PONG:
      {
         pong->restartMatch();
      }
      break;
   case GS_SQUASH:
      {
         squash->restartMatch();
      }
      break;
   }
   gamestatus = status;
}
//---------------------------------------------------------------------------

void Application::runMenu(float timediff)
{
   dasMenu->draw();

   //--Spieler input verarbeiten und Spielerskelett Zeichnen
   for(std::vector<Player*>::iterator it = players.begin();
         it != players.end(); it++)
   {
      Player* pl = *it;
      if(pl != 0)
      {
         pl->processInput(timediff);
         pl->draw(Player::SKELETON | Player::BAT);

         switch(dasMenu->checkPlayer(pl))
         {
         case Menu::NON: break;
         case Menu::PONG:   switchTo(GS_PONG); break;
         case Menu::SQUASH: dasMenu->setMenu(Menu::MENUDIF);  break;
         case Menu::OPTION: dasMenu->setMenu(Menu::MENUOPT);  break;
         case Menu::DIF1:   squash->setDifficulty(0.8); switchTo(GS_SQUASH);  break;
         case Menu::DIF2:   squash->setDifficulty(1);   switchTo(GS_SQUASH);  break;
         case Menu::DIF3:   squash->setDifficulty(1.6); switchTo(GS_SQUASH);  break;
         case Menu::DIF4:   squash->setDifficulty(2.1); switchTo(GS_SQUASH);  break;
         case Menu::SOUND:  soundPlayer->setActive(!soundPlayer->getActive()); break;
         case Menu::BACK:   dasMenu->setMenu(Menu::MENUROOT); break;
         case Menu::END:    quit = true; break;
         }
      }
   }
   //
}
//---------------------------------------------------------------------------

void Application::addPlayer(Player* player, int playerSlot)
{
	if(players[playerSlot] != 0)
	{
		remPlayer(playerSlot);
	}
	players[playerSlot] = player;
	pong->addEntity(player->getBat());
	squash->addEntity(player->getBat());
	cout << "player Add\n";
	playersActive++;

	playersChanged();
}
//---------------------------------------------------------------------------

void Application::remPlayer(int playerSlot)
{
	Player* player = players[playerSlot];
	player->quit();
	pong->remEntity(player->getBat());
	squash->remEntity(player->getBat());
	delete player;
	players[playerSlot] = 0;
	playersActive--;

	if(playerSlot == PLAYER_LEFT)
	{
		osmLeft.setMessage("Player OUT", 5.0f);
	}
	if(playerSlot == PLAYER_RIGHT)
	{
		osmRight.setMessage("Player OUT", 5.0f);
	}

	playersChanged();
}
//---------------------------------------------------------------------------

void Application::playersChanged(void)
{
   switch(gamestatus)
   {
   case GS_DEMO:
         if(playersActive)
         {
            switchTo(GS_MENU);
         }
         else
         {
            osmCenter.setMessage("Stand in front of camera to play MagnetoPong!");
         }
      break;
   case GS_MENU:
          if(!playersActive)
          {
             switchTo(GS_DEMO);
          }
      break;
   case GS_PONG:
      switch(playersActive)
      {
      case 0: switchTo(GS_DEMO); break;
      case 1:
         {
            osmCenter.setMessage("Waiting for player 2 – Stand in front of camera to play MagnetoPong!");
         }
         break;
      case 2:
         {
         }
         break;
      }
      break;
   case GS_SQUASH:
      {
         switch(playersActive)
         {
         case 0: switchTo(GS_DEMO); break;
         case 1:
            {

            }
            break;
         case 2:
            {
            }
            break;
         }
         break;
      }
      break;
   }
}
