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

class Ball: public Entity {
public:
	Ball(Application* application);
	virtual ~Ball();

	void draw(void);
	void updateforces(const EntitySet& objects, float timedifference);
	void updateposition(float timedifference);


	Vec2d getForce();

private:
	Vec2d speed;
	Vec2d force;
};

#endif /* BALL_H_ */
