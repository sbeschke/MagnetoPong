/*
 * Entity.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vec2d.h"
#include <set>

class Application;

class Entity {
public:
	Entity(Application* application);
	virtual ~Entity();

	virtual void draw(void) =0;

	virtual Vec2d getPosition(void);
	virtual float getX(void);
	virtual float getY(void);
	virtual void setPosition(const Vec2d& position);
	virtual float getCharge(void);
	virtual void setCharge(float charge);
	virtual float getMass(void);
	virtual void setMass(float mass);

protected:
	Application* application;
private:
	Vec2d position;
	float charge;
	float mass;
};

typedef std::set<Entity*> EntitySet;


#endif /* ENTITY_H_ */
