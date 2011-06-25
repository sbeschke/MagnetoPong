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
   bool  getJump();

private:
   bool leftHand;
   int  playerNr;

   double lastTorsoY;

   double x_offset;
   double x_pstrech;
   double x_nstrech;
   double x_min;
   double x_max;

   double y_offset;
   double y_strech;
   double y_min;
   double y_max;

   bool y_kali;
   bool x_kali;
};

#endif /* KINECTINPUTDEVICE_H_ */
