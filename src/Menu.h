/*
 * Menu.h
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#ifndef MENU_H_
#define MENU_H_

#include <vector>
using namespace std;

class MenuButton;
class Player;


class Menu
{
public:
   Menu();
   virtual ~Menu();

   void resetButtons();

   int checkPlayer(Player* pl);

   static const int MENUROOT = 0;
   static const int MENUDIF  = 1;
   static const int MENUOPT  = 2;
   static const int MENURES  = 3;

   void setMenu(int menuNr);
   void draw();

   static const int NON    =  0;
   static const int PONG   =  1;
   static const int SQUASH =  2;
   static const int OPTION =  3;
   static const int DIF1   = 21;
   static const int DIF2   = 22;
   static const int DIF3   = 23;
   static const int DIF4   = 24;
   static const int SOUND  = 31;
   static const int RES    = 32;
   static const int CHRES  = 321;
   static const int SAVERES= 322;

   static const int BACK   = 91;
   static const int END    = 99;

   void setRes(int x, int y);

   int getXres();
   int getYres();

   void incRes();
   void decRes();

private:
   vector<MenuButton* > buttonListRoot;
   vector<MenuButton* > buttonListDif;
   vector<MenuButton* > buttonListOpt;
   vector<MenuButton* > buttonListRes;

   int menuNr;

   int res_ctr;


};

#endif /* MENU_H_ */
