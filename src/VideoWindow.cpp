/*
 * VideoWindow.cpp
 *
 *  Created on: 28.06.2011
 *      Author: matthas
 */

#include "VideoWindow.h"

#include "OpenNi.h"

#include <iostream>

VideoWindow::VideoWindow(OpenNi *kinect)
{
   cout << "videoWindow" << endl;
   this->kinect = kinect;
   CL_DisplayWindowDescription window_desc;

   window_desc.set_size(CL_Size(640, 480), true);
   window_desc.set_title("MagnetoPong!!!11einself - Video");
   window_desc.set_visible(true);
   window_desc.set_position(CL_Rect(1,1,CL_Size(640, 480)),true);

   window = new CL_DisplayWindow(window_desc);

   CL_Slot slot_quit = window->sig_window_close().connect(this, &VideoWindow::on_window_close);
   graphicContext = window->get_gc();
   graphicContext.clear(CL_Colorf::white); //Fenster mit Weiß löschen
   window->show();
 //  window->bring_to_front();
   window->flip();
   window->set_visible(true, false);
   window_open = true;
}

VideoWindow::~VideoWindow()
{
   // TODO Auto-generated destructor stub
}


void VideoWindow::refresh()
{
   unsigned short* pixels = kinect->getRGBPicture();

   CL_PixelBuffer buffer(640, 480, cl_bgr8, pixels);
   graphicContext.draw_pixels(0,0,buffer,CL_Rect(0,0,640,480));

   window->flip();
}
