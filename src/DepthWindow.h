/*
 * DepthWindow.h
 *
 *  Created on: 28.06.2011
 *      Author: matthas
 */

#ifndef DEPTHWINDOW_H_
#define DEPTHWINDOW_H_

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
class OpenNi;

class DepthWindow
{
public:
   DepthWindow(OpenNi *kinect);
   virtual ~DepthWindow();

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

#endif /* DEPTHWINDOW_H_ */
