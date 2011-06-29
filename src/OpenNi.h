/*
 * OpenNi.h
 *
 *  Created on: 24.06.2011
 *      Author: Matthias
 */

#ifndef OPENNI_H_
#define OPENNI_H_


#include <math.h>
#include "TGString.h"
#include <iostream>

#include <vector>
using namespace std;

#define P_HEAD       0
#define P_NECK       1
#define P_TORSO      2
#define P_WAIST      3
#define P_LCOLLAR    4
#define P_LSHOULDER  5
#define P_LELBOW     6
#define P_LWRIST     7
#define P_LHAND      8
#define P_LFINGER    9
#define P_RCOLLAR   10
#define P_RSHOULDER 11
#define P_RELBOW    12
#define P_RWRIST    13
#define P_RHAND     14
#define P_RFINGER   15
#define P_LHIP      16
#define P_LKNEE     17
#define P_LANKLE    18
#define P_LFOOT     19
#define P_RHIP      20
#define P_RKNEE     21
#define P_RANKLE    22
#define P_RFOOT     23
#define P_SIZE      24

class OpenNiPoint
{
public:
   OpenNiPoint()
   {
      x = 0;
      y = 0;
      z = 0;
   };

   OpenNiPoint(double x, double y, double z)
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }

   double operator*(OpenNiPoint& p)
   {
      return x*p.x + y*p.y + z*p.z;
   }

   OpenNiPoint operator-(OpenNiPoint& p)
{
      OpenNiPoint np = *this;
      np.x -= p.x;
      np.y -= p.y;
      np.z = p.z  - np.z;
      return np;
   }

   OpenNiPoint operator+(OpenNiPoint& p)
   {
      OpenNiPoint np = *this;
      np.x += p.x;
      np.y += p.y;
      np.z += p.z;
      return np;
   }

   double length()
   {
      return sqrt(x*x + y*y + z*z);
   }

   TGString toString()
   {
      return TGString("(") + x + "|" + y + "|" + z + ")";
   }

   double x;
   double y;
   double z;   
};

class OpenNiPlayer
{
public:
   OpenNiPlayer()
   {
      calibrated = false;

      for(int i=0; i < P_SIZE; i++)
      {
         pointList.push_back(new OpenNiPoint());
      }
   }
   bool calibrated;

   std::vector<OpenNiPoint* > pointList;

   void changeForDisplay();
};

class OpenNiPlayerCallback
{
public:
	virtual void playerRecognized(int nr) =0;
	virtual void calibrationStart(int nr) =0;
	virtual void calibrationFailed(int nr) =0;
	virtual void playerCalibrated(int nr) =0;
	virtual void playerLost(int nr) =0;
};

class OpenNi
{
public:
   OpenNi();
   virtual ~OpenNi();

   void init();
   void update(float timediff);
   int  getAnzPlayer();
   OpenNiPlayer getPlayer(int nr);
   OpenNiPoint  getPlayerPart(int nr, int part);
   OpenNiPoint  getPlayerPart(int nr, int part1, int part2);
           //pos von Part1 relativ zu Part2

   unsigned short* getRGBPicture();
   unsigned short* getDepthPicture();

   double getWinkelELBOW(int nr, int leftArm);
   double getWinkel(int nr, int pos1, int gelenk, int pos2);

   void drawPlayer(int nr);

   void setPlayerCallback(OpenNiPlayerCallback* callback);

   bool kinectconnected() {return init_ok;};

private:

   bool init_ok;

   unsigned short* pixels;
   unsigned short*  depth;
   OpenNiPlayerCallback* playerCallback;

   float timepast;
};

#endif /* OPENNI_H_ */
