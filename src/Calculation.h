/*
 * Calculation.h
 *
 *  Created on: 27.06.2011
 *      Author: matthias
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_

#include "OpenNi.h"

#define GRAD_TO_2PI 0.017453292519943295769236907684886
#define PI_TO_GRAD  57.295779513082320876798154814105

class Calculation
{
public:
   static bool pointonLine(OpenNiPoint lineP, OpenNiPoint lineDir, double lineWidth, OpenNiPoint point);
   static double getWinkel(OpenNiPoint pos1, OpenNiPoint gelenk, OpenNiPoint pos2, bool rad = false);
   static double getWinkel(OpenNiPoint vector1, OpenNiPoint vector2, bool rad = false);
   static int hsl_to_rgb(double h, double s, double l);
   static bool isEqual(double v1, double v2, double tol);
};

#endif /* CALCULATION_H_ */
