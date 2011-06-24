/*
 * Entity.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Entity.h"

Entity::Entity(Application* application)
: application(application), charge(0.0f), mass(0.0f)
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

float Entity::getCharge(void)
{
	return this->charge;
}

void Entity::setCharge(float charge)
{
	this->charge = charge;
}

float Entity::getMass(void)
{
	return this->mass;
}

void Entity::setMass(float mass)
{
	this->mass = mass;
}
