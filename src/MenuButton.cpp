/*
 * MenuButton.cpp
 *
 *  Created on: 29.06.2011
 *      Author: matthias
 */

#include "MenuButton.h"

MenuButton::MenuButton(int id, CL_FontDescription font)
{
   buttonID = id;
   gc = Application::get()->getGC();
   fontSystem = CL_Font_System(gc, font);
   pressed = false;
}

MenuButton::MenuButton(int id, double x, double y, double width, double height,
                       double roundness, CL_FontDescription font)
{
   buttonID = id;
   gc = Application::get()->getGC();
   fontSystem = CL_Font_System(gc, font);
   this->x = x;
   this->y = y;
   this->width  = width;
   this->height = height;
   this->roundness = roundness;
   pressed = false;
}

MenuButton::~MenuButton()
{
}
//---------------------------------------------------------------------------

void MenuButton::draw()
{
   CL_Colorf color;
   if(pressed) color = colorBackP;
   else        color = colorBackN;

   CL_Draw::circle(gc, CL_Pointf(x+roundness,       y+roundness),        roundness, color);
   CL_Draw::circle(gc, CL_Pointf(x+roundness,       y+height-roundness), roundness, color);
   CL_Draw::circle(gc, CL_Pointf(x+width-roundness, y+roundness),        roundness, color);
   CL_Draw::circle(gc, CL_Pointf(x+width-roundness, y+height-roundness), roundness, color);

   CL_Draw::fill(gc, x+roundness, y, x+width-roundness, y+height, color);
   CL_Draw::fill(gc, x, y+roundness, x+width, y+height-roundness, color);

   CL_Size size = fontSystem.get_text_size(gc, text);

   fontSystem.draw_text(gc,(int)(x+width/2) - (size.width/2), (int)(y+height/2) + (size.height*0.6/2),
                        text, colorFont);
}
//---------------------------------------------------------------------------

void MenuButton::setPosition(double x, double y)
{
   this->x = x;
   this->y = y;
}
//---------------------------------------------------------------------------

void MenuButton::setSize(double width, double height)
{
   this->width  = abs(width);
   this->height = abs(height);
}
//---------------------------------------------------------------------------

void MenuButton::setText(TGString str)
{
   text = str;
}
//---------------------------------------------------------------------------

void MenuButton::setColor(CL_Colorf colorBackN, CL_Colorf colorBackP, CL_Colorf colorFont)
{
   this->colorBackP = colorBackP;
   this->colorBackN = colorBackN;
   this->colorFont = colorFont;
}
//---------------------------------------------------------------------------

bool MenuButton::getPointOnButton(double px, double py)
{
   return ((px >= x) && (px <= x+width) && (py >= y) && (py <= y+height));
}
//---------------------------------------------------------------------------
