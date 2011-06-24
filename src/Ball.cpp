/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Ball.h"


Ball::Ball(Application* application, Vec2d windowFrame)
: Entity(application)
{
	this->windowFrame = windowFrame;

}

Ball::~Ball() {
}

void Ball::draw(void)
{
	CL_Draw::circle(application->getGC(), CL_Pointf(getX(), getY()), RADIUS, CL_Colorf::white);
}
void Ball::updateforces(const std::vector<Entity*>& objects, float timedifference)
{
	this->force = Vec2d(0,0);
	Vec2d position = this->getPosition();
	for(int i = 0; i < objects.size(); i++)
	{

		if(objects[i]!=this)
		{
			Vec2d distance = objects[i]->getPosition() - position;

			float length = distance.length();


			float charge = objects[i]->getCharge() * this->getCharge();

			if( 2*RADIUS < length)
			{
				this->force += distance.normalize() * charge * BALLACC / (length * length *length);
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
	this->setPosition(windowFrame/2);
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
	if(newpos.x > 640 || newpos < 0 || newpos.y > 480 || newpos.x <0)
	{
		initializePosition();
		this->speed =Vec2d(0,0);
		//TODO emit gameover
	}

}
Vec2d Ball::getForce()
{
	return this->force;
}
