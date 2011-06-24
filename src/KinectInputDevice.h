/*
 * KinectInputDevice.h
 *
 *  Created on: 24.06.2011
 *      Author: matthas
 */

#ifndef KINECTINPUTDEVICE_H_
#define KINECTINPUTDEVICE_H_

#include "InputDevice.h"

class KinectInputDevice : public InputDevice
{
public:
   KinectInputDevice(int nr, bool leftHand);
   virtual ~KinectInputDevice();

   void setHand(bool leftHand);
   void setPlayer(int nr);

   CL_Point getPoint(void);
   float getZ(void);

private:
   bool leftHand;
   int  playerNr;
};

#endif /* KINECTINPUTDEVICE_H_ */
