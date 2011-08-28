/*
 * MouseInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "MouseInputDevice.h"

#include <iostream>

MouseInputDevice::MouseInputDevice(CL_InputDevice* mouse)
: mouse(mouse), zValue(1)
{
   klick = false;
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
   klick = mouse->get_keycode(mouse->string_to_keyid("Mouse Left"));
   if(klick && !klickRead)
   {
      klickRead = true;
      return true;
   }
   else if(!klick)
   {
      klickRead = false;
   }
   return false;
}
