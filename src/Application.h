/*
 * Application.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "orx.h"

class Application {
public:
	Application();
	virtual ~Application();

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void orxFASTCALL Exit();
};

#endif /* APPLICATION_H_ */
