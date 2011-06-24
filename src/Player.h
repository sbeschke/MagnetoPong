/*
 * Player.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef PLAYER_H_
#define PLAYER_H_

class Application;
class Bat;
class InputDevice;

class Player {
public:
	Player(Application* application, InputDevice* device);
	virtual ~Player();

	virtual void processInput(void);
	virtual Bat* getBat(void);

private:
	Application* application;
	Bat* bat;
	// todo should be using a ref-counting pointer here
	InputDevice* device;
};

#endif /* PLAYER_H_ */
