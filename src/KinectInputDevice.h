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
   KinectInputDevice(int nr, bool lefthand);
   virtual ~KinectInputDevice();

   void setHand(bool lefthand);
   void setPlayer(int nr);

   CL_Point getPoint(void);
   float getZ(void);

private:
   bool leftHand;
   int  playerNr;

   double max_z;
   double min_z;

   bool z_kali;


};

#endif /* KINECTINPUTDEVICE_H_ */
