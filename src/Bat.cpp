/*
 * Bat.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Bat.h"
#include <sstream>
#include "Application.h"

Bat::Bat(Application* application)
: Entity(application)
{
	setColor(CL_Colorf::cornsilk);
	setRadius(20.0f);
}

Bat::~Bat() {
}

