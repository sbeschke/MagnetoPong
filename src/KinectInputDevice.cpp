/*
 * KinectInputDevice.cpp
 *
 *  Created on: 24.06.2011
 *      Author: matthas
 */

#include "KinectInputDevice.h"
#include "OpenNi.h"
#include "Application.h"

KinectInputDevice::KinectInputDevice(int nr, bool leftHand)
{
   leftHand = leftHand;
   playerNr = nr;
}

KinectInputDevice::~KinectInputDevice()
{
}
//---------------------------------------------------------------------------

void KinectInputDevice::setHand(bool leftHand)
{
   this->leftHand = leftHand;
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
   return p.z;
}
//---------------------------------------------------------------------------
