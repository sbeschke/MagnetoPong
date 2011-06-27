#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <ClanLib/sound.h>
#include "Application.h"

#include <iostream>

class Program
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;


		CL_String filename = "";
		if(CL_FileHelp::file_exists("magnetopong.xml"))
		{
			filename = "magnetopong.xml";
		}
		else if(CL_FileHelp::file_exists("~/.magnetopong/config.xml"))
		{
			filename = "~/.magnetopong.xml";
		}
		else if(CL_FileHelp::file_exists("/etc/magnetopong.xml"))
		{
			filename = "/etc/magnetopong.xml";
		}
		else
		{
			CL_Console::write_line("Could not find magnetopong.xml\nusing default values");
			Application::x_res = 800;
			Application::y_res = 600;
			Application::fullscreen = false;
		}
		if(filename.length() > 0)try
		{
			CL_File file(filename);
			CL_String ns_magnetopong = "http://magnetopong.org/config";
			CL_DomDocument document(file);
			CL_DomNode root = document.named_item_ns(ns_magnetopong,"config");
			CL_DomElement display = root.named_item( "display").to_element();
			Application::x_res = display.get_child_int("width",800);
			Application::y_res = display.get_child_int("height",600);
			Application::fullscreen = display.get_child_bool("fullscreen",false);
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("DOM Error: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}
		Application::detail = 1;

		for(std::vector<CL_String>::const_iterator it = args.begin(); it != args.end(); it++) {
			if(*it == "low") {
				Application::detail = 0;
			}
		}

		try
		{
			Application example;
			example.run();
		}
		catch(CL_Exception &exception)
		{
			// Create a console window for text-output if not available
			CL_ConsoleWindow console("Console", 80, 160);
			CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());
			console.display_close_message();

			return -1;
		}

		return 0;
	}
};
CL_ClanApplication app(&Program::main);
