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

class KinectInputDevice : public InputDevice
{
public:
   KinectInputDevice(OpenNi* kinect, double xres, double yres, int nr, bool lefthand);
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
   bool  getKlick();
   bool  getExit();
   bool  getLaufen(){return laufen;};

private:
   void calcPos();
   void calibrate();
   void calcFeldWinkel();
   void calcJump();
   void calcKicking();
   void calcEgg();
   void calcKlick();
   void calcExit();
   void calcLaufen();

   OpenNi* kinect;
   double x_res;
   double y_res;

   bool leftHand;
   int  playerNr;

   OpenNiPoint handPoint;
   double feldWinkel;

   bool  invert;
   float invertTimeout;

   int kickingL;
   int kickingR;

   bool jumping;

   double lastTorsoY;

   double x_offset;
   double x_strech;

   double y_offset;
   double y_strech;

   bool calibrated;

   int  egg;
   bool eggRead;

   bool klick;
   bool klickRead;

   bool exit;
   bool exitRead;

   bool laufen;
   double lastLKnee;
   double lastRKnee;
};

#endif /* KINECTINPUTDEVICE_H_ */
