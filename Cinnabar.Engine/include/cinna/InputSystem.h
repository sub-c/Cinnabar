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
		
	};
}
