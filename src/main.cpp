#include "orx.h"
#include "Application.h"

int main( int argc, char** argv )
{
	orx_Execute( argc, argv, Application::Init, Application::Run, Application::Exit );

	return 0;
}
