/*
 * OnScreenMessage.h
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#ifndef ONSCREENMESSAGE_H_
#define ONSCREENMESSAGE_H_

#include <string>

class OnScreenMessage {
public:
	OnScreenMessage(const std::string& message);
	OnScreenMessage(const std::string& message, float timeout);
	~OnScreenMessage();

	std::string getMessage(void);
	float getTimeout(void);

	void reduceTimeout(float secs);
	bool timedOut(void);

private:
	std::string message;
	bool hasTimeout;
	float timeout;
};

#endif /* ONSCREENMESSAGE_H_ */
