/*
 * DepthWindow.cpp
 *
 *  Created on: 28.06.2011
 *      Author: matthias
 */

#include "DepthWindow.h"

#include "Calculation.h"
#include "OpenNi.h"

DepthWindow::DepthWindow(OpenNi *kinect)
:VideoWindow(kinect)
{
   setPosition(642,1);
}

DepthWindow::~DepthWindow()
{
}
//---------------------------------------------------------------------------

void DepthWindow::refreshPicture()
{
   unsigned short* pixels = kinect->getDepthPicture();
   double h;
   double min = 100;
   double max = 4000;
   unsigned char array[640*480*3];
   int ptr=0;
   for(int i=0; i < 640*480; i++)
   {

      if(pixels[i] < min)
      {
         h = 360;
      }
      else
      {
         h = (((double)pixels[i]-min)/max)*360.0;
      }

      int rgb;
      if(h < 360)
      {
        rgb = Calculation::hsl_to_rgb(h,1,0.5);
      }
      else
      {
         rgb = 0;
      }

      array[ptr]   = rgb >> 16;
      array[ptr+1] = rgb >> 8;
      array[ptr+2] = rgb;

      ptr+=3;
   }

   CL_PixelBuffer buffer(640, 480, cl_bgr8, array);
   graphicContext.draw_pixels(0,0,buffer,CL_Rect(0,0,640,480));
}
