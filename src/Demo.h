/*
 * Demo.h
 *
 *  Created on: 03.07.2011
 *      Author: matthas
 */

#ifndef DEMO_H_
#define DEMO_H_

#include "MagnetoEngine.h"

class Demo : public MagnetoEngine
{
public:
   Demo(Application* app);
   virtual ~Demo();

   void run(float timediff);

private:
   bool checkBall(Ball* ball);
};

#endif /* DEMO_H_ */
