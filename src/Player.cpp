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

Player::Player(Application* application, InputDevice* device)
: application(application), device(device)
{
	bat = new Bat(application);
	application->addEntity(bat);
}

Player::~Player() {
	application->remEntity(bat);
	delete bat;
}

void Player::processInput(void) {
	bat->setPosition(device->getPoint());
	bat->setCharge(device->getZ());
}

Bat* Player::getBat(void) {
	return bat;
}

int Player::getNumber(void) {
	return number;
}

void Player::setNumber(int number) {
	this->number = number;
}
