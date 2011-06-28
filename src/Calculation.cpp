/*
 * Calculation.cpp
 *
 *  Created on: 27.06.2011
 *      Author: matthias
 */

#include "Calculation.h"

#include <iostream>

bool Calculation::pointonLine(OpenNiPoint lineP, OpenNiPoint lineDir, double lineWidth, OpenNiPoint point)
{
   point = point - lineP;
   double length = point.length();
   double winkel = getWinkel(lineDir, point, true);
   double dist = length* sin(winkel);

   return dist <= lineWidth;
}
//---------------------------------------------------------------------------

double Calculation::getWinkel(OpenNiPoint pos1, OpenNiPoint gelenk, OpenNiPoint pos2, bool rad)
{
   return getWinkel(pos1 - gelenk, pos2 - gelenk, rad);
}
//---------------------------------------------------------------------------

double Calculation::getWinkel(OpenNiPoint vector1, OpenNiPoint vector2, bool rad)
{
   double winkel = acos((vector1*vector2)/(vector1.length()*vector2.length()));

   if(rad) return winkel;
   else    return winkel* 57.295779513082320876798154814105;
}
//---------------------------------------------------------------------------

int Calculation::hsl_to_rgb(double h, double s, double l)
{
   int r, g, b;
   double  dh = h/360;
   double temp1,temp2;

   if(l == 0)
   {
      r = g = b = 0;
   }
   else
   {
      if(s == 0)
      {
         r = g = b = l*255.0+0.5;
      }
      else
      {
         if(l < 0.5)
         {
            temp2 = l * (1.0 + s);
         }
         else
         {
            temp2 = (l + s) -(l * s);
         }
         temp1 = 2.0 * l - temp2;

         double t3[]  = {dh+1.0/3.0, dh, dh-1.0/3.0};
         double clr[] = {0,0,0};
         for(int i=0; i<3; i++)
         {
            if(t3[i]<0) t3[i] += 1.0;
            if(t3[i]>1) t3[i] -= 1.0;

            if(6.0*t3[i] < 1.0) clr[i] = temp1 + (temp2 - temp1) * t3[i] * 6.0;
            else if(2.0*t3[i] < 1.0) clr[i] = temp2;
            else if(3.0*t3[i] < 2.0) clr[i] = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - t3[i]) * 6.0;
            else clr[i] = temp1;
         }

         r = clr[0]*255.0+0.5;
         g = clr[1]*255.0+0.5;
         b = clr[2]*255.0+0.5;
      }
   }

   return (b << 16) + (g << 8) + r;
}
