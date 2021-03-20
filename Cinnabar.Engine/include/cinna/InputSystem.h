#pragma once

#include "PCH.h"

#include "Button.h"
#include "EcsSystem.h"

namespace cinna
{
	class InputSystem final : public EcsSystem
	{
	public:
		void handle_end_of_frame();
		void handle_keyboard_event(ALLEGRO_EVENT const& event);
		void handle_joystick_event(ALLEGRO_EVENT const& event);
		void handle_mouse_event(ALLEGRO_EVENT const& event);

	private:
		void button_down(Button& button);
		void button_up(Button& button);
		void handle_joy_down(int joy_code);
		void handle_joy_up(int joy_code);
		void handle_key_down(int key_code);
		void handle_key_up(int key_code);
	};
}
