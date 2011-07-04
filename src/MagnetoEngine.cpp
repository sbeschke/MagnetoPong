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

bool MagnetoEngine::calcForces(float timediff)
{
   Entity* object1;
   Entity* object2;

   bool overlap = false;
   for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++)
   {
      object1 = *it;
      EntitySet::iterator next = it;
      next++;

      for(; next != entities.end(); next++)
      {
         object2 = *next;

         Vec2d distance = object1->getPosition() - object2->getPosition();
         float length = distance.length();
         float charge = object1->getCharge() * object2->getCharge();

         bool positiv1 = object1->getCharge() > 0;
         bool positiv2 = object2->getCharge() > 0;
         //TODO what is this for? seems to be evil!
         if(positiv1 != positiv2) charge *= 1.5; //es wurde gewünscht, dass die Anziehung stärker ist

         //if the ball does not touch the object
         if(2*RADIUS < length)
         {
            float forceval = (charge * BALLACC / (length * length));
            Vec2d force = (distance/length) * forceval;

            if(Ball* ball = dynamic_cast<Ball*>(object1))
            {
               ball->addForce(force);
            }
            if(Ball* ball = dynamic_cast<Ball*>(object2))
            {
               ball->addForce(-force);
            }
         }
         else
         {
            //no inteaction because of overlap
         }

         //sound
         if(object2->getRadius()*4*(object2->getBoost()) + object1->getRadius()*4*object1->getBoost() > length)
         {
            overlap = true;
         }
      }

      object1->updateposition(timediff, solidSides);
      object1->draw();

      if(Ball* ball = dynamic_cast<Ball*>(object1))
      {
         if(checkBall(ball))
         {
            remEntity(ball);
            delete ball;
         }
      }
   }
   return overlap;
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

