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

   x_kali = false;
   y_kali = false;

   x_offset = 0;
   x_strech = 1;

   y_offset = 0;
   y_strech = 1;

   x_min = 0;
   x_max = 0;

   lastTorsoY = 0;
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
      p = Application::myself->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
   }
   else
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
   }

   if(!x_kali)// || !y_kali)
   {
      if((p.z < 100) && (p.z > -20))
      {
         if((p.y < 50) && (p.y > -50))
         {
            double winkel = Application::myself->kinect.getWinkelELBOW(playerNr, leftHand);
            if(p.x > 0)
            {
               if(winkel > 170)
               {
                  x_max = p.x;
                  cout << "x_max " << x_max;
               }
            }
            else
            {
               if(winkel > 140)
               {
                  x_min = p.x;
                  cout << "x_min " << x_min;
               }
            }

            if(x_min != 0 && x_max != 0)
            {
               double size = x_max - x_min;
               x_strech = Application::x_res/size;
               x_kali = true;
               cout << "x_kalk " << x_strech << "\n";
            }
         }
      }
   }

   p.x = (p.x+(Application::x_res/2.0) + x_offset) * x_strech;
   p.y = (p.y+(Application::y_res/2.0) + y_offset) * y_strech;


   return CL_Point(p.x, p.y);
}
//---------------------------------------------------------------------------

float KinectInputDevice::getZ(void)
{
   double winkel = Application::myself->kinect.getWinkelELBOW(playerNr, !leftHand);

   winkel -= 90.0;
   winkel /= 80.0;
   if(winkel > 1.0) winkel = 1.0;
   else if(winkel < -1.0) winkel = -1.0;

   return winkel;
}
//---------------------------------------------------------------------------

bool KinectInputDevice::getJump()
{
   OpenNiPoint p = Application::myself->kinect.getPlayerPart(playerNr, P_TORSO);
   bool jump = false;
   if(lastTorsoY)
   {
      if(p.y < lastTorsoY - 30)
      {
         jump = true;
        // cout << "jump\n";
      }
   }

   lastTorsoY = p.y;
   return jump;
}
