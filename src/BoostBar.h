/*
 * BoostBaar.h
 *
 *  Created on: 25.06.2011
 *      Author: matthas
 */

#ifndef BOOSTBAR_H_
#define BOOSTBAR_H_

#define BB_HEIGHT 40
#define BB_WIDTH 100
class BoostBar
{
public:
   BoostBar(int nr);
   virtual ~BoostBar();

   void setPlayer(int nr);
   void setMaxValue(double val);
   void setValue(double val);

   void draw();

private:

   int playerNr;

   double max_val;
   double akt_val;

};

#endif /* BOOSTBAAR_H_ */
