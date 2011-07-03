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

class MagnetoEngine
{
public:
   MagnetoEngine(Application* app);
   virtual ~MagnetoEngine();

   virtual void run(float timediff) =0;

   EntitySet entities;

   void addEntity(Entity* entity);
   void remEntity(Entity* entity);

protected:
   virtual bool checkBall(Ball* ball)=0;

   bool calcCollision(float timediff);
   void makeBall();
   void remBall(Ball* ball);
   void clearBalls();

   void doSpawnBall();

   int solidSides;

   Application* app;

   float timeToSpawnBall;
   float timeToSpawnBallVal;
   bool  spawnBall;

private:
   void ballOut(int player);
   void drawScores(int s1, int s2);
};

#endif /* MAGNETOENGINE_H_ */
