/*
 * Bat.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef BAT_H_
#define BAT_H_

#include "Entity.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

class Bat: public Entity {
public:
	Bat(Application* application);
	virtual ~Bat();


private:
};

#endif /* BAT_H_ */
