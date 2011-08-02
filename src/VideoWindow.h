/*
 * VideoWindow.h
 *
 *  Created on: 28.06.2011
 *      Author: matthias
 */

#ifndef VIDEOWINDOW_H_
#define VIDEOWINDOW_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

class OpenNi;

class VideoWindow
{
public:
   VideoWindow(OpenNi *kinect);
   virtual ~VideoWindow();

   void refresh(float timediff);
   void setPosition(int x, int y);

   void on_window_close()
   {
      window_open = false;
   }

protected:
   virtual void refreshPicture()=0;

   OpenNi* kinect;
   CL_GraphicContext graphicContext;
   CL_DisplayWindow window;
   CL_InputDevice* mouse;

   bool window_open;
   bool show_video;

   bool mouse_down;

   float timepast;
};

#endif /* VIDEOWINDOW_H_ */
