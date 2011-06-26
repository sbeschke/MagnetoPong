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

Player::Player(Application* application, InputDevice* device)
: application(application), device(device), score(0)
{
	bat = new Bat(application);
	application->addEntity(bat);
}

Player::~Player()
{

	delete bat;
}

void Player::quit(void)
{
	application->remEntity(bat);
}

void Player::processInput(float timepast)
{
	bat->setPosition(device->getPoint(timepast));
	bat->setCharge(device->getZ());
	bat->setBoost(device->getJump());
}

Bat* Player::getBat(void)
{
	return bat;
}

int Player::getEsterEgg()
{
   return device->getEsterEgg();
}

int Player::getNumber(void)
{
	return number;
}

void Player::setNumber(int number)
{
	this->number = number;
}

void Player::incrementScore(void)
{
	score++;
}

int Player::getScore(void)
{
	return score;
}

void Player::setScore(int score)
{
	this->score = score;
}

void Player::setInvert(bool activate)
{
   device->setInvert(activate);
}

bool Player::getInvert()
{
   return device->getInvert();
}
