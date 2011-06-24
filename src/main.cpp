#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <ClanLib/sound.h>

class SpritesExample
{
private:
	bool quit;

public:
	void run()
	{
		quit = false;

		CL_DisplayWindowDescription window_desc;
		window_desc.set_size(CL_Size(640, 480), true);
		window_desc.set_title("Sunset");
		CL_DisplayWindow window(window_desc);

		CL_Slot slot_quit = window.sig_window_close().connect(this, &SpritesExample::on_window_close);

		CL_GraphicContext gc = window.get_gc();
		CL_InputDevice keyboard = window.get_ic().get_keyboard();

		CL_ResourceManager resources("resources.xml");

		CL_Sprite boat_sprite(gc, "Boat", &resources);

		CL_FontDescription font_desc;
		font_desc.set_typeface_name("tahoma");
		font_desc.set_height(30);
		CL_Font_System font(gc, font_desc);

		while (!quit)
		{
			if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
				quit = true;

			draw_sunset(gc);

			boat_sprite.draw(gc, 70, 252);

			font.draw_text(gc, 146, 50, "A quiet evening in the pacific...");

			boat_sprite.update();

			window.flip();
			CL_KeepAlive::process();
			CL_System::sleep(10);
		}
	}

	void draw_sunset(CL_GraphicContext &gc)
	{
		CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		CL_Colorf yellow(255/255.0f, 234/255.0f, 117/255.0f);
		CL_Colorf blue(13/255.0f, 75/255.0f, 74/255.0f);
		CL_Colorf lightblue(16/255.0f, 91/255.0f, 90/255.0f);

		// Draw top of sunset
		CL_Gradient gradient1(CL_Colorf::black, red);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,0,640,160), gradient1);

		// Draw second part of sunset
		CL_Gradient gradient2(red, yellow);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,160,640,240), gradient2);

		// Draw the sun
		CL_Draw::circle(gc, CL_Pointf(320, 240), 15, CL_Colorf::white);

		// Draw the ground
		CL_Draw::fill(gc, CL_Rectf(0, 240, 640, 480), blue);

		// Draw some distance lines
		for(int y = 241, ydelta = 2; y < 480; y += ydelta, ydelta += ydelta)
		{
			CL_Draw::line(gc, 0, y, 640, y, lightblue);
		}
	}

	void on_window_close()
	{
		quit = true;
	}
};

class Program
{
public:
	static int main(const std::vector<CL_String> &args)
	{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		try
		{
			SpritesExample example;
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