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
   DepthWindow(OpenNi *kinect);
   virtual ~DepthWindow();

private:
   void refreshPicture();

};

#endif /* DEPTHWINDOW_H_ */
