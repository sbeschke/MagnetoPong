/*
 * Pong.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#include "Pong.h"
#include "Application.h"
#include "Ball.h"
#include "InputDevice.h"
#include <stdlib.h>


Pong::Pong(Application* app)
:MagnetoEngine(app)
{
   solidSides = Entity::BOTTOMSIDE | Entity::TOPSIDE;
   inMatch = false;
   timeToMatch = 2000;
}

Pong::~Pong()
{
}
//---------------------------------------------------------------------------

void Pong::run(float timediff)
{
   //--Spieler input verarbeiten und Spielerskelett Zeichnen
   for(std::vector<Player*>::iterator it = app->players.begin();
         it != app->players.end(); it++)
   {
      Player* pl = *it;
      if(pl != 0)
      {
         pl->processInput(timediff);
         pl->draw(Player::SKELETON | Player::BAR);
      }
   }

   //--Ball einfügen
   if(spawnBall)
   {
      timeToSpawnBall -= timediff;
      if(timeToSpawnBall <= 0.0f)
      {
         doSpawnBall();
      }
   }

   //--Spieler Verarbeiten
   if(app->playersActive == 2)
   {
      drawScores(app->players[app->PLAYER_LEFT]->getScore(), app->players[app->PLAYER_RIGHT]->getScore());

      if(!inMatch)
      {
         clearBalls();
         spawnBall = false;
         timeToMatch -= timediff;
         if(timeToMatch <= 0.0f)
         {
            startMatch();
         }
      }

      doEsterEgg(app->PLAYER_LEFT,  app->players[app->PLAYER_LEFT]->getEsterEgg());
      doEsterEgg(app->PLAYER_RIGHT, app->players[app->PLAYER_RIGHT]->getEsterEgg());
   }
   else
   {
      spawnBall = true;
   }

   if(calcForces(timediff)) //--bei Kollision sound ausgeben (nur wenn Spieler drin sind)
   {
      app->soundPlayer->effect("collision");
   }
}
//---------------------------------------------------------------------------

// return true if ball is out
bool Pong::checkBall(Ball* ball)
{
   bool ballOut = false;
   Vec2d pos = ball->getPosition();

   if(pos.x < 0)
   {
      this->ballOut(app->PLAYER_RIGHT);
      ballOut = true;
   }
   else if(pos.x >= app->x_res)
   {
      this->ballOut(app->PLAYER_LEFT);
      ballOut = true;
   }
   else if(!(pos.y >= 0 && pos.y < app->y_res))
   {
      makeBall();
      ballOut = true;
   }

   return ballOut;
}
//---------------------------------------------------------------------------

void Pong::ballOut(int player)
{
   if(app->playersActive == 2)
   {
      app->soundPlayer->effect("point");
      app->players[player]->incrementScore();

      if(app->players[player]->getScore() >= Application::SCORE_TO_WIN)
      {
         app->soundPlayer->effect("win");

         restartMatch();
         if(player == app->PLAYER_RIGHT)
         {
            app->osmHuge.setMessage("Right WINS", 3.0f);
         }
         else if(player == app->PLAYER_LEFT)
         {
            app->osmHuge.setMessage("Left WINS", 3.0f);
         }
      }
      else
      {
         if(player == app->PLAYER_RIGHT)
         {
            app->osmShout.setMessage("Right Scores", 2.0f);
         }
         else if(player == app->PLAYER_LEFT)
         {
            app->osmShout.setMessage("Left Scores", 2.0f);
         }
         spawnBall = true;
         timeToSpawnBall = 3000.0f;
      }
   }
   else
   {
      if(entities.size() <= app->ANZ_BALS_DEMO)
      {
         makeBall();
      }
   }
}
//---------------------------------------------------------------------------

void Pong::startMatch(void)
{
   inMatch = true;
   app->osmShout.setMessage("FIGHT", 3.0f);
   app->soundPlayer->effect("fight");
   std::ostringstream centerText;
   centerText << "Score " << app->SCORE_TO_WIN << " points to win";
   app->osmCenter.setMessage(centerText.str(), 3.0f);

   for(std::vector<Player*>::iterator it = app->players.begin(); it != app->players.end(); it++)
   {
      if(*it != 0)
      {
         (*it)->setScore(0);
      }
   }

   makeBall();
}
//---------------------------------------------------------------------------

void Pong::restartMatch()
{
   spawnBall = false;
   inMatch   = false;
   timeToMatch = 5000.0f;
   app->osmCenter.setMessage("Get ready...", 3.0f);
}
//---------------------------------------------------------------------------

void Pong::drawScores(int s1, int s2)
{
   CL_FontDescription scoreFont_desc;
   scoreFont_desc.set_typeface_name("Verdana");
   scoreFont_desc.set_height(80);
   CL_Font_System scoreFont(app->getGC(), scoreFont_desc);

   TGString txt = TGString(s1) + " : " + s2;
   CL_Size scoreSize = scoreFont.get_text_size(app->getGC(), txt);
   CL_Pointf scoreLeftPos((Application::x_res - scoreSize.width) / 2, scoreSize.height);
   scoreFont.draw_text(app->getGC(), scoreLeftPos, txt, CL_Colorf::black);
}
//---------------------------------------------------------------------------

void Pong::doEsterEgg(int playerNr, int egg)
{
   switch(egg)
   {
   case InputDevice::EGG_POL:
      {
         for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++)
         {
            if(Ball* ball = dynamic_cast<Ball*>(*it))
            {
               ball->setCharge(ball->getCharge()*-1);
            }
         }
      }
      break;
   case InputDevice::EGG_STOP:
      {
         for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++)
         {
            if(Ball* ball = dynamic_cast<Ball*>(*it))
            {
               ball->setSpeed(Vec2d(0,0));
            }
         }
      }
      break;
   case InputDevice::EGG_MEGA:
      {
         cout << "Mega Egg\n";
         if(playerNr == app->PLAYER_LEFT)
         {
            app->players[app->PLAYER_RIGHT]->setInvert(!(app->players[app->PLAYER_RIGHT]->getInvert()));
            Application::get()->osmLeft.setMessage("you found the megaEgg", 2);
         }
         else
         {
            app->players[app->PLAYER_LEFT]->setInvert(!(app->players[app->PLAYER_LEFT]->getInvert()));
            Application::get()->osmRight.setMessage("you found the megaEgg", 2);
         }
         int i = rand() % 6;
         TGString s = TGString("Egg") + i;
         app->soundPlayer->effect(s);
      }
      break;
   }
}
//---------------------------------------------------------------------------
