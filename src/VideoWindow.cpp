/*
 * VideoWindow.cpp
 *
 *  Created on: 28.06.2011
 *      Author: matthias
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
   window_desc.set_title("MagnetoPong!!!11einself - Video - mouseklick = start/stop");
   window_desc.set_visible(true);
   window_desc.set_position(CL_Rect(1,1,CL_Size(640, 480)),true);

   window = new CL_DisplayWindow(window_desc);

   CL_Slot slot_quit = window->sig_window_close().connect(this, &VideoWindow::on_window_close);
   graphicContext = window->get_gc();
   graphicContext.clear(CL_Colorf::white); //Fenster mit Weiß löschen
   window->show();
   window->flip();
   window->set_visible(true, false);
   window_open = true;
   show_video  = true;
   mouse_down  = false;

   mouse = new CL_InputDevice();
   *mouse = window->get_ic().get_mouse(0);
   timepast = 42; //24fps;
}

VideoWindow::~VideoWindow()
{
   delete window;
}
//---------------------------------------------------------------------------

void VideoWindow::refresh(float timediff)
{
   if(mouse->get_keycode(mouse->string_to_keyid("Mouse Left")))
   {
      if(!mouse_down)
      {
         show_video = !show_video;
         mouse_down = true;
      }
   }
   else
   {
      mouse_down = false;
   }

   if(!window_open || !show_video) return;

   timepast += timediff;
   if(timepast > 42) //24fps
   {
      refreshPicture();
      window->flip();
      timepast = 0;
   }
}
//---------------------------------------------------------------------------

void VideoWindow::setPosition(int x, int y)
{
   window->set_position(x,y);
}
//---------------------------------------------------------------------------

