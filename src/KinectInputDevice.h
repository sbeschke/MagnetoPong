/*
 * KinectInputDevice.h
 *
 *  Created on: 24.06.2011
 *      Author: matthas
 */

#ifndef KINECTINPUTDEVICE_H_
#define KINECTINPUTDEVICE_H_

#include "InputDevice.h"

#define EGG_POL    1
#define EGG_STOP   2
#define EGG_MEGA  42

class KinectInputDevice : public InputDevice
{
public:
   KinectInputDevice(int nr, bool lefthand);
   virtual ~KinectInputDevice();

   void setHand(bool lefthand);
   void setPlayer(int nr);
   void setInvert(bool aktivate){invert = aktivate; invertTimeout = 0;};
   bool getInvert() { return invert;};

   CL_Point getPoint(float timepast);
   float getZ(void);
   bool  getJump();
   int   getEsterEgg();

private:
   bool invert;
   float invertTimeout;
   bool leftHand;
   int  playerNr;

   bool kickingL;
   bool kickingR;
   bool jumping;

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
