/*
 * HandFinder.cpp
 *
 *  Created on: 02.08.2011
 *      Author: matthias
 */

#include "HandFinder.h"

HandFinder::HandFinder(OpenNi *kinect)
{
   this->kinect = kinect;
}
//---------------------------------------------------------------------------

HandFinder::~HandFinder()
{

}
//---------------------------------------------------------------------------

Hand HandFinder::findHand(bool lefthand, OpenNiPoint palm)
{
   Hand hand;
   unsigned short* depth = kinect->getDepthPicture();
   hand.palm = palm;

   int palmdepth = getPixel(depth, hand.palm.x, hand.palm.y);


   if(lefthand)
   {

   }
   else
   {

   }


   return hand;
}
//---------------------------------------------------------------------------

void HandFinder::findThumb(bool lefthand, unsigned short* depth, int rootdepth)
{
   int rootXptr = 0;
   int rootYptr = 0;

   for(int i = 0; i < 100; i++)
   {

   }
}
//---------------------------------------------------------------------------

unsigned short HandFinder::getPixel(unsigned short* buffer, int x, int y, bool depth, int xres, int yres)
{
   return buffer[y*xres + x];
}
//---------------------------------------------------------------------------
