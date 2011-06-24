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
   return CL_Point(p.x, p.y);
}
//---------------------------------------------------------------------------

float KinectInputDevice::getZ(void)
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
   if(p.z > max_z)  p.z = 1.0;
   else if(p.z < min_z) p.z = -1.0;
   else
   {
      p.z = (p.z/max_z)*2.0 - 1.0;
   }
   cout << p.z << "\n";
   return p.z;
}
//---------------------------------------------------------------------------
