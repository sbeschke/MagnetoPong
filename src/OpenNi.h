/*
 * OpenNi.h
 *
 *  Created on: 24.06.2011
 *      Author: Matthias
 */

#ifndef OPENNI_H_
#define OPENNI_H_



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

class Point
{
public:
   Point()
   {
      x = 0;
      y = 0;
      z = 0;
   };
   Point(double x, double y, double z)
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }

   double x;
   double y;
   double z;   
};

class Player
{
public:
   Player()
   {
      calibrated = false;

      for(int i=0; i < P_SIZE; i++)
      {
         pointList.push_back(new Point());
      }
   }
   bool calibrated;

   std::vector<Point* > pointList;
};

class OpenNi
{
public:
   OpenNi();
   virtual ~OpenNi();

   void update();
   int  getAnzPlayer();
   Player getPlayer(int nr);
   Point  getPlayerPart(int nr, int part);

   void drawPlayer(int nr);

private:


};

#endif /* OPENNI_H_ */
