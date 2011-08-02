/*
 * RGBWindow.cpp
 *
 *  Created on: 29.06.2011
 *      Author: matthias
 */

#include "RGBWindow.h"

#include "OpenNi.h"
#include "Application.h"


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

   if(pixels == NULL) return;

   CL_PixelBuffer buffer(640, 480, cl_bgr8, pixels);

   graphicContext.draw_pixels(0, 0, buffer, CL_Rect(0, 0, 640, 480));

   if(Application::get()->players[Application::PLAYER_RIGHT] != 0)
   {
      int nr = Application::get()->players[Application::PLAYER_RIGHT]->getNumber();
      OpenNiPoint hand = kinect->getPlayerPart(nr, P_RHAND, true);

      cout << "bla1" << endl;
      CL_Draw::circle(graphicContext, CL_Pointf(123,302), 2, CL_Colorf::gray);
      cout << "bla2" << endl;
      CL_Draw::circle(graphicContext, CL_Pointf(400,200), 5, CL_Colorf::red);
      cout << "bla3" << endl;
   }


}
//---------------------------------------------------------------------------
