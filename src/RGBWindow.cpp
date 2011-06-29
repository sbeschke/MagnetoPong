/*
 * RGBWindow.cpp
 *
 *  Created on: 29.06.2011
 *      Author: matthias
 */

#include "RGBWindow.h"

#include "OpenNi.h"


RGBWindow::RGBWindow(OpenNi *kinect)
:VideoWindow(kinect)
{

}

RGBWindow::~RGBWindow()
{
}
//---------------------------------------------------------------------------

void RGBWindow::refreshPicture()
{
   unsigned short* pixels = kinect->getRGBPicture();

 //  cout << pixels[640*480*3-2] << " | " << pixels[640*480*3-1]  << endl;
   unsigned short array[640*480*3];
   for(int i=0; i < 640*480*3; i++)
   {
      array[i] = pixels[640*480*3-i];
   }

   CL_PixelBuffer buffer(640, 480, cl_bgr8, pixels);
   graphicContext.draw_pixels(0, 0, buffer, CL_Rect(0, 0, 640, 480));
}
//---------------------------------------------------------------------------
