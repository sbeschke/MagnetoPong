/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Ball.h"
#include "Application.h"


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
void Ball::updateforces(const EntitySet& objects, float timedifference)
{
	this->force = Vec2d(0,0);
	Vec2d position = this->getPosition();
	for(EntitySet::iterator it = objects.begin(); it != objects.end(); it++)
	{
		Entity* object = *it;
		if(object!=this)
		{
			Vec2d distance = object->getPosition() - position;

			float length = distance.length();


			float charge = object->getCharge() * this->getCharge();

			if(0 != length)
			{
				this->force += distance.normalize() * charge / (length * length *length);
			}

		}
	}
	//borderforces

	int distance_to_middle = 240 - position.y;
	float borderparam = 1e-4;
	float borderforce = borderparam*(distance_to_middle);
	this->force.y += borderforce;



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
