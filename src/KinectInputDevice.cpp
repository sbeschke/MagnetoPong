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

   if(!x_kali || !y_kali)
   {
      double winkel = Application::myself->kinect.getWinkel(playerNr, !leftHand);
      if(winkel < 5)
      {
         if((p.z < 100) && (p.z > -20))
         {
            if((p.y < 50) && (p.y > -50) && !x_kali)
            {
               if(p.x > 0)
               {
                  x_max = p.x;
               }
               else
               {
                  x_min = p.x;
               }

               if(x_min != 0 && x_max != 0)
               {
                  double size = x_max - x_min;
                  x_strech = Application::x_res/size;
                  x_kali = true;
                  cout << "x_kalk " << x_strech << "\n";
               }
            }
   /*         else if((p.x < 50) && (p.x > -50) && !y_kali)
            {
               if(p.y > 0)
               {
                  y_max = p.y;
               }
               else
               {
                  y_min = p.y;
               }

               if(y_min != 0 && y_max != 0)
               {
                  double size = y_max - y_min;
                  y_strech = Application::y_res/size;
                  y_kali = true;
                  cout << "y_kalk " << y_strech << "\n";
               }
            }*/
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
   double winkel = Application::myself->kinect.getWinkel(playerNr, !leftHand);
   winkel -= 45;
   winkel /= 45;
   if(winkel > 1.0) winkel = 1.0;
   else if(winkel < -1.0) winkel = -1.0;

   return winkel;
}
//---------------------------------------------------------------------------
