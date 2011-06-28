/*
 * Calculation.h
 *
 *  Created on: 27.06.2011
 *      Author: matthias
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "OpenNi.h"

class Calculation
{
public:
   static bool pointonLine(OpenNiPoint lineP, OpenNiPoint lineDir, double lineWidth, OpenNiPoint point);
   static double getWinkel(OpenNiPoint pos1, OpenNiPoint gelenk, OpenNiPoint pos2, bool rad = false);
   static double getWinkel(OpenNiPoint vector1, OpenNiPoint vector2, bool rad = false);
};

#endif /* CALCULATION_H_ */
