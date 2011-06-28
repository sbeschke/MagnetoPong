/*
 * VideoWindow.h
 *
 *  Created on: 28.06.2011
 *      Author: matthas
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

   void on_window_close()
   {
      window_open = false;
   }

private:
   CL_GraphicContext graphicContext;
   OpenNi* kinect;
   CL_DisplayWindow* window;

   bool window_open;
   float timepast;
};

#endif /* VIDEOWINDOW_H_ */
