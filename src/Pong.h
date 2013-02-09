/*
 * Pong.h
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#ifndef PONG_H_
#define PONG_H_

#include "MagnetoEngine.h"

class Pong : public MagnetoEngine
{
public:
   Pong(Application* app);
   virtual ~Pong();

   void run(float timediff);

   void restartMatch();

private:
   bool checkBall(Ball* ball);
   void ballOut(int player);

   void startMatch();

   void drawScores(int s1, int s2);
   void doEsterEgg(int playerNr, int egg);

   bool  inMatch;
   float timeToMatch;
};

#endif /* PONG_H_ */
