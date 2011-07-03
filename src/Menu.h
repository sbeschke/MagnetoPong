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

   int checkPlayer(Player* pl);
   void draw();

   static const int NON    =  0;
   static const int PONG   =  1;
   static const int SQUASH =  2;
   static const int END    = 99;

private:
   vector<MenuButton* > buttonList;

};

#endif /* MENU_H_ */
