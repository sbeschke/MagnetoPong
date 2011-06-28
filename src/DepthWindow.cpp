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
{
   cout << "depthWindow" << endl;
   this->kinect = kinect;
   CL_DisplayWindowDescription window_desc;

   window_desc.set_size(CL_Size(640, 480), true);
   window_desc.set_title("MagnetoPong!!!11einself - Depth");
   window_desc.set_visible(true);
   window_desc.set_position(CL_Rect(641,1,CL_Size(640, 480)),true);

   window = new CL_DisplayWindow(window_desc);

   CL_Slot slot_quit = window->sig_window_close().connect(this, &DepthWindow::on_window_close);
   graphicContext = window->get_gc();
   graphicContext.clear(CL_Colorf::white); //Fenster mit Weiß löschen
   window->show();
   window->flip();
   window->set_visible(true, false);
   window_open = true;
   timepast = 42; //24fps;
}

DepthWindow::~DepthWindow()
{
   // TODO Auto-generated destructor stub
}

void DepthWindow::refresh(float timediff)
{
   if(!window_open) return;

   timepast += timediff;
   if(timepast > 42) //24fps
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

      window->flip();
      timepast = 0;
   }
}
