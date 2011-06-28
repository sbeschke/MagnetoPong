/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Ball.h"
#include "Application.h"
#include "stdlib.h"


Ball::Ball(Application* application, Vec2d windowFrame)
: Entity(application)
{
	setColor(CL_Colorf(0.0f, 0.0f, 0.0f, 0.6f));
	this->windowFrame = windowFrame;

}

Ball::~Ball() {
}

void Ball::draw(void)
{
	Entity::draw();
}

bool Ball::updateforces(const EntitySet& objects, float timedifference)
{
	this->force = Vec2d(0,0);
	bool overlap = false;
	Vec2d position = this->getPosition();
	for(EntitySet::iterator it = objects.begin(); it != objects.end(); it++)
	{

		Entity* object = *it;
		if(object!=this)

		{
			Vec2d distance = position - object->getPosition();
			float length = distance.length();
			float charge = object->getCharge() * this->getCharge();

			bool positiv1 = getCharge() > 0;
			bool positiv2 = object->getCharge() > 0;
			//TODO what is this for? seems to be evil!
			if(positiv1 != positiv2) charge *= 1.5;
			//if the ball does not touch the object
			if( 2*RADIUS < length)
			{
				float forceAmount = charge * BALLACC / (length * length);

				this->force += (distance/length) * forceAmount;
			}
			else
			{
				//no inteaction because of overlap
			}

			//sound
			if(object->getRadius()*4*(object->getBoost()) + this->getRadius()*4*this->getBoost() > length)
			{
			   overlap = true;
			}
		}
	}
	return overlap;
}

void Ball::initializePosition()
{
	Vec2d startpos = windowFrame/2;
	startpos.x += (rand() % 21)-10;
	startpos.y  =  rand() % (int)windowFrame.y;
	this->setPosition(startpos);

}
void Ball::updateposition(float timedifference)
{
	speed += this->force * timedifference;
	Vec2d newpos = this->getPosition()+this->speed*timedifference;

	if(newpos.y + speed.y +RADIUS> windowFrame.y){
		speed.y = - speed.y;
		newpos.y= this->windowFrame.y-RADIUS;
	}
	if(newpos.y - speed.y -RADIUS< 0){
		speed.y = - speed.y;
		newpos.y= RADIUS;
	}
	this->setPosition(newpos);


}
Vec2d Ball::getForce()
{
	return this->force;
}

void Ball::setSpeed(Vec2d v)
{
   speed = v;
}
