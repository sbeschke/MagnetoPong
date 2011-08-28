/*
 * Demo.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#include "Demo.h"
#include "Application.h"
#include "Ball.h"

Demo::Demo(Application* app)
:MagnetoEngine(app)
{
   solidSides = Entity::BOTTOMSIDE | Entity::TOPSIDE | Entity::LEFTSIDE | Entity::RIGHTSIDE;
   timeToSpawnBallVal = 500;
}

Demo::~Demo()
{

}
//---------------------------------------------------------------------------

void Demo::run(float timediff)
{
   timeToSpawnBall -= timediff;
   if(timeToSpawnBall <= 0.0f)
   {
      makeBall();
      timeToSpawnBall = timeToSpawnBallVal;
   }

   calcForces(timediff);
   drawBalls();
}
//---------------------------------------------------------------------------

void Demo::ballOut(int side)
{

}
//---------------------------------------------------------------------------
