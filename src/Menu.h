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

//typedef vector<MenuButton* >* buttonList;

class Menu
{
public:
   Menu();
   virtual ~Menu();

   int checkPlayer(Player* pl);

   static const int MENUROOT = 0;
   static const int MENUDIF  = 1;
   static const int MENUOPT  = 2;

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
   static const int BACK   = 91;
   static const int END    = 99;

private:
   vector<MenuButton* > buttonListRoot;
   vector<MenuButton* > buttonListDif;
   vector<MenuButton* > buttonListOpt;

   int menuNr;

};

#endif /* MENU_H_ */
