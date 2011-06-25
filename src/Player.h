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
	virtual void processInput(void);
	virtual Bat* getBat(void);
	virtual bool getKick();

	virtual int  getNumber(void);
	virtual void setNumber(int number);

	virtual void incrementScore(void);
	virtual int  getScore(void);
	virtual void setScore(int score);

private:
	Application* application;
	Bat* bat;
	// todo should be using a ref-counting pointer here
	InputDevice* device;

	int number;

	int score;
};

#endif /* PLAYER_H_ */
