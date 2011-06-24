/*
 * OpenNi.cpp
 *
 *  Created on: 24.06.2011
 *      Author: Matthias
 */

#include "OpenNi.h"

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>
#include "Application.h"

#include "TGString.h"


//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------

#define RECORD_FILE     "../../../Data/Recording.oni"
#define SAMPLE_XML_PATH "../../../Data/Sample-User.xml"

#define POSE_TO_USE "Psi"

#define CHECK_RC(nRetVal, what) printf("%s : %s\n", what, xnGetStatusString(nRetVal));

xn::Context g_Context;
xn::DepthGenerator g_DepthGenerator;
xn::UserGenerator  g_UserGenerator;

XnCallbackHandle h;
XnCallbackHandle hCalib;
XnCallbackHandle hPose;

void XN_CALLBACK_TYPE NewUser(xn::UserGenerator& generator, XnUserID user, void* pCookie)
{
   printf("New user identified: %d\n", user);
   g_UserGenerator.GetPoseDetectionCap().StartPoseDetection("Psi", user);
}
//---------------------------------------------------------------------------

void XN_CALLBACK_TYPE LostUser(xn::UserGenerator& generator, XnUserID user, void* pCookie)
{
   printf("User %d lost\n", user);
}
//---------------------------------------------------------------------------

void XN_CALLBACK_TYPE CalibrationStart(xn::SkeletonCapability& skeleton, XnUserID user, void* pCookie)
{
   printf("Calibration start for user %d\n", user);
}
//---------------------------------------------------------------------------

void XN_CALLBACK_TYPE CalibrationEnd(xn::SkeletonCapability& skeleton, XnUserID user, XnBool bSuccess, void* pCookie)
{
   printf("Calibration complete for user %d: %s\n", user, bSuccess?"Success":"Failure");
   if (bSuccess)
   {
      skeleton.StartTracking(user);
   }
   else
   {
      g_UserGenerator.GetPoseDetectionCap().StartPoseDetection("Psi", user);
   }
}
//---------------------------------------------------------------------------

