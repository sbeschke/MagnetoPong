#include "Application.h"
#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include "Player.h"
#include "MouseInputDevice.h"


void Application::run(void)
{
	quit = false;
	unsigned int start =  CL_System::get_time();
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



	Ball ball(this);
	ball.setPosition(Vec2d(320,240));
	ball.setCharge(0.1);
	std::vector<Entity*> objects;

	objects.push_back(&ball);


	MouseInputDevice mouseInpDev(&mouse);
	Player player1(this, &mouseInpDev);
	objects.push_back(player1.getBat());

	while (!quit)
	{
		int timediff = CL_System::get_time() - start;
		start = CL_System::get_time();



		if(keyboard.get_keycode(CL_KEY_ESCAPE) == true)
			quit = true;

		if(mouse.get_keycode(CL_MOUSE_WHEEL_DOWN)
				|| mouse.get_keycode(CL_MOUSE_LEFT)) {
			//bat.setCharge(bat.getCharge() - 0.1f);
		}
		if(mouse.get_keycode(CL_MOUSE_WHEEL_UP)
				|| mouse.get_keycode(CL_MOUSE_RIGHT)) {
			//bat.setCharge(bat.getCharge() + 0.1f);
		}

		player1.processInput();

		CL_Point mousePos = mouse.get_position();
		//bat.setPosition(mousePos);

		CL_Colorf red(155/255.0f, 60/255.0f, 68/255.0f);
		CL_Gradient gradient1(CL_Colorf::black, red);
		CL_Draw::gradient_fill(gc, CL_Rectf(0,0,640,480), gradient1);

		//draw_sunset(gc);

		//boat_sprite.draw(gc, 70, 252);

		//font.draw_text(gc, 146, 50, "A quiet evening in the pacific...");



		ball.draw();
		ball.updateforces(objects,timediff);





		ball.updateposition(timediff);
		player1.getBat()->draw();
		//std::ostringstream oss;
		//font.draw_text(gc, 146, 50, oss.str());
		//boat_sprite.update();
		window.flip();
		CL_KeepAlive::process();
		//CL_System::sleep(10);
	}
}
