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

	void quit(void);
	virtual void processInput(float timepast);
	virtual Bat* getBat(void);
	virtual int getEsterEgg();

	virtual int  getNumber(void);
	virtual void setNumber(int number);

	virtual void incrementScore(void);
	virtual int  getScore(void);
	virtual void setScore(int score);

	virtual void setInvert(bool activate);
	virtual bool getInvert();

private:
	Application* application;
	Bat* bat;
	// todo should be using a ref-counting pointer here
	InputDevice* device;

	int number;

	int score;
};

#endif /* PLAYER_H_ */
