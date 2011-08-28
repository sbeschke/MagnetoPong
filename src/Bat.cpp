/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Bat.h"
#include <sstream>
#include "Application.h"

int Bat::radius;

Bat::Bat(Application* application)
: Entity(application)
{
	setColor(CL_Colorf::cornsilk);
	setRadius(Bat::radius);
	type = TYPE_BAT;
}

Bat::~Bat()
{
}
