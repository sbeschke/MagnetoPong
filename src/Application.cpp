/*
 * Application.cpp
 *
 *  Created on: 24.06.2011
 *      Author: sebastian
 */

#include "Application.h"

Application::Application() {
	// TODO Auto-generated constructor stub

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

orxSTATUS orxFASTCALL Application::Init()
{
	orxViewport_CreateFromConfig( "Viewport" );
	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL Application::Run()
{
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL Application::Exit()
{

}
