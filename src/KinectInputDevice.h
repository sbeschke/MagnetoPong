/*
 * KinectInputDevice.h
 *
 *  Created on: 24.06.2011
 *      Author: matthias
 */

#ifndef KINECTINPUTDEVICE_H_
#define KINECTINPUTDEVICE_H_

#include "InputDevice.h"
#include "OpenNi.h"

#define EGG_POL    1
#define EGG_STOP   2
#define EGG_MEGA  42

#define KICK_SIDE  1
#define KICK_FRONT 2

class KinectInputDevice : public InputDevice
{
public:
   KinectInputDevice(int nr, bool lefthand);
   virtual ~KinectInputDevice();

   void setHand(bool lefthand);
   void setPlayer(int nr);

   void processInput(float timepast);
   CL_Point getPoint();
   float getZ();
   bool  getJump();
   int   getEsterEgg();
   void  setInvert(bool aktivate){invert = aktivate; invertTimeout = 0;};
   bool  getInvert() { return invert;};


private:
   void calcPos();
   void calibrate(OpenNiPoint p, double xnw, double xpw);
   void calcFeldWinkel();
   void calcJump();
   void calcKicking();
   void calcEgg();

   OpenNiPoint handPoint;
   double feldWinkel;

   bool invert;
   float invertTimeout;
   bool leftHand;
   int  playerNr;

   int kickingL;
   int kickingR;

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

   int  egg;
   bool eggRead;
};

#endif /* KINECTINPUTDEVICE_H_ */
