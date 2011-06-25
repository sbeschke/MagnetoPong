/*
 * BoostBaar.cpp
 *
 *  Created on: 25.06.2011
 *      Author: matthas
 */

#include "BoostBar.h"
#include "Application.h"

BoostBar::BoostBar(int nr)
{
   playerNr = nr;
   max_val  = 10;
   akt_val  = 10;
}

BoostBar::~BoostBar()
{
}

void BoostBar::setPlayer(int nr)
{
   playerNr = nr;
}

void BoostBar::setMaxValue(double val)
{
   max_val = val;
}

void BoostBar::setValue(double val)
{
   akt_val = val;
}

void BoostBar::draw()
{
   double x1;
   double x2;
   double x3;
   double y1 = Application::y_res - 50;
   double y2 = y1 - BB_HEIGHT;

   double pos = BB_WIDTH * (akt_val/max_val);

   if(playerNr == Application::PLAYER_LEFT)
   {
      x1 = 50;
      x2 = x1 + BB_WIDTH;
      x3 = x1 + (BB_WIDTH*pos);
   }
   else
   {
      x1 = Application::x_res - 50;
      x2 = x1 - BB_WIDTH;
      x3 = x1 - (BB_WIDTH*pos);
   }

   CL_Draw::box(Application::myself->getGC(), x1, y1, x2, y2, CL_Colorf::black);
   CL_Draw::box(Application::myself->getGC(), x1, y1, x3, y2, playerColors[playerNr]);
}
