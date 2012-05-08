
#include "precomp.h"
#include "redballapp.h"
#include "entity.h"
#include "component_visual.h"
#include "component_bounce.h"
#include "component_colorshift.h"
#include "component_sound.h"
#include "visual_manager.h"
#include "sound_manager.h"

void RedBallApp::run()
{
	quit = false;

	CL_DisplayWindowDescription desc;
	desc.set_title("Red Ball");
	desc.set_size(CL_Size(800, 600), true);
	desc.set_allow_resize(true);

	CL_DisplayWindow window(desc);

	CL_Slot slot_quit = window.sig_window_close().connect(this, &RedBallApp::on_window_close);
	CL_Slot slot_input_up = (window.get_ic().get_keyboard()).sig_key_up().connect(this, &RedBallApp::on_input_up);

	CL_GraphicContext gc = window.get_gc();

	VisualManager visual_manager;
	SoundManager sound_manager;
	sound_manager.add_sound("bounce", "Resources/bounce.ogg");

	Entity background;
	background.addComponent(std::make_shared<Visual>(&background, visual_manager));
	background.get<CL_Sprite>("sprite") = CL_Sprite(gc, "Resources/background.jpg");
	background.get<CL_Origin>("alignment") = origin_top_left;

	Entity ball1;
	ball1.addComponent(std::make_shared<Visual>(&ball1, visual_manager));
	ball1.get<CL_Sprite>("sprite") = CL_Sprite(gc, "Resources/Ball.png");
	ball1.get<CL_Colorf>("color") = CL_Colorf(1.0f, 0.2f, 0.2f, 1.0f);
	ball1.get<CL_Pointf>("scale") = CL_Pointf(0.3f, 0.3f);
	ball1.get<CL_Pointf>("position") = CL_Pointf(200.0f, 400.0f);
	entities.push_back(&ball1);

	Entity ball2;
	ball2.addComponent(std::make_shared<Visual>(&ball2, visual_manager));
	ball2.addComponent(std::make_shared<Bounce>(&ball2));
	ball2.addComponent(std::make_shared<Sound>(&ball2, sound_manager));
	ball2.get<CL_Sprite>("sprite") = CL_Sprite(gc, "Resources/Ball.png");
	ball2.get<CL_Colorf>("color") = CL_Colorf(1.0f, 0.2f, 0.2f, 1.0f);
	ball2.get<CL_Pointf>("scale") = CL_Pointf(0.3f, 0.3f);
	ball2.get<CL_Pointf>("position") = CL_Pointf(400.0f, 400.0f);
	ball2.get<float>("bounce_height") = 150.0f;
	ball2.get<float>("bounce_speed") = 5.0f;
	entities.push_back(&ball2);

	Entity ball3;
	ball3.addComponent(std::make_shared<Visual>(&ball3, visual_manager));
	ball3.addComponent(std::make_shared<ColorShift>(&ball3));
	ball3.get<CL_Sprite>("sprite") = CL_Sprite(gc, "Resources/Ball.png");
	ball3.get<CL_Colorf>("color") = CL_Colorf(1.0f, 0.2f, 0.2f, 1.0f);
	ball3.get<CL_Pointf>("scale") = CL_Pointf(0.3f, 0.3f);
	ball3.get<CL_Pointf>("position") = CL_Pointf(600.0f, 400.0f);
	entities.push_back(&ball3);

	unsigned int last_time = CL_System::get_time();
	while (!quit)
	{
		unsigned int current_time = CL_System::get_time();
		float time_delta_ms = static_cast<float> (current_time - last_time);
		last_time = current_time;

		for(size_t i = 0; i < entities.size(); ++i)
			entities[i]->update(time_delta_ms);

		visual_manager.render(gc);

		window.flip(1);
		CL_KeepAlive::process(0);
	}
}

void RedBallApp::on_input_up(const CL_InputEvent &key)
{
	if(key.id == CL_KEY_ESCAPE)
	{
		quit = true;
	}
}

void RedBallApp::on_window_close()
{
	quit = true;
}
