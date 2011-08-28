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

int resulutions[][2] = {{640,480},
                        {800,600},
                        {960,600},
                        {1024,768},
                        {1280,720},
                        {1280,768},
                        {1280,800},
                        {1280,1024},
                        {1360,768},
                        {1366,768},
                        {1400,1050},
                        {1440,900},
                        {1680,1050},
                        {1920,1080},
                        {1920,1200}, //15
                        {800,600}};//wenn benutzer in xml eine unbekannte auflösung einstellt
#define ANZRES 15
int anz_res = ANZRES;

Menu::Menu()
{
   menuNr = MENUROOT;

   setRes(Application::x_res, Application::y_res);

   resetButtons();
}

Menu::~Menu()
{
   buttonListDif.clear();
   buttonListRoot.clear();
   buttonListOpt.clear();
   buttonListRes.clear();
}
//---------------------------------------------------------------------------

void Menu::resetButtons()
{
   buttonListDif.clear();
   buttonListRoot.clear();
   buttonListOpt.clear();
   buttonListRes.clear();

   double fontsize = Application::x_res / 24;
   CL_FontDescription font_desc;
   font_desc.set_typeface_name("Verdana");
   font_desc.set_height(fontsize);

   double w = fontsize*9;
   double x = Application::x_res/2 - w/2;
   double y = 100;
   double h = fontsize+fontsize/2;
   double d = 15;

   MenuButton* b;
   b = new MenuButton(PONG, x, y, w, h, 20, font_desc);
   b->setText("start MagnetoPong");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRoot.push_back(b);

   b = new MenuButton(SQUASH, x, y+= h+d, w, h, 20, font_desc);
   b->setText("start MagnetoSquash");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRoot.push_back(b);

   b = new MenuButton(FLIGHT, x, y+= h+d, w, h, 20, font_desc);
   b->setText("start MagnetoFlight");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRoot.push_back(b);

   b = new MenuButton(OPTION, x, y+= h+d, w, h, 20, font_desc);
   b->setText("Options");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRoot.push_back(b);

   b = new MenuButton(END, x, y+= h+d*2, w, h, 20, font_desc);
   b->setText("Quit");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRoot.push_back(b);

   //--------------------------------------------------
   y = 100;
   b = new MenuButton(DIF1, x, y, w, h, 20, font_desc);
   b->setText("Easy");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListDif.push_back(b);

   b = new MenuButton(DIF2, x, y+= h+d, w, h, 20, font_desc);
   b->setText("Normal");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListDif.push_back(b);

   b = new MenuButton(DIF3, x, y+= h+d, w, h, 20, font_desc);
   b->setText("Hard");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListDif.push_back(b);

   b = new MenuButton(DIF4, x, y+= h+d, w, h, 20, font_desc);
   b->setText("Extrem");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListDif.push_back(b);

   b = new MenuButton(BACK, x, y+= h+d*2, w, h, 20, font_desc);
   b->setText("Back");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListDif.push_back(b);

   //--------------------------------------------------
   y = 100;
   b = new MenuButton(SOUND, x, y, w, h, 20, font_desc);
   b->setText("Sound OFF");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListOpt.push_back(b);

   b = new MenuButton(RES, x, y+= h+d, w, h, 20, font_desc);
   b->setText("screen resolution");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListOpt.push_back(b);

   b = new MenuButton(BACK, x, y+= h+d*2, w, h, 20, font_desc);
   b->setText("Back");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListOpt.push_back(b);

   //--------------------------------------------------
   y = 100;
   b = new MenuButton(CHRES, x, y, w, h, 20, font_desc);
   b->setText(TGString(resulutions[res_ctr][0]) + " x " + resulutions[res_ctr][1]);
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRes.push_back(b);

   b = new MenuButton(SAVERES, x, y+= h+d, w, h, 20, font_desc);
   b->setText("Save");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRes.push_back(b);

   b = new MenuButton(BACK, x, y+= h+d*2, w, h, 20, font_desc);
   b->setText("Back");
   b->setColor(CL_Colorf::red, CL_Colorf::blue, CL_Colorf::green);
   buttonListRes.push_back(b);
}
//---------------------------------------------------------------------------

