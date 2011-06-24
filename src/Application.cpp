/*
 * Application.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Application.h"
#include "Game.h"

Application* Application::theApplication;

Application::Application() {
	scene = new Game();
	scene->seize();
}

Application::~Application() {
	scene->yield();
	delete scene;
}

orxSTATUS orxFASTCALL Application::Init()
{
	theApplication = new Application();
	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL Application::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL Application::Exit()
{
	delete theApplication;
}
