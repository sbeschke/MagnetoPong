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
class BoostBar;

class Player
{
public:
	Player(Application* application, InputDevice* device, int playerSlot);
	virtual ~Player();

	void quit(void);
	virtual void processInput(float timepast);
	virtual void draw(int what);
	virtual Bat* getBat(void);
	virtual int  getEsterEgg();
	virtual bool getKlick();

	virtual int  getNumber(void);
	virtual void setNumber(int number);
	virtual int  getPlayerSlot();
	virtual void setPlayerSlot(int playerSlot);

	virtual void incrementScore(void);
	virtual int  getScore(void);
	virtual void setScore(int score);

	virtual void setInvert(bool activate);
	virtual bool getInvert();

	virtual bool getExit();

	static const int BAR      = 1;
	static const int SKELETON = 2;
	static const int BAT      = 4;

private:
	Application* application;
	Bat* bat;
	BoostBar* bar;
	// todo should be using a ref-counting pointer here
	InputDevice* device;


	int number;
	int playerSlot;

	int score;
};

#endif /* PLAYER_H_ */
