/*
 * DepthWindow.cpp
 *
 *  Created on: 28.06.2011
 *      Author: matthias
 */

#include "DepthWindow.h"

#include "Calculation.h"
#include "OpenNi.h"

DepthWindow::DepthWindow(OpenNi *kinect, double min, double max, double details,bool viewEndles)
:VideoWindow(kinect)
{
   this->details = details;
   setPosition(648,1);
   this->min = min;
   this->max = max;
   this->viewEndles = viewEndles;
   show_video = false;
}

DepthWindow::~DepthWindow()
{
}
//---------------------------------------------------------------------------

void DepthWindow::refreshPicture()
{
   unsigned short* pixels = kinect->getDepthPicture();
   double h;
   double lh=0;
   double dh;
   double l;
   double val;

   unsigned char array[640*480*3];
   int ptr=0;
   int rgb;

   for(int i=0; i < 640*480; i++)
   {
      val = (double)pixels[i]*2.0;
      if(val > min)
      {
         h = ((val-min)/max)*360.0;

         if(viewEndles) while(h > 360) h -= 360.0;

         l = 0.5;

         dh = lh - h;

         if(dh < details && dh > -details)
         {
           // l -= (dh/(details)) * 0.4;
            l -= 0.3;
         }
         else
         {
            lh = h;
         }

         rgb = Calculation::hsl_to_rgb(h, 0.8, l);
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
//---------------------------------------------------------------------------