void XN_CALLBACK_TYPE PoseDetected(xn::PoseDetectionCapability& poseDetection, const XnChar* strPose, XnUserID nid, void* pCookie)
{
   printf("Pose '%s' detected for user %d\n", strPose, nid);
   g_UserGenerator.GetSkeletonCap().RequestCalibration(nid, FALSE);
   g_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nid);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void OpenNiPlayer::changeForDisplay()
{
   for(int i=0; i < P_SIZE; i++)
   {
      pointList.at(i)->x = pointList.at(i)->x * 0.5 + Application::x_res/2;
      pointList.at(i)->y = pointList.at(i)->y * 0.5 + Application::y_res/2;
   }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

OpenNi::OpenNi()
{
   init_ok = false;
   printf("init\n");
   XnStatus rc = XN_STATUS_OK;
   xn::EnumerationErrors errors;

   rc = g_Context.Init();
   CHECK_RC(rc, "init");

   rc = g_DepthGenerator.Create(g_Context);

   rc = g_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
   CHECK_RC(rc, "Find depth generator");
   if(rc != XN_STATUS_OK) return;
   rc = g_Context.FindExistingNode(XN_NODE_TYPE_USER, g_UserGenerator);
   CHECK_RC(rc, "Find user generator");

   if(rc != XN_STATUS_OK)
   {
      rc = g_UserGenerator.Create(g_Context);
      CHECK_RC(rc, "create User generator");
   }

   rc = g_UserGenerator.RegisterUserCallbacks(NewUser, LostUser, NULL, h);
   CHECK_RC(rc, "create Depth");
   rc = g_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
   CHECK_RC(rc, "create Depth");

   rc = g_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(&CalibrationStart, &CalibrationEnd, NULL, hCalib);
   CHECK_RC(rc, "create Depth");
   rc = g_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(&PoseDetected, NULL, NULL, hPose);
   CHECK_RC(rc, "create Depth");

   rc = g_Context.StartGeneratingAll();
   CHECK_RC(rc, "StartGenerating");

   init_ok = true;
   printf("init E\n");
}
//---------------------------------------------------------------------------

OpenNi::~OpenNi()
{
   g_Context.Shutdown();
}
//---------------------------------------------------------------------------

void OpenNi::update()
{
   if(init_ok) g_Context.WaitAndUpdateAll();
}
//---------------------------------------------------------------------------

int OpenNi::getAnzPlayer()
{
   if(init_ok)return g_UserGenerator.GetNumberOfUsers();
   else return 0;
}
//---------------------------------------------------------------------------

OpenNiPlayer OpenNi::getPlayer(int nr)
{
   XnUserID aUsers[15];
   XnUInt16 nUsers = 15;

   OpenNiPlayer p;
   if(!init_ok) return p;

   g_UserGenerator.GetUsers(aUsers, nUsers);
   if(g_UserGenerator.GetSkeletonCap().IsTracking(nr))
   {
      try
      {
         for(int i=0; i < P_SIZE; i++)
         {
            *(p.pointList.at(i)) = getPlayerPart(nr, i);
         }
         p.calibrated = true;
      }
      catch(...){}
   }
   return p;
}
//---------------------------------------------------------------------------

OpenNiPoint OpenNi::getPlayerPart(int nr, int part)
{
   OpenNiPoint p;
   if(!init_ok) return p;

   if(g_UserGenerator.GetSkeletonCap().IsTracking(nr))
   {
      XnSkeletonJointPosition pos;
      xn::SkeletonCapability s = g_UserGenerator.GetSkeletonCap();

      switch(part)
      {
      case P_HEAD:      s.GetSkeletonJointPosition(nr, XN_SKEL_HEAD, pos); break;
      case P_NECK:      s.GetSkeletonJointPosition(nr, XN_SKEL_NECK, pos); break;
      case P_TORSO:     s.GetSkeletonJointPosition(nr, XN_SKEL_TORSO , pos); break;
      case P_WAIST:     s.GetSkeletonJointPosition(nr, XN_SKEL_WAIST, pos); break;
      case P_LCOLLAR:   s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_COLLAR , pos); break;
      case P_LSHOULDER: s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_SHOULDER , pos); break;
      case P_LELBOW:    s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_ELBOW, pos); break;
      case P_LWRIST:    s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_WRIST , pos); break;
      case P_LHAND:     s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_HAND , pos); break;
      case P_LFINGER:   s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_FINGERTIP , pos); break;
      case P_RCOLLAR:   s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_COLLAR, pos); break;
      case P_RSHOULDER: s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_SHOULDER, pos); break;
      case P_RELBOW:    s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_ELBOW, pos); break;
      case P_RWRIST:    s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_WRIST , pos); break;
      case P_RHAND:     s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_HAND, pos); break;
      case P_RFINGER:   s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_FINGERTIP, pos); break;
      case P_LHIP:      s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_HIP,    pos); break;
      case P_LKNEE:     s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_KNEE,   pos); break;
      case P_LANKLE:    s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_ANKLE,  pos); break;
      case P_LFOOT:     s.GetSkeletonJointPosition(nr, XN_SKEL_LEFT_FOOT,   pos); break;
      case P_RHIP:      s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_HIP,   pos); break;
      case P_RKNEE:     s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_KNEE,  pos); break;
      case P_RANKLE:    s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_ANKLE, pos); break;
      case P_RFOOT:     s.GetSkeletonJointPosition(nr, XN_SKEL_RIGHT_FOOT,  pos); break;
      }
      p.x = (pos.position.X * -1.0);//-0.5) + Application::x_res/2;
      p.y = (pos.position.Y * -1.0);//-0.5) + Application::y_res/2;
      p.z = abs(pos.position.Z);

   }
   return p;
}
//---------------------------------------------------------------------------

OpenNiPoint OpenNi::getPlayerPart(int nr, int part1, int part2)
{
   OpenNiPoint p1 = getPlayerPart(nr, part1);
   OpenNiPoint p2 = getPlayerPart(nr, part2);

   p1.x = p1.x - p2.x;
   p1.y = p1.y - p2.y;
   p1.z = p2.z - p1.z;

   return p1;
}
//---------------------------------------------------------------------------

