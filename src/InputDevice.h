/*
 * InputDevice.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef INPUTDEVICE_H_
#define INPUTDEVICE_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>


class InputDevice {
public:
	InputDevice();
	virtual ~InputDevice();

	virtual void processInput(float timepast)=0;
	virtual CL_Point getPoint() =0;
	virtual float getZ(void) =0;
	virtual bool  getJump() =0;
	virtual int   getEsterEgg() =0;
	virtual void setInvert(bool aktivate) =0;
	virtual bool getInvert() = 0;

};

#endif /* INPUTDEVICE_H_ */
