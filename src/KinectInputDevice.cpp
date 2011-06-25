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
   x_pstrech = 1;
   x_nstrech = 1;

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
   double x_nwinkel;
   double x_pwinkel;
   if(leftHand)
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_LHAND, P_LSHOULDER);
      x_pwinkel = 110;
      x_nwinkel = 160;
   }
   else
   {
      p = Application::myself->kinect.getPlayerPart(playerNr, P_RHAND, P_RSHOULDER);
      x_pwinkel = 160;
      x_nwinkel = 110;
   }

   if(x_max == 0 || x_min == 0)// || !y_kali)
   {
      if((p.z < 100) && (p.z > -20))
      {
         if((p.y < 50) && (p.y > -50))
         {
            double winkel = Application::myself->kinect.getWinkelELBOW(playerNr, leftHand);
            if(p.x > 0)
            {
               if((winkel > x_pwinkel) && x_max == 0)
               {
                  x_max = p.x;
                  x_pstrech = (Application::x_res/2.0)/abs(x_max);
                  cout << "player " << playerNr << " x_max calc " << x_pstrech << endl;
               }
            }
            else
            {
               if((winkel > x_nwinkel) && x_min == 0)
               {
                  x_min = p.x;
                  x_nstrech = (Application::x_res/2.0)/abs(x_min);
                  cout << "player " << playerNr << " x_min calc " << x_nstrech << endl;
               }
            }
         }
      }
   }

   if(p.x < 0) p.x = (p.x * x_nstrech +(Application::x_res/2.0) + x_offset);
   else        p.x = (p.x * x_pstrech +(Application::x_res/2.0) + x_offset);

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
