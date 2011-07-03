/*
 * Menu.cpp
 *
 *  Created on: 03.07.2011
 *      Author: matthias
 */

#include "Menu.h"
#include "MenuButton.h"
#include "Player.h"
#include "Bat.h"

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>

Menu::Menu()
{
   CL_FontDescription font_desc;
   font_desc.set_typeface_name("Verdana");
   font_desc.set_height(80);
  // fontSystem = CL_Font_System(Application::get()->getGC(), font);

   double w = 900;
   double x = Application::x_res/2 - w/2;
   double y = 100;
   double h = 120;
   double d = 15;

   MenuButton* b;
   b = new MenuButton(PONG, x, y, w, h, 20, font_desc);
   b->setText("start MagnetoPong");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonList.push_back(b);

   b = new MenuButton(SQUASH, x, y+= h+d, w, h, 20, font_desc);
   b->setText("start MagnetoSquash");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonList.push_back(b);

   b = new MenuButton(END, x, y+= h+d*2, w, h, 20, font_desc);
   b->setText("Quit");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonList.push_back(b);
}

Menu::~Menu()
{
   buttonList.clear();
}
//---------------------------------------------------------------------------

int Menu::checkPlayer(Player* pl)
{
   double x = pl->getBat()->getX();
   double y = pl->getBat()->getY();
   bool klick = pl->getKlick();
   MenuButton* b;

   for(int i=0; i < buttonList.size(); i++)
   {
      b = buttonList.at(i);

      if(b->getPointOnButton(x,y))
      {
         b->setPressed(true);
         if(klick)
         {
            return b->getID();
         }
      }
      else
      {
         b->setPressed(false);
      }
   }
   return 0;
}
//---------------------------------------------------------------------------

void Menu::draw()
{
   for(int i=0; i < buttonList.size(); i++)
   {
      buttonList.at(i)->draw();
   }
   //fontSystem.draw_text(Application::get()->getGC(),
     //                     "to klick , CL_Colorf::black);
}
//---------------------------------------------------------------------------