int Menu::checkPlayer(Player* pl)
{
   double x = pl->getBat()->getX();
   double y = pl->getBat()->getY();
   bool klick = pl->getKlick();
   MenuButton* b;
   vector<MenuButton* >* list;

   switch(menuNr)
   {
   case MENUROOT: list = &buttonListRoot; break;
   case MENUDIF:  list = &buttonListDif;  break;
   case MENUOPT:  list = &buttonListOpt;  break;
   case MENURES:  list = &buttonListRes; break;
   default: list = &buttonListRoot; break;
   }

   for(int i=0; i < list->size(); i++)
   {
      b = list->at(i);

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

void Menu::setMenu(int menuNr)
{
   this->menuNr = menuNr;
}
//---------------------------------------------------------------------------

void Menu::draw()
{
   vector<MenuButton* >* list;
   switch(menuNr)
   {
   case MENUROOT: list = &buttonListRoot; break;
   case MENUDIF:  list = &buttonListDif;  break;
   case MENUOPT:
      {
         list = &buttonListOpt;
         for(int i=0; i < list->size(); i++)
         {
            if(list->at(i)->getID() == SOUND)
            {
               if(Application::get()->soundPlayer->getActive())
               {
                  list->at(i)->setText("Sound OFF");
               }
               else
               {
                  list->at(i)->setText("Sound ON");
               }
               break;
            }
         }
      }
      break;
   case MENURES:
         list = &buttonListRes;
         for(int i=0; i < list->size(); i++)
         {
            if(list->at(i)->getID() == CHRES)
            {
               list->at(i)->setText(TGString(resulutions[res_ctr][0]) + " x " + resulutions[res_ctr][1]);
            }
         }
      break;
   default:      list = &buttonListRoot; break;
   }

   for(int i=0; i < list->size(); i++)
   {
      list->at(i)->draw();
   }

   double fontsize = Application::x_res / 50;

   CL_FontDescription font_desc;
   font_desc.set_typeface_name("Verdana");
   font_desc.set_height(fontsize);
   CL_Font_System fontSystem = CL_Font_System(Application::get()->getGC(), font_desc);

   TGString text = "The blue player is on the right side.\n"
                   "You control your bat with the right hand\n"
                   "and the field-energy with the angle of your\n"
                   "left elbow.";

   CL_Size size = fontSystem.get_text_size(Application::get()->getGC(), text);

   fontSystem.draw_text(Application::get()->getGC(), Application::x_res-size.width-30, 100, text, CL_Colorf::blue);

   text = "The orange player is on the left side.\n"
          "You control your bat with the left hand\n"
          "and the field-energy with the angle of your\n"
          "right elbow.";

   size = fontSystem.get_text_size(Application::get()->getGC(), text);
   fontSystem.draw_text(Application::get()->getGC(), 30, 100, text, CL_Colorf::orange);

   text = "To klick change your field to red.";
   size = fontSystem.get_text_size(Application::get()->getGC(), text);
   fontSystem.draw_text(Application::get()->getGC(), Application::x_res/2 - size.width/2, 50, text, CL_Colorf::black);

}
//---------------------------------------------------------------------------

int Menu::getXres()
{
   return resulutions[res_ctr][0];
}
//---------------------------------------------------------------------------

int Menu::getYres()
{
   return resulutions[res_ctr][1];
}
//---------------------------------------------------------------------------

void Menu::setRes(int x, int y)
{
   bool found = false;
   for(int i=0; i < anz_res; i++)
   {
      if(resulutions[i][0] == x && resulutions[i][1] == y)
      {
         res_ctr = i;
         i = anz_res;
         found = true;
      }
   }

   if(!found)
   {
      resulutions[ANZRES][0] = x;
      resulutions[ANZRES][1] = y;
      anz_res = ANZRES+1;
      res_ctr = anz_res-1;
   }
}
//---------------------------------------------------------------------------

void Menu::incRes()
{
   res_ctr++;
   if(res_ctr >= anz_res) res_ctr = 0;
}
//---------------------------------------------------------------------------

void Menu::decRes()
{
   res_ctr--;
   if(res_ctr < 0) res_ctr = anz_res-1;
}
//---------------------------------------------------------------------------
