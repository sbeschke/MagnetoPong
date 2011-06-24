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

	virtual CL_Point getPoint(void) =0;
	virtual float getZ(void) =0;
};

#endif /* INPUTDEVICE_H_ */
