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

void Ball::updateforces(const EntitySet& objects, float timedifference)
{
	this->force = Vec2d(0,0);
	Vec2d position = this->getPosition();
	for(EntitySet::iterator it = objects.begin(); it != objects.end(); it++)
	{

		Entity* object = *it;
		if(object!=this)

		{
			Vec2d distance = position - object->getPosition();
			float length = distance.length();
			float charge = object->getCharge() * this->getCharge();

			if( 2*RADIUS < length)
			{
				float forceAmount = charge * BALLACC / (length * length);
				//std::cout << "Force amount: " << forceAmount << std::endl;
				this->force += (distance/length) * forceAmount;
			}
			else
			{



			}

		}
	}
	//borderforces

	/*int distance_to_middle = 240 - position.y;
	float borderparam = 1e-6;
	float borderforce = borderparam*(distance_to_middle);
	this->force.y += borderforce;*/



}
void Ball::initializePosition()
{
	Vec2d startpos = windowFrame/2;
	startpos.x += (rand() % 21)-10;//;/RAND_MAX*20)-10;
	startpos.y  =  rand() % (int)windowFrame.y;///RAND_MAX*windowFrame.y-(windowFrame.y/2);
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
	if(newpos.x > windowFrame.x || newpos.x < 0 || newpos.y > windowFrame.y || newpos.y < 0)
	{
		initializePosition();
		this->speed = Vec2d(0,0);
		//TODO emit gameover
	}

}
Vec2d Ball::getForce()
{
	return this->force;
}
