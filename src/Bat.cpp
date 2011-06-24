/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Bat.h"

Bat::Bat(Application* application)
: Entity(application)
{
}

Bat::~Bat() {
}

void Bat::draw(void)
{
	float charge = getCharge();
	CL_Colorf color;
	color.set_alpha(255);
	color.set_blue(255);
	color.set_red(255.0f * charge);
	color.set_green(255.0f * (1.0f - charge));
	CL_Draw::circle(application->getGC(), CL_Pointf(getX(), getY()), 15, color);
}
