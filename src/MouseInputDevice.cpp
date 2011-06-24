/*
 * MouseInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "MouseInputDevice.h"

MouseInputDevice::MouseInputDevice(CL_InputDevice* mouse)
: mouse(mouse)
{

}

MouseInputDevice::~MouseInputDevice() {
}

CL_Point MouseInputDevice::getPoint(void) {
	return mouse->get_position();
}
