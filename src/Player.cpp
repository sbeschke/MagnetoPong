/*
 * Player.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Player.h"
#include "Bat.h"
#include "InputDevice.h"
#include "Application.h"
#include "BoostBar.h"

Player::Player(Application* application, InputDevice* device, int playerSlot)
: application(application), device(device), score(0)
{
   this->playerSlot = playerSlot;
	bat = new Bat(application);

	bar = new BoostBar(playerSlot);
   bar->setMaxValue(BOOSTRELOADTIME);
}

Player::~Player()
{
   delete bar;
	delete bat;
}
//---------------------------------------------------------------------------

void Player::quit(void)
{
}
//---------------------------------------------------------------------------

void Player::processInput(float timepast)
{
   device->processInput(timepast);
	bat->setPosition(device->getPoint());
	bat->setCharge(device->getZ());
	bat->setBoost(device->getJump());
	bar->setValue(bat->getBoostctr());
}
//---------------------------------------------------------------------------

void Player::draw(int what)
{
   if(what & BAR) bar->draw();
   if(what & SKELETON) application->kinect.drawPlayer(number);
   if(what & BAT) bat->draw();
}
//---------------------------------------------------------------------------

Bat* Player::getBat(void)
{
	return bat;
}
//---------------------------------------------------------------------------

int Player::getEsterEgg()
{
   return device->getEsterEgg();
}
//---------------------------------------------------------------------------

bool Player::getKlick()
{
   return device->getKlick();
}
//---------------------------------------------------------------------------

int Player::getNumber(void)
{
	return number;
}
//---------------------------------------------------------------------------

void Player::setNumber(int number)
{
	this->number = number;
}
//---------------------------------------------------------------------------

int Player::getPlayerSlot()
{
   return playerSlot;
}
//---------------------------------------------------------------------------

void Player::setPlayerSlot(int playerSlot)
{
   this->playerSlot = playerSlot;
}
//---------------------------------------------------------------------------

void Player::incrementScore(void)
{
	score++;
}
//---------------------------------------------------------------------------

int Player::getScore(void)
{
	return score;
}
//---------------------------------------------------------------------------

void Player::setScore(int score)
{
	this->score = score;
}
//---------------------------------------------------------------------------

void Player::setInvert(bool activate)
{
   device->setInvert(activate);
}
//---------------------------------------------------------------------------

bool Player::getInvert()
{
   return device->getInvert();
}
//---------------------------------------------------------------------------

bool Player::getExit()
{
   return device->getExit();
}
//---------------------------------------------------------------------------
