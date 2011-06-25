/*
 * Entity.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Entity.h"
#include "Application.h"

Entity::Entity(Application* application)
: application(application), charge(0.0f), mass(0.0f), radius(10.0f), color(CL_Colorf::white)
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

void Entity::draw(void)
{
	float charge = getCharge();
	CL_Colorf fieldColor = charge > 0 ?
			CL_Colorf(0.0f, 2.0f, 0.0f, 1.0f) : CL_Colorf(2.0f, 0.0f, 0.0f, 1.0f);
	fieldColor.set_alpha(abs(charge));
	CL_Pointf center(getX(), getY());
	if(Application::detail >= 1) {
		CL_Draw::gradient_circle(application->getGC(), center, radius+20.0f,
			CL_Gradient(fieldColor, CL_Colorf::transparent));
	}
	else {
		CL_Draw::circle(application->getGC(), center, radius+20.0f, fieldColor);
	}
	CL_Draw::circle(application->getGC(), center, radius, getColor());
}

CL_Colorf Entity::getColor()
{
	return color;
}

void Entity::setColor(CL_Colorf color)
{
	this->color = color;
}

float Entity::getRadius(void) {
	return radius;
}

void Entity::setRadius(float radius) {
	this->radius = radius;
}
