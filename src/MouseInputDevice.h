/*
 * MouseInputDevice.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef MOUSEINPUTDEVICE_H_
#define MOUSEINPUTDEVICE_H_

#include "InputDevice.h"
#include <ClanLib/core.h>

class MouseInputDevice: public InputDevice {
public:
	MouseInputDevice(CL_InputDevice* mouse);
	virtual ~MouseInputDevice();

	CL_Point getPoint(void);
	float getZ(void);
	bool getJump(void) { return false; }
	bool  getKick() {return false;}

private:

	CL_InputDevice* mouse;
	float zValue;
};

#endif /* MOUSEINPUTDEVICE_H_ */
