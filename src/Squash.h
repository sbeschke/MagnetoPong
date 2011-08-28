/*
 * Squash.h
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#ifndef SQUASH_H_
#define SQUASH_H_

#include "MagnetoEngine.h"

class Squash : public MagnetoEngine
{
public:
   Squash(Application* app);
   virtual ~Squash();

   void run(float timediff);

   void restartMatch();
   void setDifficulty(float dif);

private:
   void ballOut(int side);
   int  checkBall(Ball* ball);

   void startMatch();

   void drawScores(int s1);

   bool  inMatch;
   float timeToMatch;
   float difficulty;
};

#endif /* SQUASH_H_ */
