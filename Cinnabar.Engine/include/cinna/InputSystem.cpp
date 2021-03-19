#include "PCH.h"

#include "EcsAgent.h"
#include "InputContext.h"
#include "InputSystem.h"

namespace cinna
{
	void InputSystem::handle_end_of_frame()
	{
		auto& controller_state = ecs_agent->get_component<InputContext>().controller_state;
		
		controller_state.Down.just_pressed = false;
		controller_state.Left.just_pressed = false;
		controller_state.Right.just_pressed = false;
		controller_state.Up.just_pressed = false;

		controller_state.A.just_pressed = false;
		controller_state.B.just_pressed = false;
		controller_state.L.just_pressed = false;
		controller_state.R.just_pressed = false;
		controller_state.Select.just_pressed = false;
		controller_state.Start.just_pressed = false;
		controller_state.X.just_pressed = false;
		controller_state.Y.just_pressed = false;
	}

	// Private function ///////////////////////////////////////////////////////////////////////////

	void InputSystem::handle_keyboard_event(ALLEGRO_EVENT const& event)
	{

	}

	void InputSystem::handle_joystick_event(ALLEGRO_EVENT const& event)
	{

	}

	void InputSystem::handle_mouse_event(ALLEGRO_EVENT const& event)
	{

	}
}
