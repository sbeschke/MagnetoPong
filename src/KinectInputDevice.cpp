/*
 * KinectInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: matthas
 */

#include "KinectInputDevice.h"
#include "OpenNi.h"
#include "Application.h"
#include <iostream>

KinectInputDevice::KinectInputDevice(int nr, bool lefthand)
{
   leftHand = lefthand;
   playerNr = nr;
   min_z = 0;
   max_z = 600;

   z_kali = false;
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

CL_Point KinectInputDevice::getPoint(void)
{
   OpenNiPoint p;
   if(leftHand)
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
   }
   else
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
   }
   return CL_Point((p.x+Application::x_res/2), (p.y+Application::y_res/2));
}
//---------------------------------------------------------------------------

float KinectInputDevice::getZ(void)
{
   double winkel = Application::myself->kinect.getWinkel(playerNr, !leftHand);
   winkel -= 45;
   winkel /= 45;
   if(winkel > 1.0) winkel = 1.0;
   else if(winkel < -1.0) winkel = -1.0;

   return winkel;
/*
   OpenNiPoint p;
   if(leftHand)
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
   }
   else
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
   }

   if(!z_kali)
   {
      double winkel = Application::myself->kinect.getWinkel(playerNr, leftHand);
      if(winkel < 2)
      {
         max_z = p.length();
         z_kali = true;

         cout << "kali\n";
      }


   }

   double dist = p.length();
   if(dist > max_z)  dist = 1.0;
   else if(dist < min_z) dist = -1.0;
   else
   {
      dist = (dist/max_z)*2.0 - 1.0;
   }
   return dist;
   */
}
//---------------------------------------------------------------------------
