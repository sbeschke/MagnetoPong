/*
 * MenuButton.h
 *
 *  Created on: 29.06.2011
 *      Author: matthias
 */

#ifndef MENUBUTTON_H_
#define MENUBUTTON_H_

#include "TGString.h"
#include "Application.h"

class MenuButton
{
public:
   MenuButton(int id, CL_FontDescription font);
   MenuButton(int id, double x, double y, double width, double height,
              double roundness, CL_FontDescription font);
   virtual ~MenuButton();

   void draw();

   int getID(){return buttonID;};

   void setPosition(double x, double y);
   void setSize(double width, double height);
   void setText(TGString str);
   void setColor(CL_Colorf colorBackN, CL_Colorf colorBackP, CL_Colorf colorFont);
   void setPressed(bool pressed) {this->pressed = pressed;};

   bool getPointOnButton(double px, double py);

private:
   double x;
   double y;
   double width;
   double height;
   double roundness;

   TGString text;

   CL_Colorf colorBackP;
   CL_Colorf colorBackN;
   CL_Colorf colorFont;
   CL_GraphicContext gc;
   CL_Font_System fontSystem;

   int buttonID;

   bool pressed;
};

#endif /* MENUBUTTON_H_ */
