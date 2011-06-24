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

#ifndef BALLACC
#define BALLACC 100.0
#endif
#ifndef WALLACC
#define WALLACC 1e-6
#endif
#ifndef RADIUS
#define RADIUS 15
#endif


class Ball: public Entity {
public:
	Ball(Application* application,Vec2d windowFrame);
	virtual ~Ball();

	void draw(void);
	void updateforces(const EntitySet& objects, float timedifference);
	void updateposition(float timedifference);
	void initializePosition();

	Vec2d getForce();

private:
	Vec2d speed;
	Vec2d force;
	Vec2d windowFrame;
};

#endif /* BALL_H_ */
