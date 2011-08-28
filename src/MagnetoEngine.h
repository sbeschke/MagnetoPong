/*
 * MagnetoEngine.h
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#ifndef MAGNETOENGINE_H_
#define MAGNETOENGINE_H_

#include "Entity.h"
class Application;
class Ball;
class Brick;

class MagnetoEngine
{
public:
   MagnetoEngine(Application* app);
   virtual ~MagnetoEngine();

   virtual void run(float timediff) =0;

   void addEntity(Entity* entity);
   void remEntity(Entity* entity);

protected:
   virtual void ballOut(int side)=0;
   virtual int  checkBall(Ball* ball);

   bool calcForces(float timediff); //to be called in run

   void drawBalls();
   void makeBall();
   void remBall(Ball* ball);
   void clearBalls();

   int solidSides;

   Application* app;

   float timeToSpawnBall;
   float timeToSpawnBallVal;

   EntitySet entities;
private:
   Vec2d calcForce(Brick* brick, Ball* ball);

};

#endif /* MAGNETOENGINE_H_ */
