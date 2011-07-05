/*
 * Bat.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef BALL_H_
#define BALL_H_

#include "Entity.h"
#include <vector>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
/*
#ifndef BALLACC
#define BALLACC 5.0
#endif
#ifndef RADIUS
#define RADIUS 15
#endif
*/

class Ball: public Entity
{
public:
   static float ballacc;
   static float radius;

	Ball(Application* application,Vec2d windowFrame);
	virtual ~Ball();

	void draw(void);
	void updateposition(float timedifference, int solidSides);
	void initializePosition();

	Vec2d getForce();
	void  addForce(Vec2d force);

	void  setSpeed(Vec2d v);
	Vec2d getSpeed() {return speed;};

private:
	Vec2d speed;
	Vec2d force;
	Vec2d windowFrame;
};

#endif /* BALL_H_ */
