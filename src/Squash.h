/*
 * Squash.h
 *
 *  Created on: 03.07.2011
 *      Author: matthas
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

private:
   void startMatch();

   bool checkBall(Ball* ball);
   void ballOut(int player);

   void drawScores(int s1);

   bool  inMatch;
   float timeToMatch;
};

#endif /* SQUASH_H_ */
