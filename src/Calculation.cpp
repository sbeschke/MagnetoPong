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
