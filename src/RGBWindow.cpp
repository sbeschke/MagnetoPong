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
      CL_Draw::circle(graphicContext, CL_Pointf(hand.x , hand.y), 5, CL_Colorf::red);

      OpenNiPoint finger = kinect->getPlayerPart(nr, P_LHAND, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_HEAD, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_LELBOW, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_RELBOW, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_RHIP, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_RKNEE, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_RFOOT, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_TORSO, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_WAIST, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);

      finger = kinect->getPlayerPart(nr, P_RSHOULDER, true);
      CL_Draw::circle(graphicContext, CL_Pointf(finger.x , finger.y), 5, CL_Colorf::green);
   }
}
//---------------------------------------------------------------------------
