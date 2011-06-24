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
	CL_Draw::circle(application->getGC(), CL_Pointf(getX(), getY()), 15, CL_Colorf::white);
}
