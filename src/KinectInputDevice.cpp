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

   x_kali = false;
   y_kali = false;

   x_offset = 0;
   x_pstrech = 1;
   x_nstrech = 1;

   y_offset = 0;
   y_strech = 1;

   x_min = 0;
   x_max = 0;

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

   if(leftHand)
   {
      handPoint = Application::get()->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
      x_pwinkel = 110;
      x_nwinkel = 130;
   }
   else
   {
      handPoint = Application::get()->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
      x_pwinkel = 130;
      x_nwinkel = 110;
   }

   if(invert)
   {
      handPoint.x *= -1.0;
      handPoint.y *= -1.0;
   }
   else if(x_max == 0 || x_min == 0)//Kalibrierung
   {
      calibrate(handPoint, x_nwinkel, x_pwinkel);
   }

   if(handPoint.x < 0) handPoint.x = (handPoint.x * x_nstrech +(Application::x_res/2.0) + x_offset);
   else                handPoint.x = (handPoint.x * x_pstrech +(Application::x_res/2.0) + x_offset);

   handPoint.y = (handPoint.y+(Application::y_res/2.0) + y_offset) * y_strech;
}
//---------------------------------------------------------------------------

void KinectInputDevice::calibrate(OpenNiPoint p, double xnw, double xpw)
{
   double winkel = Application::get()->kinect.getWinkelELBOW(playerNr, leftHand);
   if(p.x > 0)
   {
      if((winkel > xpw) && (winkel < xpw+10))
      {
         if(Calculation::pointonLine(OpenNiPoint(0,0,30), OpenNiPoint(1,0,0), 300, p))
         {
            x_max = p.x;
            x_pstrech = (Application::x_res/2.0)/abs(x_max);
            cout << "player " << playerNr << " x_max calc " << x_pstrech << endl;
         }
      }
   }
   else
   {
      if((winkel > xnw) && (winkel < xnw+10))
      {
         if(Calculation::pointonLine(OpenNiPoint(0,0,30), OpenNiPoint(1,0,0), 300, p))
         {
            x_min = p.x;
            x_nstrech = (Application::x_res/2.0)/abs(x_min);
            cout << "player " << playerNr << " x_min calc " << x_nstrech << endl;
         }
      }
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
   if(feldWinkel > 0.5)
   {
      klick = true;
   }
   else
   {
      klick = false;
      klickRead = false;
   }
}
