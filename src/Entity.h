/*
 * Entity.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "Vec2d.h"
#include "Application.h"

class Entity {
public:
	Entity(Application* application);
	virtual ~Entity();

	virtual void draw(void) =0;

	virtual Vec2d getPosition(void);
	virtual float getX(void);
	virtual float getY(void);
	virtual void setPosition(const Vec2d& position);

protected:
	Application* application;
private:
	Vec2d position;
};

#endif /* ENTITY_H_ */
