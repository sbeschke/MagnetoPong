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
void Ball::updateforces(const std::vector<Entity*>& objects)
{
	for(int i = 0; i < objects.size(); i++)
	{
		if(objects[i]!=this)
		{
			//this->force += objects[i]->getX();

		}

	}

}
