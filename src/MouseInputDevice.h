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

	void processInput(float timepast){};
	CL_Point getPoint();
	float getZ(void);
	bool  getJump(void) {return false;}
	int   getEsterEgg() {return 0;}
	void  setInvert(bool aktivate) {};
   bool  getInvert(){return false;}
   bool  getKlick();
   bool  getExit() {return false;}
   bool  getLaufen() {return false;};

private:

	CL_InputDevice* mouse;
	float zValue;
	bool klick;
	bool klickRead;
};

#endif /* MOUSEINPUTDEVICE_H_ */
