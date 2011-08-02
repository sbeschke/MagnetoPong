/*
 * KinectInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: matthias
 */

#include "KinectInputDevice.h"
#include "Application.h"
#include "Calculation.h"
#include <iostream>

KinectInputDevice::KinectInputDevice(OpenNi* kinect, double xres, double yres, int nr, bool lefthand)
{
   this->kinect = kinect;
   x_res = xres;
   y_res = yres;
   leftHand = lefthand;
   playerNr = nr;

   calibrated = false;

   x_offset = 0;
   x_strech  = 1;

   y_offset = 0;
   y_strech = 1;

   lastTorsoY = 0;
   kickingR = 0;
   kickingL = 0;

   invert   = false;
   jumping  = false;
   invertTimeout = 0;
   feldWinkel = 0;

   egg = 0;
   eggRead = false;

   klick = false;
   klickRead = false;

   exit = false;
   exitRead = false;
}

KinectInputDevice::~KinectInputDevice()
{
}
//---------------------------------------------------------------------------

void KinectInputDevice::setHand(bool lefthand)
{
   this->leftHand = lefthand;
}
//---------------------------------------------------------------------------

void KinectInputDevice::setPlayer(int nr)
{
   playerNr = nr;
   calibrate();
}
//---------------------------------------------------------------------------

void KinectInputDevice::processInput(float timepast)
{
   if(invert)
   {
      invertTimeout += timepast;
      if(invertTimeout > 20000) invert = false;
   }

   calcPos();
   calcFeldWinkel();
   calcJump();
   calcKicking();
   calcEgg();
   calcKlick();
   calcExit();
   calcLaufen();
}
//---------------------------------------------------------------------------

CL_Point KinectInputDevice::getPoint()
{
   return CL_Point(handPoint.x, handPoint.y);
}
//---------------------------------------------------------------------------

float KinectInputDevice::getZ()
{
   return feldWinkel;
}
//---------------------------------------------------------------------------

bool KinectInputDevice::getJump()
{
   return jumping;
}
//---------------------------------------------------------------------------

int KinectInputDevice::getEsterEgg()
{
   if(egg && !eggRead)
   {
      eggRead = true;
      return egg;
   }
   else
   {
      return 0;
   }
}
//---------------------------------------------------------------------------

bool KinectInputDevice::getKlick()
{
   if(klick && !klickRead)
   {
      klickRead = true;
      return true;

   }
   else
   {
      return false;
   }
}
//---------------------------------------------------------------------------

bool KinectInputDevice::getExit()
{
   if(exit && !exitRead)
   {
      exitRead = true;
      return true;

   }
   else
   {
      return false;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcPos()
{
   double x_nwinkel;
   double x_pwinkel;

   OpenNiPoint p;

   if(leftHand)
   {
      p = kinect->getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
      x_pwinkel = 110;
      x_nwinkel = 130;
   }
   else
   {
      p = kinect->getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
      x_pwinkel = 130;
      x_nwinkel = 110;
   }

   if(invert)
   {
      p.x *= -1.0;
      p.y *= -1.0;
   }

   if(!calibrated)//Kalibrierung
   {
      calibrate();
   }

   handPoint.x = (handPoint.x + (p.x * x_strech +(x_res/2.0) + x_offset)) / 2.0;
   handPoint.y = (handPoint.y + (p.y * y_strech +(y_res/2.0) + y_offset)) / 2.0;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calibrate()
{
   double armlength;
   OpenNiPoint unterarm;
   OpenNiPoint oberarm;
   if(leftHand)
   {
      unterarm = kinect->getPlayerPart(playerNr, P_LHAND,  P_LELBOW);
      oberarm  = kinect->getPlayerPart(playerNr, P_LELBOW, P_LSHOULDER);

   }
   else
   {
      unterarm = kinect->getPlayerPart(playerNr, P_RHAND,  P_RELBOW);
      oberarm  = kinect->getPlayerPart(playerNr, P_RELBOW, P_RSHOULDER);
   }
   armlength = unterarm.length() + oberarm.length();
   //armlength *= 0.9;
   double winkel = atan(y_res/x_res);
   cout << winkel * PI_TO_GRAD << endl;
   double xres = cos(winkel) * armlength;
   double yres = sin(winkel) * armlength;

   if(armlength && winkel)
   {
      x_strech = (x_res/2.0) / xres;
      y_strech = (y_res/2.0) / yres;

      cout << "calibrated: " << armlength << " : " << x_strech << "|" << y_strech << endl;;
      calibrated = true;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcFeldWinkel()
{
   feldWinkel = kinect->getWinkelELBOW(playerNr, !leftHand);

   feldWinkel -= 90.0;
   feldWinkel /= 80.0;
   if(feldWinkel > 1.0) feldWinkel = 1.0;
   else if(feldWinkel < -1.0) feldWinkel = -1.0;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcJump()
{
   OpenNiPoint p = kinect->getPlayerPart(playerNr, P_TORSO);
   jumping = false;
   if(lastTorsoY)
   {
      if(p.y < lastTorsoY - 30)
      {
         jumping = true;
      }
   }
   lastTorsoY = p.y;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcKicking()
{
   double winkel = kinect->getWinkel(playerNr, P_RSHOULDER, P_RHIP, P_RKNEE);

   if(winkel < 90  ) kickingR = 1;
   else              kickingR = 0;

   winkel = kinect->getWinkel(playerNr, P_LSHOULDER, P_LHIP, P_LKNEE);

   if(winkel < 90  ) kickingL = 1;
   else              kickingL = 0;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcEgg()
{
   if(kickingR)
   {
      if(jumping)
      {
         egg = EGG_MEGA;
      }
      else
      {
         egg = EGG_POL;
      }
   }
   else if(kickingL)
   {
      if(jumping)
      {
      }
      else
      {
         egg = EGG_STOP;
      }
   }
   else
   {
      eggRead = false;
      egg = 0;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcKlick()
{
   if(feldWinkel < -0.7)
   {
      klick = true;
   }
   else
   {
      klick = false;
      klickRead = false;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcExit()
{
   OpenNiPoint torso = kinect->getPlayerPart(playerNr, P_TORSO);
   OpenNiPoint neck  = kinect->getPlayerPart(playerNr, P_NECK, P_TORSO);
   OpenNiPoint head  = kinect->getPlayerPart(playerNr, P_HEAD, P_TORSO);
   if(Calculation::isEqual(neck.y, torso.y, 80) && Calculation::isEqual(head.y, torso.y, 80))
   {
      exit = true;
   }
   else
   {
      exit = false;
      exitRead = false;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcLaufen()
{
   double winkelLK = kinect->getWinkel(playerNr, P_LHIP, P_LKNEE, P_LFOOT);
   double winkelRK = kinect->getWinkel(playerNr, P_RHIP, P_RKNEE, P_RFOOT);

   laufen = false;

   if(winkelLK < lastLKnee-5)
   {
      if(winkelRK > lastRKnee+5)
      {
         laufen = true;
      }
   }
   else if(winkelLK > lastLKnee+5)
   {
      if(winkelRK < lastRKnee-5)
      {
         laufen = true;
      }
   }
   lastLKnee = winkelLK;
   lastRKnee = winkelRK;
}
//---------------------------------------------------------------------------
