/*
 * Demo.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthas
 */

#include "Demo.h"
#include "Application.h"
#include "Ball.h"

Demo::Demo(Application* app)
:MagnetoEngine(app)
{
   solidSides = Entity::BOTTOMSIDE | Entity::TOPSIDE;
   spawnBall = true;
   timeToSpawnBallVal = 500;
}

Demo::~Demo()
{

}
//---------------------------------------------------------------------------

void Demo::run(float timediff)
{
   //--Ball einfügen
   if(spawnBall)
   {
      timeToSpawnBall -= timediff;
      if(timeToSpawnBall <= 0.0f)
      {
         doSpawnBall();
      }
   }
   calcForces(timediff);
}
//---------------------------------------------------------------------------

bool Demo::checkBall(Ball* ball)
{
   bool ballOut = false;
   Vec2d pos = ball->getPosition();

   if(pos.x < 0)
   {
      ballOut = true;
   }
   else if(pos.x >= app->x_res)
   {
      ballOut = true;
   }
   else if(!(pos.y >= 0 && pos.y < app->y_res))
   {
      ballOut = true;
   }

   return ballOut;
}
//---------------------------------------------------------------------------
