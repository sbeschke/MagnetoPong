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

KinectInputDevice::KinectInputDevice(int nr, bool lefthand)
{
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

void KinectInputDevice::calcPos()
{
   double x_nwinkel;
   double x_pwinkel;

   OpenNiPoint p;

   if(leftHand)
   {
      p = Application::get()->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
      x_pwinkel = 110;
      x_nwinkel = 130;
   }
   else
   {
      p = Application::get()->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
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

   handPoint.x = (handPoint.x + (p.x * x_strech +(Application::x_res/2.0) + x_offset)) / 2.0;
   handPoint.y = (handPoint.y + (p.y * y_strech +(Application::y_res/2.0) + y_offset)) / 2.0;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calibrate()
{
   double armlength;
   OpenNiPoint unterarm;
   OpenNiPoint oberarm;
   if(leftHand)
   {
      unterarm = Application::get()->kinect.getPlayerPart(playerNr, P_LHAND,  P_LELBOW);
      oberarm  = Application::get()->kinect.getPlayerPart(playerNr, P_LELBOW, P_LSHOULDER);

   }
   else
   {
      unterarm = Application::get()->kinect.getPlayerPart(playerNr, P_RHAND,  P_RELBOW);
      oberarm  = Application::get()->kinect.getPlayerPart(playerNr, P_RELBOW, P_RSHOULDER);
   }
   armlength = unterarm.length() + oberarm.length();
   //armlength *= 0.9;
   double winkel = atan((double)Application::y_res/(double)Application::x_res);
   cout << winkel * PI_TO_GRAD << endl;
   double xres = cos(winkel) * armlength;
   double yres = sin(winkel) * armlength;

   if(armlength && winkel)
   {
      x_strech = (Application::x_res/2.0) / xres;
      y_strech = (Application::y_res/2.0) / yres;

      cout << "calibrated: " << armlength << " : " << x_strech << "|" << y_strech << endl;;
      calibrated = true;
   }
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcFeldWinkel()
{
   feldWinkel = Application::get()->kinect.getWinkelELBOW(playerNr, !leftHand);

   feldWinkel -= 90.0;
   feldWinkel /= 80.0;
   if(feldWinkel > 1.0) feldWinkel = 1.0;
   else if(feldWinkel < -1.0) feldWinkel = -1.0;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calcJump()
{
   OpenNiPoint p = Application::get()->kinect.getPlayerPart(playerNr, P_TORSO);
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
   double winkel = Application::get()->kinect.getWinkel(playerNr, P_RSHOULDER, P_RHIP, P_RKNEE);

   if(winkel < 90  ) kickingR = 1;
   else              kickingR = 0;

   winkel = Application::get()->kinect.getWinkel(playerNr, P_LSHOULDER, P_LHIP, P_LKNEE);

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
