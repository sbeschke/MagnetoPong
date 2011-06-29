/*
 * RGBWindow.h
 *
 *  Created on: 29.06.2011
 *      Author: matthias
 */

#ifndef RGBWINDOW_H_
#define RGBWINDOW_H_

#include "VideoWindow.h"

class RGBWindow : public VideoWindow
{
public:
   RGBWindow(OpenNi *kinect);
   virtual ~RGBWindow();

private:
   void refreshPicture();
};

#endif /* RGBWINDOW_H_ */
