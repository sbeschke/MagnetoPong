/*
 * DepthWindow.h
 *
 *  Created on: 28.06.2011
 *      Author: matthias
 */

#ifndef DEPTHWINDOW_H_
#define DEPTHWINDOW_H_

#include "VideoWindow.h"


class DepthWindow : public VideoWindow
{
public:
   DepthWindow(OpenNi *kinect, double min, double max, double details = 0.1, bool viewEndles = true);
   virtual ~DepthWindow();

private:
   void refreshPicture();

   double details;
   double min;
   double max;

   bool viewEndles;

};

#endif /* DEPTHWINDOW_H_ */
