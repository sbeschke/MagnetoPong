/*
 * MagnetoEngine.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#include "MagnetoEngine.h"
#include "Application.h"
#include "Ball.h"
#include <stdlib.h>

MagnetoEngine::MagnetoEngine(Application* app)
{
   this->app = app;
   timeToSpawnBallVal = 3000;
}

MagnetoEngine::~MagnetoEngine()
{

}
//---------------------------------------------------------------------------

bool MagnetoEngine::calcCollision(float timediff)
{
   bool collision = false;
   //--Bälle berechnen, zeichnen, und position überprüfen
   for(EntitySet::iterator it = entities.begin(); it != entities.end();)
   {
      EntitySet::iterator next = it;
      next++;
      collision = collision || (*it)->updateforces(entities, timediff);
      (*it)->updateposition(timediff, solidSides);
      (*it)->draw();

      if(Ball* ball = dynamic_cast<Ball*>(*it))
      {
         if(checkBall(ball))
         {
            remEntity(ball);
            delete ball;
         }
      }
      it = next;
   }

   return collision;
}
//---------------------------------------------------------------------------

void MagnetoEngine::makeBall(void)
{
   Ball* b1 = new Ball(app, Vec2d(Application::x_res, Application::y_res));
   b1->initializePosition();
   int ch = rand() % 2;
   b1->setCharge(ch ? 1.0f : -1.0f);
   addEntity(b1);
}
//---------------------------------------------------------------------------

void MagnetoEngine::remBall(Ball* ball)
{
   remEntity(ball);
}
//---------------------------------------------------------------------------

void MagnetoEngine::clearBalls(void)
{
  // entities.clear();
   for(EntitySet::iterator it = entities.begin(); it != entities.end();)
   {
      EntitySet::iterator next = it;
      next++;
      if(Ball* ball = dynamic_cast<Ball*>(*it))
      {
         remEntity(ball);
         delete ball;
      }
      it = next;
   }
}
//---------------------------------------------------------------------------

void MagnetoEngine::doSpawnBall(void)
{
   switch(app->playersActive)
   {
   case 0:
   case 1:
      {
         makeBall();
         spawnBall = true;
         timeToSpawnBall = timeToSpawnBallVal;
      }
      break;
   case 2:
      {
         makeBall();
         spawnBall = false;
      }
      break;
   }
}
//---------------------------------------------------------------------------

void MagnetoEngine::addEntity(Entity* entity)
{
   entities.insert(entity);
}
//---------------------------------------------------------------------------

void MagnetoEngine::remEntity(Entity* entity)
{
   entities.erase(entity);
}
//---------------------------------------------------------------------------

