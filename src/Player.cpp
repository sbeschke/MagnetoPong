/*
 * Player.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Player.h"
#include "Bat.h"
#include "InputDevice.h"

Player::Player(Application* application, InputDevice* device)
: application(application), device(device)
{
	bat = new Bat(application);
}

Player::~Player() {
	delete bat;
}

void Player::processInput(void) {
	bat->setPosition(device->getPoint());
}

Bat* Player::getBat(void) {
	return bat;
}

