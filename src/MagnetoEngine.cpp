/*
 * MagnetoEngine.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#include "MagnetoEngine.h"
#include "Application.h"
#include "Ball.h"
#include "Brick.h"
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

int MagnetoEngine::checkBall(Ball* ball)
{
   Vec2d pos = ball->getPosition();

   if(pos.x < 0)
   {
      return Entity::LEFTSIDE;
   }
   else if(pos.x >= app->x_res)
   {
      return Entity::RIGHTSIDE;
   }
   else if(pos.y < 0)
   {
      return Entity::TOPSIDE;
   }
   else if(pos.y >= app->y_res)
   {
      return Entity::BOTTOMSIDE;
   }
   return 0;
}
//---------------------------------------------------------------------------

bool MagnetoEngine::calcForces(float timediff)
{
   Entity* object1;
   Entity* object2;
   bool isball1;
   bool isball2;
   bool overlap = false;
   float length;
   Vec2d force;

   for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++)
   {
      object1 = *it;
      EntitySet::iterator next = it;
      next++;

      for(; next != entities.end(); next++)
      {
         object2 = *next;
         bool isball2 = false;
         float charge = 0;
         if(Brick* brick = dynamic_cast<Brick*>(object1))
         {
            if(Ball* ball = dynamic_cast<Ball*>(object2))
            {
               force = calcForce(brick, ball);
               charge = 1;
            }
         }
         else if(Ball* ball = dynamic_cast<Ball*>(object1))
         {
            if(Brick* brick = dynamic_cast<Brick*>(object2))
            {
               force = calcForce(brick, ball);
               charge = 1;
            }
         }

         if(!charge)
         {
            Vec2d distance = object1->getPosition() - object2->getPosition();
            length = distance.length();
            charge = object1->getCharge() * object2->getCharge();

            bool positiv1 = object1->getCharge() > 0;
            bool positiv2 = object2->getCharge() > 0;
            //TODO what is this for? seems to be evil!
            if(positiv1 != positiv2) charge *= 1.5; //es wurde gewünscht, dass die Anziehung stärker ist

            float forceval = (charge * Ball::ballacc / (length * length));
            force = (distance/length) * forceval;
         }


         //if the ball does not touch the object
         if(object1->getRadius() + object2->getRadius() < length)
         {
            if(Ball* ball = dynamic_cast<Ball*>(object1))
            {
               ball->addForce(force);
               isball1 = true;
            }
            if(Ball* ball = dynamic_cast<Ball*>(object2))
            {
               ball->addForce(-force);
               isball2 = true;
            }
         }
         else
         {
            //no inteaction because of overlap
         }

         //sound
         if(!(!isball2 && !isball1))
         {
            if(object2->getRadius()*4*(object2->getBoost()) + object1->getRadius()*4*object1->getBoost() > length)
            {
               overlap = true;
            }
         }
      }

      object1->updateposition(timediff, solidSides);

      if(Ball* ball = dynamic_cast<Ball*>(object1))
      {
         if(int side = checkBall(ball))
         {
            remEntity(ball);
            delete ball;
            ballOut(side);

            return overlap;
         }
      }
   }
   return overlap;
}
//---------------------------------------------------------------------------

void MagnetoEngine::drawBalls()
{
   Entity* object;
   for(EntitySet::iterator it = entities.begin(); it != entities.end(); it++)
   {
      object = *it;
      object->draw();
   }
}
//---------------------------------------------------------------------------

void MagnetoEngine::makeBall(void)
{
   Ball* b1 = new Ball(app);
   b1->initializePosition();
   int ch = rand() % 2;
//   int ch = 0;
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

Vec2d MagnetoEngine::calcForce(Brick* brick, Ball* ball)
{
   Vec2d force = 0;
   int positionIndex;
   if(brick->getY() > ball->getY())
   {
      //ueber Brick
      positionIndex = 1;
   }
   else if(brick->getY() + brick->height < ball->getY())
   {
      //unter Brick
      positionIndex = 2;
   }
   else
   {
      //in Brick
      positionIndex = 3;
   }

   if(brick->getX() > ball->getX())
   {
      //links von Brick
      positionIndex *= 1;
   }
   else if(brick->getX() + brick->width < ball->getX())
   {
      //rechts Brick
      positionIndex *= 10;
   }
   else
   {
      //in Brick
      positionIndex *= 100;
   }

   switch(positionIndex)
   {
   case 1://obenlinks
      {
         Vec2d distance = ball->getPosition() - brick->getPosition();
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 2: //untenlinks
      {
         Vec2d p = brick->getPosition();
         p.y += brick->height;
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 3://links
      {
         Vec2d p = ball->getPosition();
         p.x = brick->getX();
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 10://obenrechts
      {
         Vec2d p = brick->getPosition();
         p.x += brick->width;
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 20://untenrechts
      {
         Vec2d p = brick->getPosition();
         p.y += brick->height;
         p.x += brick->width;
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 30://rechts
      {
         Vec2d p = ball->getPosition();
         p.x = brick->getX() + brick->width;
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 100://oben
      {
         Vec2d p = ball->getPosition();
         p.y = brick->getY();
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 200://unten
      {
         Vec2d p = ball->getPosition();
         p.y = brick->getY() + brick->height;
         Vec2d distance = ball->getPosition() - p;
         float length = distance.length();
         float charge = ball->getCharge() * brick->getCharge();
         float forceval = (charge * Ball::ballacc / (length * length));
         force = (distance/length) * forceval;
      }
      break;
   case 300://innen
      break;
   }
   return force;
}
//---------------------------------------------------------------------------
