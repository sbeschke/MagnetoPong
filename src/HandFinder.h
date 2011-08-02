/*
 * HandFinder.h
 *
 *  Created on: 02.08.2011
 *      Author: matthias
 */

#ifndef HANDFINDER_H_
#define HANDFINDER_H_

#include "OpenNi.h"

class Hand
{
public:
      Hand(){};
      ~Hand(){};

      OpenNiPoint palm;
      OpenNiPoint thumb;
      OpenNiPoint finger[4];
};

class HandFinder
{
public:
   HandFinder(OpenNi *kinect);
   virtual ~HandFinder();

   Hand findHand(bool lefthand, OpenNiPoint palm);

private:
   OpenNi *kinect;

   void findThumb(bool lefthand, unsigned short* depth, int rootdepth);
   unsigned short getPixel(unsigned short* buffer, int x, int y, bool depth = true, int xres = 640, int yres = 480);

   unsigned short flaeche[640][480];
};

#endif /* HANDFINDER_H_ */
