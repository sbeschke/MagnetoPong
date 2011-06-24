/*
 * Entity.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Entity.h"

Entity::Entity(Application* application)
: application(application)
{

}

Entity::~Entity() {

}

Vec2d Entity::getPosition(void)
{
	return position;
}

float Entity::getX(void)
{
	return position.x;
}

float Entity::getY(void)
{
	return position.y;
}

void Entity::setPosition(const Vec2d& position)
{
	this->position = position;
}
