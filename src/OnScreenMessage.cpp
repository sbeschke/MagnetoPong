/*
 * OnScreenMessage.cpp
 *
 *  Created on: 25.06.2011
 *      Author: sebastian
 */

#include "OnScreenMessage.h"
#include <string>

OnScreenMessage::OnScreenMessage(const std::string& message)
: message(message), timeout(0.0f), hasTimeout(false)
{

}

OnScreenMessage::OnScreenMessage(const std::string& message, float timeout)
: message(message), timeout(timeout), hasTimeout(true)
{

}

OnScreenMessage::~OnScreenMessage() {
}

std::string OnScreenMessage::getMessage(void)
{
	return message;
}

float OnScreenMessage::getTimeout(void) {
	return timeout;
}

void OnScreenMessage::reduceTimeout(float secs) {
	timeout -= secs;
}

bool OnScreenMessage::timedOut(void) {
	return timeout <= 0.0f;
}
