/*
 * Application.h
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "orx.h"
#include "Scene.h"

class Application {
public:
	static Application* theApplication;

	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void orxFASTCALL Exit();

	Application();
	virtual ~Application();

private:
	Scene* scene;
};

#endif /* APPLICATION_H_ */
