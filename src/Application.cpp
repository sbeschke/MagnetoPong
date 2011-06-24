#include "Application.h"
#include "Bat.h"

void Application::run(void)
{
	quit = false;

	CL_DisplayWindowDescription window_desc;
	window_desc.set_size(CL_Size(640, 480), true);
	window_desc.set_title("MagnetoPong!!!11einself");
	CL_DisplayWindow window(window_desc);

	CL_Slot slot_quit = window.sig_window_close().connect(this, &Application::on_window_close);

	graphicContext = window.get_gc();
	CL_GraphicContext& gc = graphicContext;
	CL_InputDevice keyboard = window.get_ic().get_keyboard();
	CL_InputDevice mouse = window.get_ic().get_mouse(0);

	CL_ResourceManager resources("resources.xml");

	CL_Sprite boat_sprite(gc, "Boat", &resources);

	CL_FontDescription font_desc;
	font_desc.set_typeface_name("tahoma");
	font_desc.set_height(30);
	CL_Font_System font(gc, font_desc);

	Bat bat(this);

	while (!quit)
	{
		if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
			quit = true;

		if(mouse.get_keycode(CL_MOUSE_WHEEL_DOWN)
				|| mouse.get_keycode(CL_MOUSE_LEFT)) {
			bat.setCharge(bat.getCharge() - 0.1f);
		}
		if(mouse.get_keycode(CL_MOUSE_WHEEL_UP)
				|| mouse.get_keycode(CL_MOUSE_RIGHT)) {
			bat.setCharge(bat.getCharge() + 0.1f);
		}

		CL_Point mousePos = mouse.get_position();
		bat.setPosition(mousePos);

		CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		CL_Gradient gradient1(CL_Colorf::black, red);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,0,640,480), gradient1);

		//draw_sunset(gc);

		//boat_sprite.draw(gc, 70, 252);

		//font.draw_text(gc, 146, 50, "A quiet evening in the pacific...");

		bat.draw();

		//boat_sprite.update();

		window.flip();
		CL_KeepAlive::process();
		//CL_System::sleep(10);
	}
}
