/*
 * MouseInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "MouseInputDevice.h"


#include <iostream>

MouseInputDevice::MouseInputDevice(CL_InputDevice* mouse)
: mouse(mouse), zValue(0.5f)
{

}

MouseInputDevice::~MouseInputDevice()
{
}

CL_Point MouseInputDevice::getPoint()
{
	return mouse->get_position();
}

float MouseInputDevice::getZ(void)
{
	return zValue;
}

bool MouseInputDevice::getKlick()
{
   return mouse->get_keycode(mouse->string_to_keyid("Mouse Left"));
}
