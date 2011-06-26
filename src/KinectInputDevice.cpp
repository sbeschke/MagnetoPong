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
   kickingR = false;
   kickingL = false;
   invert   = false;
   jumping  = false;
   invertTimeout = 0;
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

CL_Point KinectInputDevice::getPoint(float timepast)
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
   if(invert)
   {
      invertTimeout += timepast;
      cout << invert;
      p.x *= -1.0;
      p.y *= -1.0;
      if(invertTimeout > 20000) invert = false;
   }
   else if(x_max == 0 || x_min == 0)// || !y_kali)
   {
      if((p.z < 100) && (p.z > -20))
      {
         if((p.y < 50) && (p.y > -50))
         {
            double winkel = Application::myself->kinect.getWinkelELBOW(playerNr, leftHand);
            if(p.x > 0)
            {
               if((winkel > x_pwinkel))// && x_max == 0)
               {
                  x_max = p.x;
                  x_pstrech = (Application::x_res/2.0)/abs(x_max);
                  cout << "player " << playerNr << " x_max calc " << x_pstrech << endl;
               }
            }
            else
            {
               if((winkel > x_nwinkel)) //&& x_min == 0)
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
   jumping = false;
   if(lastTorsoY)
   {
      if(p.y < lastTorsoY - 30)
      {
         jumping = true;
      }
   }

   lastTorsoY = p.y;
   return jumping;
}
//---------------------------------------------------------------------------

int KinectInputDevice::getEsterEgg()
{
   int egg = 0;
   double winkel;
   winkel = Application::myself->kinect.getWinkel(playerNr, P_RSHOULDER, P_RHIP, P_RKNEE);

   if(winkel < 90  && !kickingR)
   {
      if(jumping)
      {
         egg = EGG_MEGA;
         cout << "Mega Egg\n";
         if(!leftHand)
         {
            Application::get()->osmRight.setMessage("you found the megaEgg", 2);
         }
         else
         {
            Application::get()->osmLeft.setMessage("you found the megaEgg", 2);
         }

      }
      else
      {
         egg = EGG_POL;
      }
      kickingR = true;
   }
   else if(winkel > 90)
   {
      kickingR = false;
   }

   if(!egg)
   {
      winkel = Application::myself->kinect.getWinkel(playerNr, P_LSHOULDER, P_LHIP, P_LKNEE);

      if(winkel < 90  && !kickingL)
      {
         if(jumping)
         {
         /*   cout << "Mega Egg\n";
            if(!leftHand)
            {
               Application::get()->osmRight.setMessage("you found the megaEgg", 2);
            }
            else
            {
               Application::get()->osmLeft.setMessage("you found the megaEgg", 2);
            }
            egg = EGG_MEGA;*/
         }
         else
         {
            egg = EGG_STOP;
         }
         kickingL = true;
      }
      else if(winkel > 90)
      {
         kickingL = false;
      }
   }

   return egg;
}
//---------------------------------------------------------------------------
