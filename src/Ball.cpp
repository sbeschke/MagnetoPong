/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Ball.h"


Ball::Ball(Application* application)
: Entity(application)
{
}

Ball::~Ball() {
}

void Ball::draw(void)
{
	CL_Draw::circle(application->getGC(), CL_Pointf(getX(), getY()), 15, CL_Colorf::white);
}
void Ball::updateforces(const std::vector<Entity*>& objects, float timedifference)
{
	this->force = Vec2d(0,0);
	for(int i = 0; i < objects.size(); i++)
	{
		if(objects[i]!=this)
		{
			Vec2d distance = objects[i]->getPosition() - this->getPosition();

			float length = distance.length();


			float charge = objects[i]->getCharge() * this->getCharge();

			if(0 != length)
			{
				this->force += distance.normalize() * charge / (length * length *length);
			}

		}

	}
}
void Ball::updateposition(float timedifference)
{
	speed += this->force * timedifference;
	Vec2d newpos = this->getPosition()+this->speed*timedifference;
	if(newpos.y > 480)
		newpos.y -= 480;
	if(newpos.y < 0)
			newpos.y += 480;
	this->setPosition(newpos);

}
Vec2d Ball::getForce()
{
	return this->force;
}