double OpenNi::getWinkel(int nr, int leftArm)
{
   OpenNiPoint p1, p2;
   if(leftArm)
   {
      p1 = Application::myself->kinect.getPlayerPart(nr, P_RELBOW, P_RHAND);
      p2 = Application::myself->kinect.getPlayerPart(nr, P_RELBOW, P_RSHOULDER);
   }
   else
   {
      p1 = Application::myself->kinect.getPlayerPart(nr, P_LELBOW, P_LHAND);
      p2 = Application::myself->kinect.getPlayerPart(nr, P_LELBOW, P_LSHOULDER);
   }

   return atan((p1*p2)/(p1.length()*p2.length())) * 57.295779513082320876798154814105;
}
//---------------------------------------------------------------------------

void OpenNi::drawPlayer(int nr)
{
   if(!init_ok) return;
   CL_FontDescription font_desc;
   font_desc.set_typeface_name("tahoma");
   font_desc.set_height(30);
   CL_Font_System font(Application::myself->gc, font_desc);

   OpenNiPlayer p = getPlayer(nr);
   if(p.calibrated)
   {
      p.changeForDisplay();
      for(int i=0; i < P_SIZE; i++)
      {
         if((p.pointList.at(i)->x != 0) && (p.pointList.at(i)->y != 0)) CL_Draw::circle(Application::myself->getGC(), CL_Pointf(p.pointList.at(i)->x, p.pointList.at(i)->y), 5, CL_Colorf((float)p.pointList.at(i)->z/2500.0,(float)0.0,(float)1.0,(float)1.0));
      }

      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_HEAD)->x, p.pointList.at(P_HEAD)->y, p.pointList.at(P_NECK)->x, p.pointList.at(P_NECK)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_TORSO)->x, p.pointList.at(P_TORSO)->y, p.pointList.at(P_NECK)->x, p.pointList.at(P_NECK)->y, CL_Colorf::white);

      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LSHOULDER)->x, p.pointList.at(P_LSHOULDER)->y, p.pointList.at(P_RSHOULDER)->x, p.pointList.at(P_RSHOULDER)->y, CL_Colorf::white);


      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LELBOW)->x, p.pointList.at(P_LELBOW)->y, p.pointList.at(P_LHAND)->x, p.pointList.at(P_LHAND)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LSHOULDER)->x, p.pointList.at(P_LSHOULDER)->y, p.pointList.at(P_LELBOW)->x, p.pointList.at(P_LELBOW)->y, CL_Colorf::white);


      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_RELBOW)->x, p.pointList.at(P_RELBOW)->y, p.pointList.at(P_RHAND)->x, p.pointList.at(P_RHAND)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_RSHOULDER)->x, p.pointList.at(P_RSHOULDER)->y, p.pointList.at(P_RELBOW)->x, p.pointList.at(P_RELBOW)->y, CL_Colorf::white);

      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LHIP)->x, p.pointList.at(P_LHIP)->y, p.pointList.at(P_TORSO)->x, p.pointList.at(P_TORSO)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_TORSO)->x, p.pointList.at(P_TORSO)->y, p.pointList.at(P_RHIP)->x, p.pointList.at(P_RHIP)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LHIP)->x, p.pointList.at(P_LHIP)->y, p.pointList.at(P_RHIP)->x, p.pointList.at(P_RHIP)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_LHIP)->x, p.pointList.at(P_LHIP)->y, p.pointList.at(P_LKNEE)->x, p.pointList.at(P_LKNEE)->y, CL_Colorf::white);
      CL_Draw::line(Application::myself->getGC(), p.pointList.at(P_RHIP)->x, p.pointList.at(P_RHIP)->y, p.pointList.at(P_RKNEE)->x, p.pointList.at(P_RKNEE)->y, CL_Colorf::white);

      TGString s = TGString("Winkel L: ") + getWinkel(nr, true) + " R Hand:(" + p.pointList.at(P_LHAND)->x + "|" + p.pointList.at(P_LHAND)->y + "|" + p.pointList.at(P_LHAND)->z +")" ;
      font.draw_text(Application::myself->gc, 10, 20*nr, s.c_str());

   }
}
